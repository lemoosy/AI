#pragma once

#include "../Settings.h"

// Structure repr�sentant un noeud dans une liste doublement cha�n�e.
typedef struct sDNode
{
	// Valeur du noeud.
	void* value;

	// Pointeur vers le noeud pr�c�dent.
	struct sDNode* prev;

	// Pointeur vers le noeud suivant.
	struct sDNode* next;
}DNode;

// Cr�e un noeud (prev et next sont � NULL).
DNode* DNode_New(void* value);

// Structure repr�sentant une liste doublement cha�n�e.
typedef struct sDList
{
	// Sentinelle.
	DNode* sentinel;

	// Taille de la liste.
	int	size;
}DList;

// Cr�e une liste vide.
DList* DList_New(void);

// Copie une liste.
DList* DList_Copy(DList* list, void* (*funcCopy)(void*));

// D�truit un liste.
void DList_Destroy(DList* list, void (*funcDestroy)(void*));

// Affiche une liste.
void DList_Print(DList* list, void (*funcPrint)(void*));

// V�rifie si une liste est vide.
bool DList_IsEmpty(DList* list);

// V�rifie si une valeur est dans une liste.
bool DList_IsIn(DList* list, void* value, int (*funcCompare)(void*, void*));

// Renvoie la valeur � l'indice <index> dans une liste.
void* DList_Get(DList* list, int index);

// Ins�re une valeur en premier dans une liste.
void DList_InsertFirst(DList* list, void* value);

// Ins�re une valeur en dernier dans une liste.
void DList_InsertLast(DList* list, void* value);

// Ins�re une valeur de mani�re ordonn�e dans une liste.
void DList_InsertSorted(DList* list, void* value, bool reverse, int (*funcCompare)(void*, void*));

// Ins�re une valeur � la position <index> dans une liste.
void DList_InsertBefore(DList* list, void* value, int index);

// Ins�re une valeur � la position <index+1> dans une liste.
void DList_InsertAfter(DList* list, void* value, int index);

// Renvoie la premi�re valeur identique � celle de <value> dans une liste.
void* DList_FirstOf(DList* list, void* value, int (*funcCompare)(void*, void*));

// Renvoie la derni�re valeur identique � celle de <value> dans une liste.
void* DList_LastOf(DList* list, void* value, int (*funcCompare)(void*, void*));

// Retire et renvoie la premi�re valeur dans une liste.
void* DList_PopFirst(DList* list);

// Retire et renvoie la derni�re valeur dans une liste.
void* DList_PopLast(DList* list);


// Retire et renvoie la valeur � l'indice <index> d'une liste.
void* DList_RemoveAt(DList* list, int index);
