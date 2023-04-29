#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "..\inc\avl_tree.h"
#include "..\inc\math.h"
#include "..\inc\system.h"

#define USE_RAW_MALLOC 1

#if USE_RAW_MALLOC
#define Mem_Malloc	malloc
#define Mem_Free	free
#define Mem_Realloc	realloc
#define Mem_MemSize _msize
#endif

uint64_t g_avl_count = 0;
uint64_t g_avl_mem = 0;


// TODO: use setjmp / longjmp for AVL_Walk
// TODO: Walk should use root level flag to provide early exit

struct trunk 
{
	struct trunk *prev;
	char * str;
};

void AVL_show_trunks(struct trunk *p)
{
	if (!p) 
		return;
	AVL_show_trunks(p->prev);
	printf("%s", p->str);
}

// this is very haphazzard
void AVL_show_tree(avl_tree_node_t *root, struct trunk *prev, int is_left, void (*payload_cb)(void *payload, avl_tree_node_t *node))
{
	if (root == NULL) 
		return;

	struct trunk this_disp = { prev, "    " };
	char *prev_str = this_disp.str;
	AVL_show_tree(root->child[0], &this_disp, 1, payload_cb);

	if (!prev)
		this_disp.str = "---";
	else if (is_left) 
	{
		this_disp.str = ".--";
		prev_str = "   |";
	} 
	else 
	{
		this_disp.str = "`--";
		prev->str = prev_str;
	}

	AVL_show_trunks(&this_disp);
	payload_cb(root->payload, root);

	if (prev) 
		prev->str = prev_str;
	this_disp.str = "   |";

	AVL_show_tree(root->child[1], &this_disp, 0, payload_cb);
	if (!prev) 
		printf("\n");
}

int AVL_verify(avl_tree_node_t *p)
{
	if (p == NULL) 
		return 1;

	int h0 = p->child[0]->height, h1 = p->child[1]->height;
	int b = h0 - h1;

	if (p->height != 1 + max(h0, h1) || b < -1 || b > 1) {
		printf("node 0x%016"PRIX64" bad, balance %i\n", (uint64_t)p->payload, b);
		AVL_show_tree(p, 0, 0, 0);
	}
	return AVL_verify(p->child[0]) && AVL_verify(p->child[1]);
}












static avl_tree_node_t *AVLTree_NewNode(avl_tree_node_t *parent, void *payload)
{
	avl_tree_node_t *n = Mem_Malloc(sizeof(avl_tree_node_t));

	g_avl_count++;
	g_avl_mem += Mem_MemSize(n);

	n->payload = payload;
	n->height = 1;
	n->num_children = 0;
	n->child[0] = NULL;
	n->child[1] = NULL;
	n->parent = parent;

	return n;
}

static void AVLTree_SetHeight(avl_tree_node_t *n) 
{
	n->height = 1 + Math_Maxi32((n->child[0] ? n->child[0]->height : 0), (n->child[1] ? n->child[1]->height : 0));
}

static int AVLTree_Balance(avl_tree_node_t *n) 
{
	return (n->child[0] ? n->child[0]->height : 0) - (n->child[1] ? n->child[1]->height : 0);
}

static avl_tree_node_t * AVLTree_Rotate(avl_tree_node_t **rootp, int dir)
{
	avl_tree_node_t *old_r = *rootp;
	avl_tree_node_t *new_r = old_r->child[dir];
	avl_tree_node_t *parent = old_r->parent;

	*rootp = new_r;

	if (NULL == *rootp)
	{
		while (parent != NULL)
		{
			parent->num_children--;
			parent = parent->parent;
		}

		g_avl_count--;
		g_avl_mem -= Mem_MemSize(old_r);

		Mem_Free(old_r);

	}
	else 
	{
		old_r->child[dir] = new_r->child[!dir];
		AVLTree_SetHeight(old_r);
		new_r->child[!dir] = old_r;

		new_r->parent = old_r->parent;
		old_r->parent = new_r;

		if (new_r->child[dir] != NULL)
			new_r->child[dir]->parent = new_r;
		if (old_r->child[dir] != NULL)
			old_r->child[dir]->parent = old_r;

		old_r->num_children = (old_r->child[0] != NULL ? old_r->child[0]->num_children + 1 : 0) + (old_r->child[1] != NULL ? old_r->child[1]->num_children + 1: 0);
		new_r->num_children = (new_r->child[0] != NULL ? new_r->child[0]->num_children + 1 : 0) + (new_r->child[1] != NULL ? new_r->child[1]->num_children + 1: 0);
	}
	return new_r;
}

void AVLTree_AdjustBalance(avl_tree_node_t **rootp)
{
	avl_tree_node_t *root = *rootp;
	int b;
	if (!root)
		return;
	b = AVLTree_Balance(root)/2;
	if (b) 
	{
		int dir = (1 - b)/2;
		if (AVLTree_Balance(root->child[dir]) == -b)
			AVLTree_Rotate(&root->child[dir], !dir);
		root = AVLTree_Rotate(rootp, dir);
	}
	if (root != NULL) 
		AVLTree_SetHeight(root);
}

void **AVLTree_Query(avl_tree_node_t *root, void *value, void *context, int (*compare_fp)(void *arg0, void *arg1, void *context))
{
	if (root == NULL)
		return 0;
	else
	{
		if (compare_fp(value, root->payload, context) == 0)
			return &root->payload;
		else
		{
			int dir = compare_fp(value, root->payload, context) == 1 ? 1 : 0;
			return AVLTree_Query(root->child[dir], value, context, compare_fp);
		}
	}
}

