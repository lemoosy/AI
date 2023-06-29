#pragma once

#include "../Settings.h"

typedef struct sBTreeNode
{
	void* value;
	struct sBTreeNode* left;
	struct sBTreeNode* right;
}BTreeNode;

typedef struct sBTree
{
	BTreeNode* root;
	float score; // PG
}BTree;

BTree*     BTree_New(void);
BTree*     BTree_Copy(BTree* tree, void* (*funcCopy)(void*));
void       BTree_Destroy(BTree* tree, void* (*funcDestroy)(void*));

void       BTree_Print(BTree* tree, void (*funcPrint)(void*));

int        BTree_GetSize(BTree* tree);
BTreeNode* BTree_GetNode(BTree* tree, int index, BTreeNode** parent);
