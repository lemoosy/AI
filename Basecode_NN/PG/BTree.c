#include "BTree.h"

BTree* BTree_New(void)
{
	BTree* tree = (BTree*)calloc(1, sizeof(BTree));
	assert(tree);

	return tree;
}

BTreeNode* BTree_CopyRec(BTreeNode* node, void* (*funcCopy)(void*))
{
	if (!node) return NULL;

	BTreeNode* res = (BTreeNode*)calloc(1, sizeof(BTreeNode));
	assert(res);

	if (funcCopy) res->value = funcCopy(node->value);
	else res->value = node->value;

	res->left = BTree_CopyRec(node->left, funcCopy);
	res->right = BTree_CopyRec(node->right, funcCopy);

	return res;
}

BTree* BTree_Copy(BTree* tree, void* (*funcCopy)(void*))
{
	if (!tree) return NULL;

	BTree* res = (BTree*)calloc(1, sizeof(BTree));
	assert(res);

	res->root = BTree_CopyRec(tree->root, funcCopy);
	res->score = tree->score;

	return res;
}

void BTree_DestroyRec(BTreeNode* node, void* (*funcDestroy)(void*))
{
	if (!node) return;

	BTree_DestroyRec(node->left, funcDestroy);
	BTree_DestroyRec(node->right, funcDestroy);

	if (funcDestroy) funcDestroy(node->value);
	free(node);
}

void BTree_Destroy(BTree* tree, void* (*funcDestroy)(void*))
{
	if (!tree) return;

	BTree_DestroyRec(tree->root, funcDestroy);
	free(tree);
}

int BTree_GetSizeRec(BTreeNode* node)
{
	if (!node) return 0;

	return (BTree_GetSizeRec(node->left) + BTree_GetSizeRec(node->right) + 1);
}

int BTree_GetSize(BTree* tree)
{
	return BTree_GetSizeRec(tree->root);
}

void BTree_PrintRec(BTreeNode* node, void (*funcPrint)(void*), int w)
{
	if (!node) return;

	int space = 5;

	w += space;

	BTree_PrintRec(node->right, funcPrint, w);

	printf("\n");

	for (int i = space; i < w; i++)
	{
		putchar(' ');
	}

	funcPrint(node->value);

	BTree_PrintRec(node->left, funcPrint, w);
}

void BTree_Print(BTree* tree, void (*funcPrint)(void*))
{
	BTree_PrintRec(tree->root, funcPrint, 10);
	putchar('\n');
}

BTreeNode* BTree_GetNodeRec(BTreeNode* node, int* index, BTreeNode** parent)
{
	if (!node) return NULL;

	if (*index == 0) return node;

	*index -= 1;

	*parent = node;
	BTreeNode* res = BTree_GetNodeRec(node->left, index, parent);

	if (res)
	{
		return res;
	}
	else
	{
		*parent = node;
		return BTree_GetNodeRec(node->right, index, parent);
	}
}

BTreeNode* BTree_GetNode(BTree* tree, int index, BTreeNode** parent)
{
	int size = BTree_GetSize(tree);

	assert((0 <= index) && (index < size));

	*parent = NULL;

	return BTree_GetNodeRec(tree->root, &index, parent);
}
