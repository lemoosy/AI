#pragma once

#include "../Settings.h"
#include "../Utils/DList.h"

/// @brief Nombre d'enfants maximum que possède un noeud.
#define MAX_CHILDREN 3

/// @brief Structure représentant un noeud dans un arbre avec N enfants (sous-arbre).
typedef struct sTreeNode
{
	/// @brief Valeur du noeud.
	void* value;

	/// @brief Nombre de noeuds du sous-arbre.
	int size;

	/// @brief Pointeurs vers les enfants.
	struct sTreeNode* children[MAX_CHILDREN];
}TreeNode;

/// @brief Structure représentant un arbre avec N enfants.
typedef struct sTree
{
	/// @brief Racine de l'arbre.
	TreeNode* root;

	/// @brief Score obtenue par la fonction de fitness (PG).
	float score;
}Tree;

/// @brief Crée un arbre vide.
Tree* Tree_Create(void);

/// @brief Copie un sous arbre.
TreeNode* Tree_CopyRec(TreeNode* node, void* (*dataCopy)(void*));

/// @brief Copie un arbre.
Tree* Tree_Copy(Tree* tree, void* (*dataCopy)(void*));

/// @brief Détruit un sous arbre.
void Tree_DestroyRec(TreeNode* node, void* (*dataDestroy)(void*));

/// @brief Détruit un arbre.
void Tree_Destroy(Tree* tree, void* (*dataDestroy)(void*));

/// @brief Affiche un sous-arbre.
void Tree_PrintRec(TreeNode* node, void (*dataPrint)(void*), int depth);

/// @brief Affiche un arbre.
void Tree_Print(Tree* tree, void (*dataPrint)(void*));

/// @brief Met à jour la taille de chaque noeud d'un sous-arbre.
int Tree_UpdateSizeRec(TreeNode* node);

/// @brief Met à jour la taille de chaque noeud d'un arbre.
int Tree_UpdateSize(Tree* tree);

/// @brief Renvoie la taille d'un arbre.
int Tree_GetSize(Tree* tree);

/// @brief Structure pour les fonctions de recherche.
typedef struct sTreeSearch
{
	/// @brief Noeud.
	TreeNode* node;
	
	/// @brief Parent du noeud.
	TreeNode* parent;

	/// @brief Indice de l'enfant à partir du parent.
	int child;
}TreeSearch;

/// @brief Renvoie à l'indice 'index' le noeud d'un arbre (recherche en profondeur).
TreeSearch* Tree_GetNodeByIndex(Tree* tree, int index);

/// @brief Recherche les noeuds égalent à 'value' d'un arbre.
DList* Tree_GetNodeByValue(Tree* tree, void* value, int (*dataCompare)(void*, void*));
