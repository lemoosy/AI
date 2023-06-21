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
	// Nombre d'échantillons.
	int sampleCount;
	
	// Nombre d'entrées dans chaque échantillon.
	int xCount;

	// Nombre de sorties dans chaque échantillon.
	int yCount;
	
	// Échantillons.
	Sample* samples;
}Data;

// ---------- Fichier TXT ----------
// Ligne (0)	Informations
// Ligne (1)	N
// Ligne (2)	xCount yCount
// Ligne (3)	x[0] x[1] x[2] ... x[xCount-1] y[0] y[1] y[2] ... y[yCount-1]
// Ligne (4)	x[0] x[1] x[2] ... x[xCount-1] y[0] y[1] y[2] ... y[yCount-1]
// ...
// Ligne (N+2)	x[0] x[1] x[2] ... x[xCount-1] y[0] y[1] y[2] ... y[yCount-1]
// ---------------------------------

Data* Data_Import(char* path);
void  Data_Destroy(Data* data);
void  Data_Print(Data* data);
