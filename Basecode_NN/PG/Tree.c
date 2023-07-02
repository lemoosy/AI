#include "Tree.h"

Tree* Tree_New(void)
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

	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		res->children[i] = Tree_CopyRec(node->children[i], dataCopy);
	}

	return res;
}

Tree* Tree_Copy(Tree* tree, void* (*funcCopy)(void*))
{
	if (!tree) return NULL;

	Tree* res = (Tree*)calloc(1, sizeof(Tree));
	assert(res);

	res->root = Tree_CopyRec(tree->root, funcCopy);
	res->score = tree->score;

	return res;
}

void Tree_DestroyRec(TreeNode* node, void* (*funcDestroy)(void*))
{
	if (!node) return;

	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		Tree_DestroyRec(node->children[i], funcDestroy);
	}

	if (funcDestroy)
	{
		funcDestroy(node->value);
	}

	free(node);
}

void Tree_Destroy(Tree* tree, void* (*funcDestroy)(void*))
{
	if (!tree) return;

	Tree_DestroyRec(tree->root, funcDestroy);
	free(tree);
}

void Tree_PrintRec(TreeNode* node, void (*funcPrint)(void*), int depth)
{
	if (!node) return;

	for (int i = 0; i < depth; i++)
	{
		putchar('\t');
	}

	funcPrint(node->value);

	putchar('\n');

	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		Tree_PrintRec(node->children[i], funcPrint, depth + 1);
	}
}

void Tree_Print(Tree* tree, void (*funcPrint)(void*))
{
	/*int treeSize = Tree_GetSize(tree);

	printf("Tree (size=%d) : \n", treeSize);*/

	Tree_PrintRec(tree->root, funcPrint, 0);
}

int Tree_GetSizeRec(TreeNode* node)
{
	if (!node) return 0;

	int res = 0;

	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		res += Tree_GetSizeRec(node->children[i]);
	}

	return (res + 1);
}

int Tree_GetSize(Tree* tree)
{
	return Tree_GetSizeRec(tree->root);
}

TreeNode* Tree_GetNodeRec(TreeNode* node, int* index, TreeNode** parent, int* child)
{
	if (!node) return NULL;
	if (*index == 0) return node;

	*index -= 1;
	
	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		*parent = node;
		TreeNode* res = Tree_GetNodeRec(node->children[i], index, parent, child);

		if (res)
		{
			if (*child == -1)
			{
				*child = i;
			}

			return res;
		}
	}

	return NULL;
}

TreeNode* Tree_GetNode(Tree* tree, int index, TreeNode** parent, int* child)
{
	int treeSize = Tree_GetSize(tree);

	assert((0 <= index) && (index < treeSize));

	*parent = NULL;
	*child = -1;

	int i = index;

	return Tree_GetNodeRec(tree->root, &i, parent, child);
}

void Tree_GetNodeListRec(TreeNode* node, void* value, int (*dataCompare)(void*, void*), DList* list)
{
	if (!node) return;

	if (dataCompare(value, node->value) == 0)
	{
		DList_InsertLast(list, node);
	}

	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		Tree_GetNodeListRec(node->children[i], value, dataCompare, list);
	}
}

TreeNode* Tree_GetNodeList(Tree* tree, void* value, int (*dataCompare)(void*, void*))
{
	DList* list = DList_New();

	Tree_GetNodeListRec(tree->root, value, dataCompare, list);

	return list;
}
