#pragma once

#include "../Settings.h"

/// @brief Structure représentant un noeud dans une liste doublement chaînée.
typedef struct sDNode
{
	/// @brief Valeur du noeud.
	void* value;

	/// @brief Pointeur vers le noeud précédent.
	struct sDNode* prev;

	/// @brief Pointeur vers le noeud suivant.
	struct sDNode* next;
}DNode;

/// @brief Crée un noeud (prev et next sont à NULL).
DNode* DNode_Create(void* value);

/// @brief Structure représentant une liste doublement chaînée.
typedef struct sDList
{
	/// @brief Sentinelle.
	DNode* sentinel;

	/// @brief Taille de la liste.
	int size;
}DList;

/// @brief Crée une liste vide.
DList* DList_Create(void);

/// @brief Copie une liste.
DList* DList_Copy(DList* list, void* (*dataCopy)(void*));

/// @brief Détruit un liste.
void DList_Destroy(DList* list, void (*dataDestroy)(void*));

/// @brief Affiche une liste.
void DList_Print(DList* list, void (*dataPrint)(void*));

/// @brief Vérifie si une liste est vide.
bool DList_IsEmpty(DList* list);

/// @brief Vérifie si une valeur est dans une liste.
bool DList_IsIn(DList* list, void* value, int (*dataCompare)(void*, void*));

/// @brief Renvoie la valeur à l'indice [index] d'une liste.
void* DList_Get(DList* list, int index);

/// @brief Insère une valeur en premier dans une liste.
void DList_InsertFirst(DList* list, void* value);

/// @brief Insère une valeur en dernier dans une liste.
void DList_InsertLast(DList* list, void* value);

/// @brief Insère une valeur de manière ordonnée dans une liste.
void DList_InsertSorted(DList* list, void* value, bool reverse, int (*dataCompare)(void*, void*));

/// @brief Insère une valeur à la position [index] dans une liste.
void DList_InsertBefore(DList* list, void* value, int index);

/// @brief Insère une valeur à la position [index+1] dans une liste.
void DList_InsertAfter(DList* list, void* value, int index);

/// @brief Renvoie la première valeur identique à celle de [value] dans une liste.
void* DList_FirstOf(DList* list, void* value, int (*dataCompare)(void*, void*));

/// @brief Renvoie la dernière valeur identique à celle de [value] dans une liste.
void* DList_LastOf(DList* list, void* value, int (*dataCompare)(void*, void*));

/// @brief Retire et renvoie la première valeur dans une liste.
void* DList_PopFirst(DList* list);

/// @brief Retire et renvoie la dernière valeur dans une liste.
void* DList_PopLast(DList* list);

/// @brief Retire et renvoie la valeur à l'indice [index] d'une liste.
void* DList_RemoveAt(DList* list, int index);
