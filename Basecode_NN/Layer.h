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
	int size;
}Layer;

Layer* Layer_New(int size, float (*activation)(float), float (*activationDer)(float));
Layer* Layer_Copy(Layer* layer);
void   Layer_Destroy(Layer* layer);

Node*  Layer_GetNode(Layer* layer, int index);
