#pragma once

#include "../Settings.h"
#include "../Utils/DList.h"

#define MAX_CHILDREN 3

// Structure représentant un noeud dans un arbre avec N enfant(s).
typedef struct sTreeNode
{
	// Valeur du noeud.
	void* value;

	// Nombre de noeud du sous-arbre.
	int size;

	// Pointeurs vers les enfants.
	struct sTreeNode* children[MAX_CHILDREN];
}TreeNode;

// Structure représentant un arbre avec N enfant(s).
typedef struct sTree
{
	// Racine de l'arbre.
	TreeNode* root;

	// Variables utilisées pour la programmation génétique.

	int id;			// ID de l'arbre.
	float score;	// Score obtenue par la fonction de fitness.
}Tree;

Tree*     Tree_New(void);
TreeNode* Tree_CopyRec(TreeNode* node, void* (*dataCopy)(void*));
Tree*     Tree_Copy(Tree* tree, void* (*dataCopy)(void*));
void      Tree_DestroyRec(TreeNode* node, void* (*dataDestroy)(void*));
void      Tree_Destroy(Tree* tree, void* (*dataDestroy)(void*));
void      Tree_Print(Tree* tree, void (*dataPrint)(void*));
int       Tree_UpdateSize(Tree* tree);
TreeNode* Tree_GetNode(Tree* tree, int index, TreeNode** parent, int* child);
TreeNode* Tree_GetNodeList(Tree* tree, void* value, int (*dataCompare)(void*, void*));
