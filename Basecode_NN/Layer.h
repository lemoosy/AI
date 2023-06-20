#pragma once

#include "Node.h"
#include "Settings.h"

// Structure représentant une couche dans un réseau de neurones.
typedef struct sLayer
{
	// Fonction d'activation.
	float (*activation)(float);

	// Dérivée de la fonction d'activation.
	float (*activationDer)(float);

	// Neurones.
	Node* nodes[NODE_PER_LAYER];

	// Nombre de neurones.
	int nodeCount;
}Layer;

Layer* Layer_New(int nodeCount, float (*activation)(float), float (*activationDer)(float));
Layer* Layer_Copy(Layer* layer);
void   Layer_Destroy(Layer* layer);
