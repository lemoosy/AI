#include "Layer.h"

Layer* Layer_New(Layer* layerPrev, int size, FunctionID funcActivationID)
{
	Layer* layer = (Layer*)calloc(1, sizeof(Layer));
	assert(layer);

	layer->size = size;

	if (layerPrev)
	{
		layer->W = Mat_New(layerPrev->size, size);
		layer->B = Mat_New(1, size);

		Mat_Randomize(layer->W, (data)-1, (data)+1, &float_random);
		Mat_Randomize(layer->B, (data)-1, (data)+1, &float_random);
	}

	layer->Z = Mat_New(1, size);
	layer->A = Mat_New(1, size);
	layer->S = Mat_New(1, size);

	layer->funcActivationID = funcActivationID;

	switch (funcActivationID)
	{
	case FUNCTION_LINEAR:
		layer->funcActivation = &linear;
		layer->funcActivationDer = &linearDer;
		break;

	case FUNCTION_SIGMOID:
		layer->funcActivation = &sigmoid;
		layer->funcActivationDer = &sigmoidDer;
		break;

	case FUNCTION_TANH:
		layer->funcActivation = &tanhf;
		layer->funcActivationDer = &tanhfDer;
		break;

	case FUNCTION_RELU:
		layer->funcActivation = &ReLU;
		layer->funcActivationDer = &ReLUDer;
		break;

	case FUNCTION_SOFTMAX:
		layer->funcActivation = &expf;
		layer->funcActivationDer = &linearDer;
		break;

	default:
		printf("ERROR - Layer_New() \n");
		printf("ERROR - [funcActivationID=%d] \n", funcActivationID);
		abort();
		break;
	}

	return layer;
}

Layer* Layer_Copy(Layer* layer)
{
	Layer* res = (Layer*)calloc(1, sizeof(Layer));
	assert(res);

	res->size = layer->size;
	res->W = Mat_Copy(layer->W);
	res->W = Mat_Copy(layer->B);
	res->Z = Mat_Copy(layer->Z);
	res->A = Mat_Copy(layer->A);
	res->S = Mat_Copy(layer->S);
	res->funcActivationID = layer->funcActivationID;
	res->funcActivation = layer->funcActivation;
	res->funcActivationDer = layer->funcActivationDer;

	return res;
}

void Layer_Destroy(Layer* layer)
{
	if (!layer) return;

	Mat_Destroy(layer->S);
	Mat_Destroy(layer->A);
	Mat_Destroy(layer->Z);
	Mat_Destroy(layer->B);
	Mat_Destroy(layer->W);
	free(layer);
}
