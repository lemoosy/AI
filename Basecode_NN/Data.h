#pragma once

#include "Settings.h"

#define CHAR_PER_LINE 4096

// Structure représentant un échantillon.
typedef struct sSample
{
	// Entrées.
	float x[NODE_PER_LAYER];

	// Sorties.
	float y[NODE_PER_LAYER];
}Sample;

// Structure représentant un jeu de données.
typedef struct sData
{
	// Informations sur le jeu données.
	char* informations;

	// Nombre d'échantillons.
	int size;
	
	// Nombre d'entrées dans chaque échantillon.
	int xSize;

	// Nombre de sorties dans chaque échantillon.
	int ySize;
	
	// Échantillons.
	Sample* samples;
}Data;

// ---------- Fichier TXT ----------
// Ligne (0)		informations
// Ligne (1)		size
// Ligne (2)		xSize ySize
// Ligne (3)		x[0] x[1] x[2] ... x[xSize-1] y[0] y[1] y[2] ... y[ySize-1]
// Ligne (4)		x[0] x[1] x[2] ... x[xSize-1] y[0] y[1] y[2] ... y[ySize-1]
// ...
// Ligne (size+2)	x[0] x[1] x[2] ... x[xSize-1] y[0] y[1] y[2] ... y[ySize-1]
// ---------------------------------

Data* Data_Import(char* path);
void  Data_Destroy(Data* data);
