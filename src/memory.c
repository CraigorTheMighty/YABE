#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <conio.h>
#include <commctrl.h>
#include <math.h>
#include <psapi.h>
#include <Dbghelp.h>
#include <inttypes.h>

#include "..\inc\mutex.h"
#include "..\inc\memory.h"
#include "..\inc\timer.h"
#include "..\inc\system.h"

#define REFTYPE_EXTENDED	1
#define REFTYPE_RAW			2

typedef struct malloc_block_s
{
	size_t	memsize;
	int		block_list_index;
	char	*file;
	char	*function;
	int		line;
}malloc_block_t;

typedef struct malloc_tree_entry_s
{
	void	*memblock;
	int		reftype;
}malloc_tree_entry_t;

mem_managed_t g_malloc = 
{
	.is_init = 0,
	.spinlock = SPINLOCK_INIT
};

static void Mem_ShowTree(void *payload, avl_tree_node_t *node)
{
	printf("0x%016"PRIX64"\n", (uint64_t)payload);
}

static int Mem_AVLCompare(void *arg0, void *arg1, void *context)
{
	if (arg0 == arg1)
		return 0;
	else if (arg0 > arg1)
		return 1;
	else
		return -1;
}
static int Mem_WalkAVLTreePrint(void *value, void *context, int depth)
{
	*(size_t*)context += ((malloc_block_t*)value)->memsize;
	ALWAYS_PRINT_NODEC("Block of size %I64u allocated at %s:%s():%i 0x%016"PRIX64"\n", ((malloc_block_t*)value)->memsize, ((malloc_block_t*)value)->file, ((malloc_block_t*)value)->function, ((malloc_block_t*)value)->line, (uint64_t)(malloc_block_t*)value);
	return 0;
}

static void Mem_EnsureInit()
{
	SpinLock_Lock(&g_malloc.spinlock);
	if (!g_malloc.is_init)
	{
		Mutex_Init(&g_malloc.mutex);
		g_malloc.is_init = 1;
		g_malloc.tree = AVLTree_New();
	}
	SpinLock_Unlock(&g_malloc.spinlock);
}
static void Mem_DestroyCB(void *value, void *context)
{
	free(value);
}


void *Mem_Malloc_IMP(size_t size, char *file, char *function, int line)
{
	malloc_block_t *ptr = malloc(size + sizeof(malloc_block_t));

	Mem_EnsureInit();

	ptr->memsize = size;
	ptr->file = file;
	ptr->function = function;
	ptr->line = line;

	Mutex_Lock(&g_malloc.mutex);
	AVLTree_Insert(&g_malloc.tree, ptr, 0, Mem_AVLCompare);
	Mutex_Unlock(&g_malloc.mutex);

	return &ptr[1];
}
void *Mem_Realloc_IMP(void *ptr, size_t size, char *file, char *function, int line)
{
	void *memblock = Mem_Malloc_IMP(size, file, function, line);
	malloc_block_t *old_ptr = &((malloc_block_t*)ptr)[-1];

	if (ptr == 0)
		return memblock;

	memcpy(memblock, ptr, old_ptr->memsize);
	
	Mem_Free(ptr);
	
	return memblock;
}
void Mem_Free(void *memblock)
{
	malloc_block_t *ptr;

	if (!memblock)
		return;

	Mem_EnsureInit();

	ptr = &((malloc_block_t*)memblock)[-1];

	Mutex_Lock(&g_malloc.mutex);
	if (AVLTree_Query(g_malloc.tree, ptr, 0, Mem_AVLCompare) == 0)
		ALWAYS_PRINT("Attempt to free dangling pointer\n");
	AVLTree_DeleteValue(&g_malloc.tree, ptr, 0, Mem_AVLCompare, 0);
	Mutex_Unlock(&g_malloc.mutex);

	free(ptr);
}
void Mem_ReportAllocatedBlocks()
{
	size_t total = 0;

	Mutex_Lock(&g_malloc.mutex);
	AVLTree_Walk(g_malloc.tree, 0, &total, Mem_WalkAVLTreePrint);
	Mutex_Unlock(&g_malloc.mutex);

	if (total)
		ALWAYS_PRINT_NODEC("Total memory leaked: %.2f MB\n", total / 1048576.0);
}
void Mem_Destroy()
{
	Mutex_Lock(&g_malloc.mutex);
	AVLTree_Destroy(&g_malloc.tree, 0, Mem_DestroyCB);
	Mutex_Unlock(&g_malloc.mutex);
}












