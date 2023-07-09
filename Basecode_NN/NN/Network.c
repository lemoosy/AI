#include "Network.h"

Network* Network_New(float learningStep)
{
	Network* net = (Network*)calloc(1, sizeof(Network));
	assert(net);

	net->layers = DList_Create();
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
	printf("---------- Network_PrintLayer() { index=%d ; var=%c } ---------- \n\n", index, var);

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
	Layer* layerCurr = NULL;

	Mat_Copy2(inputs, layerPrev->A);
	Mat_Compose(layerPrev->A, layerPrev->funcActivation);

	while (nodeCurr != nodeSent)
	{
		layerPrev = (Layer*)nodePrev->value;
		layerCurr = (Layer*)nodeCurr->value;

		Mat_Multiply2(layerCurr->W, layerPrev->A, layerCurr->Z);
		Mat_Add(layerCurr->Z, layerCurr->B);
		Mat_Compose2(layerCurr->Z, layerCurr->funcActivation, layerCurr->A);

		nodePrev = nodeCurr;
		nodeCurr = nodeCurr->next;
	}

	if (layerCurr->funcActivationID == FUNCTION_SOFTMAX)
	{
		Mat_Scale(layerCurr->A, 1.0f / Mat_Sum(layerCurr->A));
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
	Mat_Sub(layerNext->S, outputs);

	if (layerNext->funcActivationID != FUNCTION_SOFTMAX)
	{
		Mat_Compose(layerNext->Z, layerNext->funcActivationDer); // Z^(L+1) inutile pour la suite.
		Mat_Product(layerNext->S, layerNext->Z);
	}

	while (nodeCurr != nodeSent)
	{
		layerNext = (Layer*)nodeNext->value;
		layerCurr = (Layer*)nodeCurr->value;

		Mat* W_T = Mat_Transpose(layerNext->W);
		
		Mat_Multiply2(W_T, layerNext->S, layerCurr->S);
		Mat_Compose(layerCurr->Z, layerCurr->funcActivationDer); // Z^(L+1) inutile pour la suite.
		Mat_Product(layerCurr->S, layerCurr->Z);

		Mat_Destroy(W_T);

		nodeNext = nodeCurr;
		nodeCurr = nodeCurr->prev;
	}
}

void Network_Backward(Network* net, Mat* outputs)
{
	__Network_InitDelta(net, outputs);

	DNode* nodeSent = net->layers->sentinel;
	DNode* nodeCurr = nodeSent->prev;
	DNode* nodePrev = nodeCurr->prev;

	Layer* layerCurr = (Layer*)nodeCurr->value;
	Layer* layerPrev;

	data learningStep = net->learningStep;

	Mat* A_T;
	Mat* tmp;

	while (nodePrev != nodeSent)
	{
		layerCurr = (Layer*)nodeCurr->value;
		layerPrev = (Layer*)nodePrev->value;

		Mat_Scale(layerCurr->S, learningStep);	// n * S^i

		A_T = Mat_Transpose(layerPrev->A);
		tmp = Mat_Multiply(layerCurr->S, A_T);	// n * S^i * A^(i-1).T
		Mat_Sub(layerCurr->W, tmp);				// W^i -= n * S^i * A^(i-1).T
		Mat_Sub(layerCurr->B, layerCurr->S);	// B^i -= n * S^i

		Mat_Destroy(tmp);
		Mat_Destroy(A_T);

		nodeCurr = nodePrev;
		nodePrev = nodePrev->prev;
	}
}

void Network_Learning(Network* net, Batch* batch)
{
	int size = batch->size;
	int* index = int_tab_random_norep(size);

	for (int _ = 0; _ < size; _++)
	{
		Sample sample = batch->samples[index[_]];

		Network_Forward(net, sample.X);
		Network_Backward(net, sample.Y);
	}

	free(index);
}

int Network_CountError(Network* net, Batch* batch, data epsilon)
{
	int res = 0;
	int size = batch->size;

	for (int i = 0; i < size; i++)
	{
		Sample sample = batch->samples[i];

		Network_Forward(net, sample.X);

		Layer* layerOutput = (Layer*)DList_Get(net->layers, -1);

		res += !Mat_Equal(layerOutput->A, sample.Y, epsilon);
	}

	return res;
}
