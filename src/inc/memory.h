#include "..\inc\mutex.h"
#include "..\inc\avl_tree.h"

typedef struct mem_managed_s
{
	int				is_init;
	spinlock_t		spinlock;
	mutex_t			mutex;
	avl_tree_node_t *tree;
}mem_managed_t;

#define Mem_Malloc(size)		Mem_Malloc_IMP(size, (char*)__FILE__, (char*)__FUNCTION__, __LINE__)
#define Mem_Realloc(mem, size)	Mem_Realloc_IMP(mem, size, (char*)__FILE__, (char*)__FUNCTION__, __LINE__)

#define MemM_Malloc(mmem, size)			MemM_Malloc_IMP(mmem, size, (char*)__FILE__, (char*)__FUNCTION__, __LINE__)
#define MemM_Realloc(mmem, mem, size)	MemM_Realloc_IMP(mmem, mem, size, (char*)__FILE__, (char*)__FUNCTION__, __LINE__)

void Mem_Free(void *memblock);
void *Mem_Malloc_IMP(size_t size, char *file, char *function, int line);
void *Mem_Realloc_IMP(void *ptr, size_t size, char *file, char *function, int line);
void Mem_ReportAllocatedBlocks();
void Mem_Destroy();

mem_managed_t *MemM_New();
void MemM_Destroy(mem_managed_t **memm);
void *MemM_Malloc_IMP(mem_managed_t *memm, size_t size, char *file, char *function, int line);
void *MemM_Realloc_IMP(mem_managed_t *memm, void *ptr, size_t size, char *file, char *function, int line);
void MemM_AddRef(mem_managed_t *memm, void *memblock);
void MemM_RemoveRef(mem_managed_t *memm, void *memblock);
void MemM_Free(mem_managed_t *memm, void *memblock);
void MemM_ReportAllocatedBlocks(mem_managed_t *memm);