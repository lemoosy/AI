#include "Layer.h"

Layer* Layer_New(int size, float (*activation)(float), float (*activationDer)(float))
{
	Layer* layer = (Layer*)calloc(1, sizeof(Layer));
	assert(layer);

	layer->activation = activation;
	layer->activationDer = activationDer;

	for (int j = 0; j < size; j++)
	{
		layer->nodes[j] = Node_New();
	}

	layer->size = size;

	return layer;
}

Layer* Layer_Copy(Layer* layer)
{
	if (!layer) return NULL;

	Layer* res = (Layer*)calloc(1, sizeof(Layer));
	assert(res);

	*res = *layer;

	int size = layer->size;

	for (int j = 0; j < size; j++)
	{
		res->nodes[j] = Node_Copy(layer->nodes[j]);
	}

	return res;
}

void Layer_Destroy(Layer* layer)
{
	if (!layer) return;

	int size = layer->size;

	for (int j = 0; j < size; j++)
	{
		Node_Destroy(layer->nodes[j]);
	}

	free(layer);
}

Node* Layer_GetNode(Layer* layer, int index)
{
	if (index < 0)
	{
		index += layer->size;
	}

	assert((0 <= index) && (index < layer->size));

	return layer->nodes[index];
}
