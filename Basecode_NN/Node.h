#pragma once

#include "Settings.h"
#include "Utils.h"

// Structure représentant un neurone artificiel.
typedef struct sNode
{
	// Poids entrants.
	float w[NODE_PER_LAYER];

	// Biais.
	float b;

	// Valeur de la fonction somme.
	float z;

	// Valeur de la fonction d'activation.
	float a;

	// Valeur intermédiaire.
	float d;
}Node;

Node* Node_New(void);
Node* Node_Copy(Node* node);
void  Node_Destroy(Node* node);

void  Node_ExportBin(Node* node, FILE* file);
Node* Node_ImportBin(FILE* file);
