#pragma once

#include "../Settings.h"
#include "../Utils/DList.h"

#define MAX_CHILDREN 3

typedef struct sTreeNode
{
	void* value;
	struct sTreeNode* children[MAX_CHILDREN];
}TreeNode;

typedef struct sTree
{
	TreeNode* root;
	float score;		// for TreeAI.h
}Tree;

Tree*     Tree_New(void);
TreeNode* Tree_CopyRec(TreeNode* node, void* (*dataCopy)(void*));
Tree*     Tree_Copy(Tree* tree, void* (*dataCopy)(void*));
void      Tree_DestroyRec(TreeNode* node, void* (*dataDestroy)(void*));
void      Tree_Destroy(Tree* tree, void* (*dataDestroy)(void*));
void      Tree_Print(Tree* tree, void (*dataPrint)(void*));
int       Tree_GetSize(Tree* tree);
TreeNode* Tree_GetNode(Tree* tree, int index, TreeNode** parent, int* child);
TreeNode* Tree_GetNodeList(Tree* tree, void* value, int (*dataCompare)(void*, void*));
