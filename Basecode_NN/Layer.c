#include "Layer.h"

Layer* Layer_New(int nodeCount, float (*activation)(float), float (*activationDer)(float))
{
	Layer* layer = (Layer*)calloc(1, sizeof(Layer));
	assert(layer);

	layer->activation = activation;
	layer->activationDer = activationDer;

	for (int j = 0; j < nodeCount; j++)
	{
		layer->nodes[j] = Node_New();
	}

	layer->nodeCount = nodeCount;

	return layer;
}

Layer* Layer_Copy(Layer* layer)
{
	if (!layer) return NULL;

	Layer* res = (Layer*)calloc(1, sizeof(Layer));
	assert(res);

	*res = *layer;

	int nodeCount = layer->nodeCount;

	for (int j = 0; j < nodeCount; j++)
	{
		res->nodes[j] = Node_Copy(layer->nodes[j]);
	}

	return res;
}

void Layer_Destroy(Layer* layer)
{
	if (!layer) return;

	int nodeCount = layer->nodeCount;

	for (int j = 0; j < nodeCount; j++)
	{
		Node_Destroy(layer->nodes[j]);
	}

	free(layer);
}

Node* Layer_GetNode(Layer* layer, int index)
{
	if (index < 0)
	{
		index += layer->nodeCount;
	}

	assert((0 <= index) && (index < layer->nodeCount));

	return layer->nodes[index];
}
