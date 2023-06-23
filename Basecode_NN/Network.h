#pragma once

#include "Data.h"
#include "Layer.h"
#include "Node.h"
#include "Settings.h"

// Structure représentant un réseau de neurones.
typedef struct sNetwork
{
	// Couches.
	Layer* layers[LAYER_PER_NETWORK];

	// Nombre de couches.
	int size;

	// Pas d'apprentissage.
	float learningStep;
}Network;

Network* Network_Init(float learningStep);
void     Network_Copy(Network* net);
void     Network_Destroy(Network* net);

Layer*   Network_GetLayer(Network* net, int index);
void     Network_AddLayer(Network* net, int size, FunctionID activationID);
void     Network_PrintLayer(Network* net, int index, char var);

void     Network_Forward(Network* net, float inputs[NODE_PER_LAYER]);
void     Network_Backward(Network* net, float outputs[NODE_PER_LAYER]);

void     Network_Learning(Network* net, Data* data);

bool     Network_CkeckError(Network* net, float outputs[NODE_PER_LAYER], float epsilon);
int      Network_CountError(Network* net, Data* data, float epsilon);
