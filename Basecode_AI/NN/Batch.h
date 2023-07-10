#pragma once

#include "../Settings.h"
#include "../Utils/Mat.h"

/// @brief Structure représentant un échantillon.
typedef struct sSample
{
	/// @brief Entrées.
	Mat* X;

	/// @brief Sorties.
	Mat* Y;
}Sample;

/// @brief Structure représentant un jeu de données.
typedef struct sBatch
{
	/// @brief Nombre d'échantillons.
	int size;

	/// @brief Nombre d'entrées dans chaque échantillon.
	int xSize;

	/// @brief Nombre de sorties dans chaque échantillon.
	int ySize;

	/// @brief Échantillons.
	Sample* samples;
}Batch;

// ---------- Fichier TXT ----------
// Ligne (1)		size
// Ligne (2)		xSize ySize
// Ligne (3)		x[0] x[1] x[2] ... x[xSize-1] y[0] y[1] y[2] ... y[ySize-1]
// Ligne (4)		x[0] x[1] x[2] ... x[xSize-1] y[0] y[1] y[2] ... y[ySize-1]
// ...
// Ligne (size+2)	x[0] x[1] x[2] ... x[xSize-1] y[0] y[1] y[2] ... y[ySize-1]
// ---------------------------------

/// @brief Importe un jeu de données.
Batch* Batch_Import(char* path);

/// @brief Détruit un jeu de données.
void Batch_Destroy(Batch* batch);
