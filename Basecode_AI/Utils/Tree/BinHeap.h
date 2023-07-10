#pragma once

#include "../../Settings.h"
#include "../Type/Void.h"

// URL: https://fr.wikipedia.org/wiki/Tas_binaire

/// @brief Structure représentant un tas binaire.
typedef struct sBinHeap
{
	/// @brief Indique si le tas binaire est un minimum ou un maximum.
	bool minimum;

	/// @brief Liste.
	void** values;

	/// @brief Taille actuelle de la liste.
	int size;

	/// @brief Taille maximale de la liste.
	int capacity;
}BinHeap;

/// @brief Crée un tas binaire vide.
BinHeap* BinHeap_Create(bool minimum, int capacity);

/// @brief Détruit un tas binaire.
void BinHeap_Destroy(BinHeap* heap, void (*dataDestroy)(void*));

/// @brief Affiche un tas binaire.
void BinHeap_Print(BinHeap* heap, void (*dataPrint)(void*));

/// @brief Insère une valeur dans un tas binaire en O(logN).
void BinHeap_Insert(BinHeap* heap, void* value, int (*dataCompare)(void*, void*));

/// @brief Retire et renvoie le premier élément (la racine) d'un tas binaire en O(logN).
void* BinHeap_PopFirst(BinHeap* heap, int (*dataCompare)(void*, void*));
