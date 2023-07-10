#include "Tree.h"

Tree* Tree_Create(void)
{
	Tree* tree = (Tree*)calloc(1, sizeof(Tree));
	assert(tree);

	return tree;
}

TreeNode* Tree_CopyRec(TreeNode* node, void* (*dataCopy)(void*))
{
	if (!node) return NULL;

	TreeNode* res = (TreeNode*)calloc(1, sizeof(TreeNode));
	assert(res);
	
	res->value = dataCopy(node->value);
	res->size = node->size;

	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		res->children[i] = Tree_CopyRec(node->children[i], dataCopy);
	}

	return res;
}

Tree* Tree_Copy(Tree* tree, void* (*dataCopy)(void*))
{
	if (!tree) return NULL;

	Tree* res = (Tree*)calloc(1, sizeof(Tree));
	assert(res);

	res->root = Tree_CopyRec(tree->root, dataCopy);
	res->score = tree->score;

	return res;
}

void Tree_DestroyRec(TreeNode* node, void* (*dataDestroy)(void*))
{
	if (!node) return;

	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		Tree_DestroyRec(node->children[i], dataDestroy);
	}

	if (dataDestroy)
	{
		dataDestroy(node->value);
	}

	free(node);
}

void Tree_Destroy(Tree* tree, void* (*dataDestroy)(void*))
{
	if (!tree) return;

	Tree_DestroyRec(tree->root, dataDestroy);
	free(tree);
}

void Tree_PrintRec(TreeNode* node, void (*dataPrint)(void*), int depth)
{
	if (!node) return;

	for (int i = 0; i < depth; i++)
	{
		putchar('\t');
	}

	dataPrint(node->value);

	putchar('\n');

	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		Tree_PrintRec(node->children[i], dataPrint, depth + 1);
	}
}

void Tree_Print(Tree* tree, void (*dataPrint)(void*))
{
	if (tree)
	{
		if (tree->root)
		{
			printf("------------------------------ Tree (size=%d) ------------------------------ \n\n", tree->root->size);
			Tree_PrintRec(tree->root, dataPrint, 0);
		}
		else
		{
			printf("Tree is empty. \n");
		}
	}
	else
	{
		printf("Tree is null. \n");
	}

	putchar('\n');
}

int Tree_UpdateSizeRec(TreeNode* node)
{
	if (!node) return 0;

	int res = 0;

	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		res += Tree_UpdateSizeRec(node->children[i]);
	}

	node->size = (res + 1);

	return node->size;
}

int Tree_UpdateSize(Tree* tree)
{
	return Tree_UpdateSizeRec(tree->root);
}

int Tree_GetSize(Tree* tree)
{
	return tree->root->size;
}

// TreeSearch:

TreeSearch* TreeSearch_Create(TreeNode* node, TreeNode* parent, int child)
{
	TreeSearch* search = (TreeSearch*)calloc(1, sizeof(TreeSearch));
	assert(search);

	search->node = node;
	search->parent = parent;
	search->child = child;

	return search;
}

TreeSearch* Tree_GetNodeByIndexRec(TreeNode* node, int* index, TreeNode* parent, int child)
{
	if (!node) return NULL;

	if (*index == 0) return TreeSearch_Create(node, parent, child);

	*index -= 1;

	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		TreeSearch* res = Tree_GetNodeByIndexRec(node->children[i], index, node, i);

		if (res) return res;
	}

	return NULL;
}

TreeSearch* Tree_GetNodeByIndex(Tree* tree, int index)
{
	assert((0 <= index) && (index < Tree_GetSize(tree)));

	return Tree_GetNodeByIndexRec(tree->root, &index, NULL, -1);
}

void Tree_GetNodeByValueRec(TreeNode* node, void* value, int (*dataCompare)(void*, void*), TreeNode* parent, int child, DList* list)
{
	if (!node) return NULL;

	if (dataCompare(node->value, value) == 0)
	{
		DList_InsertLast(list, TreeSearch_Create(node, parent, child));
	}

	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		Tree_GetNodeByValueRec(node->children[i], value, dataCompare, node, i, list);
	}
}

DList* Tree_GetNodeByValue(Tree* tree, void* value, int (*dataCompare)(void*, void*))
{
	DList* list = DList_Create();
	
	Tree_GetNodeByValueRec(tree->root, value, dataCompare, NULL, -1, list);
	
	return list;
}