static void MemM_DestroyCB(void *value, void *context)
{
	Mem_Free(value);
}

mem_managed_t *MemM_New()
{
	mem_managed_t *memm = Mem_Malloc(sizeof(mem_managed_t));
	memset(memm, 0, sizeof(mem_managed_t));
	Mutex_Init(&memm->mutex);
	memm->tree = AVLTree_New();
	return memm;
}
void MemM_Destroy(mem_managed_t **memm)
{
	AVLTree_Destroy(&(*memm)->tree, (*memm), MemM_DestroyCB);
	Mutex_Delete(&(*memm)->mutex);
	Mem_Free(*memm);
	*memm = 0;
}
void MemM_Discard(mem_managed_t **memm)
{
	AVLTree_Destroy(&(*memm)->tree, (*memm), 0);
	Mutex_Delete(&(*memm)->mutex);
	Mem_Free(*memm);
	*memm = 0;
}

void *MemM_Malloc_IMP(mem_managed_t *memm, size_t size, char *file, char *function, int line)
{
	malloc_block_t *ptr = Mem_Malloc_IMP(size + sizeof(malloc_block_t), file, function, line);

	ptr->memsize = size;
	ptr->file = file;
	ptr->function = function;
	ptr->line = line;

	Mutex_Lock(&memm->mutex);
	AVLTree_Insert(&memm->tree, ptr, 0, Mem_AVLCompare);
	Mutex_Unlock(&memm->mutex);

	return &ptr[1];
}
void *MemM_Realloc_IMP(mem_managed_t *memm, void *ptr, size_t size, char *file, char *function, int line)
{
	void *memblock = MemM_Malloc_IMP(memm, size, file, function, line);
	malloc_block_t *old_ptr = &((malloc_block_t*)ptr)[-1];

	if (ptr == 0)
		return memblock;

	memcpy(memblock, ptr, old_ptr->memsize);

	MemM_Free(memm, ptr);

	return memblock;
}
void MemM_AddRef(mem_managed_t *memm, void *memblock)
{
	malloc_block_t *ptr;

	if (!memblock)
		return;

	ptr = &((malloc_block_t*)memblock)[-1];

	Mutex_Lock(&memm->mutex);
	AVLTree_Insert(&memm->tree, ptr, 0, Mem_AVLCompare);
	Mutex_Unlock(&memm->mutex);
}

void MemM_RemoveRef(mem_managed_t *memm, void *memblock)
{
	malloc_block_t *ptr;

	if (!memblock)
		return;

	ptr = &((malloc_block_t*)memblock)[-1];

	Mutex_Lock(&memm->mutex);
	if (AVLTree_Query(memm->tree, ptr, 0, Mem_AVLCompare) == 0)
		ALWAYS_PRINT("Attempt to remove dangling pointer reference\n");
	AVLTree_DeleteValue(&memm->tree, ptr, 0, Mem_AVLCompare, 0);
	Mutex_Unlock(&memm->mutex);
}
void MemM_Free(mem_managed_t *memm, void *memblock)
{
	malloc_block_t *ptr;

	if (!memblock)
		return;

	ptr = &((malloc_block_t*)memblock)[-1];

	Mutex_Lock(&memm->mutex);
	if (AVLTree_Query(memm->tree, ptr, 0, Mem_AVLCompare) == 0)
		ALWAYS_PRINT("Attempt to free dangling pointer\n");
	AVLTree_DeleteValue(&memm->tree, ptr, 0, Mem_AVLCompare, 0);
	Mutex_Unlock(&memm->mutex);

	Mem_Free(ptr);
}
void MemM_ReportAllocatedBlocks(mem_managed_t *memm)
{
	size_t total = 0;

	Mutex_Lock(&memm->mutex);
	AVLTree_Walk(memm->tree, 0, &total, Mem_WalkAVLTreePrint);
	Mutex_Unlock(&memm->mutex);

	if (total)
		ALWAYS_PRINT_NODEC("Total memory leaked: %.2f MB\n", total / 1048576.0);
}