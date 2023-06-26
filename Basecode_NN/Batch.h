#pragma once

#include "Settings.h"
#include "Utils/Mat.h"

// Structure représentant un échantillon.
typedef struct sSample
{
	// Entrées.
	Mat* X;

	// Sorties.
	Mat* Y;
}Sample;

// Structure représentant un jeu de données.
typedef struct sBatch
{
	// Nombre d'échantillons.
	int size;

	// Nombre d'entrées dans chaque échantillon.
	int xSize;

	// Nombre de sorties dans chaque échantillon.
	int ySize;

	// Échantillons.
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

// Importe un jeu de données.
Batch* Batch_Import(char* path);

// Détruit un jeu de données.
void Batch_Destroy(Batch* batch);
