#pragma once

#include "Layer.h"
#include "Node.h"
#include "Settings.h"

// Structure représentant un réseau de neurones.
typedef struct sNetwork
{
	// Couches.
	Layer* layers[LAYER_PER_NETWORK];

	// Nombre de couches.
	int layerCount;

	// Pas d'apprentissage (par défaut: 0.5).
	float learningStep;
}Network;

Network* Network_Init(void);
void     Network_Copy(Network* net);
void     Network_Destroy(Network* net);

Layer*   Network_GetLayer(Network* net, int index);
void     Network_AddLayer(Network* net, int nodeCount, float (*activation)(float), float (*activationDer)(float));

void     Network_Forward(Network* net, float inputs[NODE_PER_LAYER]);
void     Network_Backward(Network* net, float outputs[NODE_PER_LAYER]);
