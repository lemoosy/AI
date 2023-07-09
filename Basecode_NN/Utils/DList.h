#pragma once

#include "../Settings.h"

// Structure représentant un noeud dans une liste doublement chaînée.
typedef struct sDNode
{
	// Valeur du noeud.
	void* value;

	// Pointeur vers le noeud précédent.
	struct sDNode* prev;

	// Pointeur vers le noeud suivant.
	struct sDNode* next;
}DNode;

// Crée un noeud (prev et next sont à NULL).
DNode* DNode_New(void* value);

// Structure représentant une liste doublement chaînée.
typedef struct sDList
{
	// Sentinelle.
	DNode* sentinel;

	// Taille de la liste.
	int	size;
}DList;

// Crée une liste vide.
DList* DList_Create(void);

// Copie une liste.
DList* DList_Copy(DList* list, void* (*funcCopy)(void*));

// Détruit un liste.
void DList_Destroy(DList* list, void (*funcDestroy)(void*));

// Affiche une liste.
void DList_Print(DList* list, void (*funcPrint)(void*));

// Vérifie si une liste est vide.
bool DList_IsEmpty(DList* list);

// Vérifie si une valeur est dans une liste.
bool DList_IsIn(DList* list, void* value, int (*funcCompare)(void*, void*));

// Renvoie la valeur à l'indice <index> dans une liste.
void* DList_Get(DList* list, int index);

// Insère une valeur en premier dans une liste.
void DList_InsertFirst(DList* list, void* value);

// Insère une valeur en dernier dans une liste.
void DList_InsertLast(DList* list, void* value);

// Insère une valeur de manière ordonnée dans une liste.
void DList_InsertSorted(DList* list, void* value, bool reverse, int (*funcCompare)(void*, void*));

// Insère une valeur à la position <index> dans une liste.
void DList_InsertBefore(DList* list, void* value, int index);

// Insère une valeur à la position <index+1> dans une liste.
void DList_InsertAfter(DList* list, void* value, int index);

// Renvoie la première valeur identique à celle de <value> dans une liste.
void* DList_FirstOf(DList* list, void* value, int (*funcCompare)(void*, void*));

// Renvoie la dernière valeur identique à celle de <value> dans une liste.
void* DList_LastOf(DList* list, void* value, int (*funcCompare)(void*, void*));

// Retire et renvoie la première valeur dans une liste.
void* DList_PopFirst(DList* list);

// Retire et renvoie la dernière valeur dans une liste.
void* DList_PopLast(DList* list);

// Retire et renvoie la valeur à l'indice <index> d'une liste.
void* DList_RemoveAt(DList* list, int index);

DList* DList_Fusion(DList* l1, DList* l2);
