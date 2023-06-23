#pragma once

#include "Function.h"
#include "Node.h"
#include "Settings.h"

// Structure représentant une couche dans un réseau de neurones.
typedef struct sLayer
{
	// Fonction d'activation.
	float (*activation)(float);

	// Dérivée de la fonction d'activation.
	float (*activationDer)(float);

	// ID de la fonction d'activation.
	FunctionID activationID;

	// Nombre de neurones.
	int size;
	
	// Neurones.
	Node* nodes[NODE_PER_LAYER];
}Layer;

Layer* Layer_New(int size, FunctionID activationID);
Layer* Layer_Copy(Layer* layer);
void   Layer_Destroy(Layer* layer);

Node*  Layer_GetNode(Layer* layer, int index);
void   Layer_AddNode(Layer* layer, Node* node);

void   Layer_ExportBin(Layer* layer, FILE* file);
Layer* Layer_ImportBin(FILE* file);