static void AVLTree_InsertInternal(avl_tree_node_t **rootp, avl_tree_node_t *parent, void *value, void *context, int (*compare_fp)(void *arg0, void *arg1, void *context))
{
	avl_tree_node_t *root = *rootp;

	if (root == NULL)
	{
		*rootp = AVLTree_NewNode(parent, value);
		while (parent != NULL)
		{
			parent->num_children++;
			parent = parent->parent;
		}
	}
	else if (compare_fp(value, root->payload, context)) 
	{
		int dir = compare_fp(value, root->payload, context) == 1 ? 1 : 0;

		AVLTree_InsertInternal(&root->child[dir], root, value, context, compare_fp);
		AVLTree_AdjustBalance(rootp);
	}
}

void AVLTree_Insert(avl_tree_node_t **rootp, void *value, void *context, int (*compare_fp)(void *arg0, void *arg1, void *context))
{
	AVLTree_InsertInternal(rootp, *rootp ? (*rootp)->parent : NULL, value, context, compare_fp);
}

static void AVLTree_DeleteValueInternal(avl_tree_node_t **rootp, void *value, void *context, void **payload, int (*compare_fp)(void *arg0, void *arg1, void *context))
{
	avl_tree_node_t *root = *rootp;
	int dir;

	if (root == NULL) 
		return;

	if (compare_fp(value, root->payload, context) == 0)
	{
		*payload = root->payload;
		root = AVLTree_Rotate(rootp, AVLTree_Balance(root) < 0);
		if (NULL == root)
			return;
	}

	dir = compare_fp(value, root->payload, context) == 1 ? 1 : 0;

	AVLTree_DeleteValueInternal(&root->child[dir], value, context, payload, compare_fp);
	AVLTree_AdjustBalance(rootp);
}
void AVLTree_DeleteValue(avl_tree_node_t **rootp, void *value, void *context, int (*compare_fp)(void *arg0, void *arg1, void *context), void (*delete_fp)(void *value, void *context))
{
	void *payload = 0;

	AVLTree_DeleteValueInternal(rootp, value, context, &payload, compare_fp);

	if (delete_fp && payload)
		delete_fp(payload, context);
}

avl_tree_node_t *AVLTree_New()
{
	return NULL;
}
void AVLTree_Destroy(avl_tree_node_t **root, void *context, void (*delete_fp)(void *value, void *context)) // TODO: balance parents afterwards?
{
	avl_tree_node_t *parent;

	if (*root == NULL) 
		return;

	parent = (*root)->parent;

	while (parent != NULL)
	{
		parent->num_children -= (*root)->num_children;
		parent = parent->parent;
	}

	if ((*root)->child[0] != NULL)
		AVLTree_Destroy(&(*root)->child[0], context, delete_fp);
	if ((*root)->child[1] != NULL)
		AVLTree_Destroy(&(*root)->child[1], context, delete_fp);

	if (delete_fp)
		delete_fp((*root)->payload, context);

	g_avl_count--;
	g_avl_mem -= Mem_MemSize(*root);

	Mem_Free(*root);

	*root = NULL;
}

static void AVLTree_WalkInternal(avl_tree_node_t *root, int *flag, int dir, void *context, int depth, int (*callback_fp)(void *value, void *context, int depth))
{
	if (root == NULL || *flag) 
		return;

	AVLTree_WalkInternal(root->child[dir == 0 ? 0 : 1], flag, dir, context, depth + 1, callback_fp);
	if (*flag)
		return;
	if (callback_fp(root->payload, context, depth))
	{
		*flag = 1;
		return;
	}
	AVLTree_WalkInternal(root->child[dir == 0 ? 1 : 0], flag, dir, context, depth + 1, callback_fp);
}
void AVLTree_Walk(avl_tree_node_t *root, int dir, void *context, int (*callback_fp)(void *value, void *context, int depth))
{
	int flag = 0;

	AVLTree_WalkInternal(root, &flag, dir, context, 0, callback_fp);
}
static void AVLTree_WalkPreInternal(avl_tree_node_t *root, int *flag, int dir, void *context, int depth, int (*callback_fp)(void *value, void *context, int depth))
{
	if (root == NULL || *flag) 
		return;

	if (callback_fp(root->payload, context, depth))
	{
		*flag = 1;
		return;
	}
	AVLTree_WalkPreInternal(root->child[dir == 0 ? 0 : 1], flag, dir, context, depth + 1, callback_fp);
	if (*flag)
		return;
	AVLTree_WalkPreInternal(root->child[dir == 0 ? 1 : 0], flag, dir, context, depth + 1, callback_fp);
}
void AVLTree_WalkPre(avl_tree_node_t *root, int dir, void *context, int (*callback_fp)(void *value, void *context, int depth))
{
	int flag = 0;

	AVLTree_WalkPreInternal(root, &flag, dir, context, 0, callback_fp);
}
void *AVLTree_Payload(avl_tree_node_t *root)
{
	if (root == NULL)
		return 0;
	else
		return root->payload;
}
void **AVLTree_PayloadP(avl_tree_node_t *root)
{
	if (root == NULL)
		return 0;
	else
		return &root->payload;
}