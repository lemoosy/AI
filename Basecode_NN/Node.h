#pragma once

#include "Settings.h"
#include "Utils.h"

// Structure repr�sentant un neurone artificiel.
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

	// Valeur interm�diaire.
	float d;
}Node;

Node* Node_New(void);
Node* Node_Copy(Node* node);
void  Node_Destroy(Node* node);
