#pragma once

#include "Settings.h"
#include "Utils/Data.h"

// Structure repr�sentant un �chantillon.
typedef struct sSample
{
	// Entr�es.
	data* x;

	// Sorties.
	data* y;
}Sample;

// Structure repr�sentant un jeu de donn�es.
typedef struct sBatch
{
	// Nombre d'�chantillons.
	int size;

	// Nombre d'entr�es dans chaque �chantillon.
	int xSize;

	// Nombre de sorties dans chaque �chantillon.
	int ySize;

	// �chantillons.
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

// Importe un jeu de donn�es.
Batch* Batch_Import(char* path);

// D�truit un jeu de donn�es.
void  Batch_Destroy(Batch* data);
