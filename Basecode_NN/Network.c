#include "Network.h"

Network* Network_New(float learningStep)
{
	Network* net = (Network*)calloc(1, sizeof(Network));
	assert(net);

	net->layers = DList_New();
	net->learningStep = learningStep;

	return net;
}

Network* Network_Copy(Network* net)
{
	if (!net) return NULL;

	Network* res = (Network*)calloc(1, sizeof(Network));
	assert(res);

	res->layers = DList_Copy(net->layers, &Layer_Copy);
	res->learningStep = net->learningStep;

	return res;
}

void Network_Destroy(Network* net)
{
	if (!net) return;

	DList_Destroy(net->layers, &Layer_Destroy);
	free(net);
}

void Network_AddLayer(Network* net, int size, FunctionID funcActivationID)
{
	Layer* layerEnd = NULL;

	if (!DList_IsEmpty(net->layers))
	{
		layerEnd = DList_Get(net->layers, -1);
	}

	Layer* layerAdd = Layer_New(layerEnd, size, funcActivationID);

	DList_InsertLast(net->layers, layerAdd);
}

void Network_PrintLayer(Network* net, int index, char var)
{
	printf("---------- Network_PrintLayer() { index=%d ; var=%c } ---------- \n\n ", index, var);

	Layer* layer = DList_Get(net->layers, index);

	switch (var)
	{
	case 'W':
		Mat_Print(layer->W);
		break;

	case 'B':
		Mat_Print(layer->B);
		break;

	case 'Z':
		Mat_Print(layer->Z);
		break;

	case 'A':
		Mat_Print(layer->A);
		break;

	default:
		printf("ERROR - Network_PrintLayer() \n");
		printf("ERROR - [var=%c] \n", var);
		abort();
		break;
	}

	putchar('\n');
}

void Network_Forward(Network* net, Mat* inputs)
{
	DNode* nodeSent = net->layers->sentinel;
	DNode* nodePrev = nodeSent->next;
	DNode* nodeCurr = nodePrev->next;

	Layer* layerPrev = (Layer*)nodePrev->value;
	Layer* layerCurr;

	Mat_Copy2(inputs, layerPrev->A);
	Mat_Compose(layerPrev->A, layerPrev->funcActivation);

	while (nodeCurr != nodeSent)
	{
		layerPrev = (Layer*)nodePrev->value;
		layerCurr = (Layer*)nodeCurr->value;

		Mat_Multiply2(layerCurr->W, layerPrev->A, layerCurr->Z);
		Mat_Operation(layerCurr->Z, layerCurr->B, &Data_Add);
		Mat_Compose2(layerCurr->Z, layerCurr->funcActivation, layerCurr->A);

		nodePrev = nodeCurr;
		nodeCurr = nodeCurr->next;
	}
}

void __Network_InitDelta(Network* net, Mat* outputs)
{
	DNode* nodeSent = net->layers->sentinel;
	DNode* nodeNext = nodeSent->prev;
	DNode* nodeCurr = nodeNext->prev;

	Layer* layerNext = (Layer*)nodeNext->value;
	Layer* layerCurr;

	Mat_Copy2(layerNext->A, layerNext->S);
	Mat_Operation(layerNext->S, outputs, &Data_Sub);
	Mat_Compose(layerNext->Z, layerNext->funcActivationDer);
	Mat_Operation(layerNext->S, layerNext->Z, &Data_Multiply);

	while (nodeCurr != nodeSent->next)
	{
		layerNext = (Layer*)nodeNext->value;
		layerCurr = (Layer*)nodeCurr->value;

		// todo opti

		Mat* W_T = Mat_Transpose(layerNext->W);
		Mat* S_L = Mat_Multiply(W_T, layerNext->S);

		Mat_Compose(layerCurr->Z, layerCurr->funcActivationDer);
		Mat_Operation(S_L, layerCurr->Z, &Data_Multiply);
		Mat_Copy2(S_L, layerCurr->S);

		Mat_Destroy(S_L);
		Mat_Destroy(W_T);

		nodeNext = nodeCurr;
		nodeCurr = nodeCurr->prev;
	}
}

void Network_Backward(Network* net, Mat* outputs)
{
	__Network_InitDelta(net, outputs);

	DNode* nodeSent = net->layers->sentinel;
	DNode* nodeNext = nodeSent->prev;
	DNode* nodeCurr = nodeNext->prev;

	Layer* layerNext = (Layer*)nodeNext->value;
	Layer* layerCurr;

	data learningStep = net->learningStep;

	while (nodeCurr != nodeSent->next)
	{
		layerNext = (Layer*)nodeNext->value;
		layerCurr = (Layer*)nodeCurr->value;

		Mat* A_T = Mat_Transpose(layerCurr->A);
		Mat* der = Mat_Multiply(layerNext->S, A_T);
		
		Mat_Scale(der, learningStep);
		Mat_Operation(layerNext->W, der, &Data_Sub);
		
		nodeNext = nodeCurr;
		nodeCurr = nodeCurr->prev;
	}
}

void Network_Learning(Network* net, Batch* batch)
{
	int size = batch->size;
	int xSize = batch->xSize;
	int ySize = batch->ySize;
	
	int* index = int_tab_random_norep(size);

	Mat* X = Mat_New(1, xSize);
	Mat* Y = Mat_New(1, ySize);

	for (int _ = 0; _ < size; _++)
	{
		int i = index[_];

		Sample sample = batch->samples[i];

		memcpy(X->values, sample.x, sizeof(data) * xSize);
		memcpy(Y->values, sample.y, sizeof(data) * ySize);

		Network_Forward(net, X);
		Network_Backward(net, Y);
	}
}

int Network_CountError(Network* net, Batch* batch, data epsilon)
{
	int res = 0;

	int size = batch->size;
	int xSize = batch->xSize;
	int ySize = batch->ySize;

	Mat* X = Mat_New(1, xSize);
	Mat* Y = Mat_New(1, ySize);

	for (int i = 0; i < size; i++)
	{
		Sample sample = batch->samples[i];

		memcpy(X->values, sample.x, sizeof(data) * xSize);
		memcpy(Y->values, sample.y, sizeof(data) * ySize);

		Network_Forward(net, X);

		Layer* layerOutput = (Layer*)DList_Get(net->layers, -1);

		res += !Mat_Equal(layerOutput->A, Y, 0.1f);
	}

	return res;
}
