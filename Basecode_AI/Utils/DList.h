#pragma once

#include "../Settings.h"

/// @brief Structure repr�sentant un noeud dans une liste doublement cha�n�e.
typedef struct sDNode
{
	/// @brief Valeur du noeud.
	void* value;

	/// @brief Pointeur vers le noeud pr�c�dent.
	struct sDNode* prev;

	/// @brief Pointeur vers le noeud suivant.
	struct sDNode* next;
}DNode;

/// @brief Cr�e un noeud (prev et next sont � NULL).
DNode* DNode_Create(void* value);

/// @brief Structure repr�sentant une liste doublement cha�n�e.
typedef struct sDList
{
	/// @brief Sentinelle.
	DNode* sentinel;

	/// @brief Taille de la liste.
	int size;
}DList;

/// @brief Cr�e une liste vide.
DList* DList_Create(void);

/// @brief Copie une liste.
DList* DList_Copy(DList* list, void* (*dataCopy)(void*));

/// @brief D�truit un liste.
void DList_Destroy(DList* list, void (*dataDestroy)(void*));

/// @brief Affiche une liste.
void DList_Print(DList* list, void (*dataPrint)(void*));

/// @brief V�rifie si une liste est vide.
bool DList_IsEmpty(DList* list);

/// @brief V�rifie si une valeur est dans une liste.
bool DList_IsIn(DList* list, void* value, int (*dataCompare)(void*, void*));

/// @brief Renvoie la valeur � l'indice [index] d'une liste.
void* DList_Get(DList* list, int index);

/// @brief Ins�re une valeur en premier dans une liste.
void DList_InsertFirst(DList* list, void* value);

/// @brief Ins�re une valeur en dernier dans une liste.
void DList_InsertLast(DList* list, void* value);

/// @brief Ins�re une valeur de mani�re ordonn�e dans une liste.
void DList_InsertSorted(DList* list, void* value, bool reverse, int (*dataCompare)(void*, void*));

/// @brief Ins�re une valeur � la position [index] dans une liste.
void DList_InsertBefore(DList* list, void* value, int index);

/// @brief Ins�re une valeur � la position [index+1] dans une liste.
void DList_InsertAfter(DList* list, void* value, int index);

/// @brief Renvoie la premi�re valeur identique � celle de [value] dans une liste.
void* DList_FirstOf(DList* list, void* value, int (*dataCompare)(void*, void*));

/// @brief Renvoie la derni�re valeur identique � celle de [value] dans une liste.
void* DList_LastOf(DList* list, void* value, int (*dataCompare)(void*, void*));

/// @brief Retire et renvoie la premi�re valeur dans une liste.
void* DList_PopFirst(DList* list);

/// @brief Retire et renvoie la derni�re valeur dans une liste.
void* DList_PopLast(DList* list);

/// @brief Retire et renvoie la valeur � l'indice [index] d'une liste.
void* DList_RemoveAt(DList* list, int index);
