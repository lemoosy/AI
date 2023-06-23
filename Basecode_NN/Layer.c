#include "Layer.h"

void __Layer_InitFunctions(Layer* layer, FunctionID activationID)
{
	layer->activationID = activationID;

	switch (activationID)
	{
	case FUNCTION_LINEAR:
		layer->activation = &linear;
		layer->activationDer = &linearDer;
		break;

	case FUNCTION_SIGMOID:
		layer->activation = &sigmoid;
		layer->activationDer = &sigmoidDer;
		break;

	case FUNCTION_TANH:
		layer->activation = &tanhf;
		layer->activationDer = &tanhfDer;
		break;

	case FUNCTION_RELU:
		layer->activation = &ReLU;
		layer->activationDer = &ReLUDer;
		break;

	case FUNCTION_SOFTMAX:
		layer->activation = &linear;
		layer->activationDer = &linearDer;
		break;

	default:
		printf("ERROR - __Layer_InitFunctions() \n");
		printf("ERROR - [activationID=%d] \n", activationID);
		abort();
		break;
	}
}

Layer* Layer_New(int size, FunctionID activationID)
{
	Layer* layer = (Layer*)calloc(1, sizeof(Layer));
	assert(layer);

	__Layer_InitFunctions(layer, activationID);

	layer->size = size;

	for (int j = 0; j < size; j++)
	{
		layer->nodes[j] = Node_New();
	}

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

void Layer_AddNode(Layer* layer, Node* node)
{
	assert(layer->size < NODE_PER_LAYER);

	layer->nodes[layer->size] = node;
	layer->size += 1;
}

void Layer_ExportBin(Layer* layer, FILE* file)
{
	fwrite(&(layer->activationID), sizeof(int), 1, file);

	int size = layer->size;

	fwrite(size, sizeof(int), 1, file);

	for (int j = 0; j < size; j++)
	{
		Node* node = Layer_GetNode(layer, j);

		Node_ExportBin(node, file);
	}
}

Layer* Layer_ImportBin(FILE* file)
{
	Layer* layer = (Layer*)calloc(1, sizeof(Layer));
	assert(layer);

	FunctionID activationID = 0;
	fread(&activationID, sizeof(int), 1, file);

	__Layer_InitFunctions(layer, activationID);

	int size = 0;
	fread(&size, sizeof(int), 1, file);

	for (int j = 0; j < size; j++)
	{
		Node* node = Node_ImportBin(file);

		Layer_AddNode(layer, node);
	}






	return layer;
}
