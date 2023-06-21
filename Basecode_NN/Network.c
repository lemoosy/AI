#include "Network.h"

Network* Network_Init(void)
{
	Network* net = (Network*)calloc(1, sizeof(Network));
	assert(net);

	net->learningStep = 0.5f;

	return net;
}

void Network_Copy(Network* net)
{
	if (!net) return NULL;

	Network* res = (Network*)calloc(1, sizeof(Network));
	assert(res);

	*res = *net;

	int size = net->size;

	for (int i = 0; i < size; i++)
	{
		res->layers[i] = Layer_Copy(net->layers[i]);
	}

	return res;
}

void Network_Destroy(Network* net)
{
	if (!net) return;

	int size = net->size;

	for (int i = 0; i < size; i++)
	{
		Layer_Destroy(net->layers[i]);
	}

	free(net);
}

Layer* Network_GetLayer(Network* net, int index)
{
	if (index < 0)
	{
		index += net->size;
	}

	assert((0 <= index) && (index < net->size));

	return net->layers[index];
}

void Network_AddLayer(Network* net, int size, float (*activation)(float), float (*activationDer)(float))
{
	assert(net->size < LAYER_PER_NETWORK);

	net->layers[net->size] = Layer_New(size, activation, activationDer);
	net->size += 1;
}

void Network_PrintLayer(Network* net, int index, char var)
{
	if (index < 0)
	{
		index += net->size;
	}

	Layer* layerCurr = Network_GetLayer(net, index);
	int layerCurrSize = layerCurr->size;

	printf("%c : ", var);

	switch (var)
	{
	case 'w':
	{
		assert(index > 0);

		Layer* layerPrev = Network_GetLayer(net, index - 1);
		int layerPrevSize = layerPrev->size;

		for (int j = 0; j < layerCurrSize; j++)
		{
			Node* node = Layer_GetNode(layerCurr, j);

			for (int k = 0; k < layerPrevSize; k++)
			{
				printf("%.2f ", node->w[k]);
			}
		}

		break;
	}

	case 'b':
	{
		for (int j = 0; j < layerCurrSize; j++)
		{
			Node* node = Layer_GetNode(layerCurr, j);

			printf("%.2f ", node->b);
		}

		break;
	}

	case 'z':
	{
		for (int j = 0; j < layerCurrSize; j++)
		{
			Node* node = Layer_GetNode(layerCurr, j);

			printf("%.2f ", node->z);
		}

		break;
	}

	case 'a':
	
		for (int j = 0; j < layerCurrSize; j++)
		{
			Node* node = Layer_GetNode(layerCurr, j);
			printf("%.2f ", node->a);
		}

		break;

	case 'd':

		for (int j = 0; j < layerCurrSize; j++)
		{
			Node* node = Layer_GetNode(layerCurr, j);

			printf("%.2f ", node->d);
		}

		break;

	default:

		printf("ERROR - Network_PrintLayer() \n");
		printf("ERROR - [var=%c] \n", var);
		abort();
		
		break;
	}

	putchar('\n');
}

void Network_Forward(Network* net, float inputs[NODE_PER_LAYER])
{
	Layer* layerInput = Network_GetLayer(net, 0);
	int layerInputSize = layerInput->size;

	for (int j = 0; j < layerInputSize; j++)
	{
		Node* node = Layer_GetNode(layerInput, j);

		node->a = layerInput->activation(inputs[j]);
	}

	int netSize = net->size;

	for (int i = 1; i < netSize; i++)
	{
		Layer* layerCurr = Network_GetLayer(net, i);
		int layerCurrSize = layerCurr->size;

		Layer* layerPrev = Network_GetLayer(net, i - 1);
		int layerPrevSize = layerPrev->size;

		for (int j = 0; j < layerCurrSize; j++)
		{
			Node* nodeCurr = Layer_GetNode(layerCurr, j);

			nodeCurr->z = nodeCurr->b;

			for (int k = 0; k < layerPrevSize; k++)
			{
				Node* nodePrev = Layer_GetNode(layerPrev, k);

				nodeCurr->z += nodePrev->a * nodeCurr->w[k];
			}

			nodeCurr->a = layerCurr->activation(nodeCurr->z);
		}
	}
}

void __Network_InitDelta(Network* net, float outputs[NODE_PER_LAYER])
{
	Layer* layerOutput = Network_GetLayer(net, -1);
	int layerOutputSize = layerOutput->size;

	for (int j = 0; j < layerOutputSize; j++)
	{
		Node* node = Layer_GetNode(layerOutput, j);

		node->d = (node->a - outputs[j]) * layerOutput->activationDer(node->z);
	}

	int netSize = net->size;

	for (int i = netSize - 2; i > 0; i--)
	{
		Layer* layerCurr = Network_GetLayer(net, i);
		int layerCurrSize = layerCurr->size;

		for (int j = 0; j < layerCurrSize; j++)
		{
			Layer* layerNext = Network_GetLayer(net, i + 1);
			int layerNextSize = layerNext->size;

			float sum = 0.0f;

			for (int k = 0; k < layerNextSize; k++)
			{
				Node* nodeNext = Layer_GetNode(layerNext, k);

				sum += nodeNext->w[j] * nodeNext->d;
			}
			
			Node* nodeCurr = Layer_GetNode(layerOutput, j);

			nodeCurr->d = sum * layerCurr->activationDer(nodeCurr->z);
		}
	}
}

void Network_Backward(Network* net, float outputs[NODE_PER_LAYER])
{
	__Network_InitDelta(net, outputs);

	int netSize = net->size;

	for (int i = 1; i < netSize; i++)
	{
		Layer* layerCurr = Network_GetLayer(net, i);
		int layerCurrSize = layerCurr->size;
		
		Layer* layerPrev = Network_GetLayer(net, i - 1);
		int layerPrevSize = layerPrev->size;

		for (int j = 0; j < layerCurrSize; j++)
		{
			Node* nodeCurr = Layer_GetNode(layerCurr, j);

			for (int k = 0; k < layerPrevSize; k++)
			{
				Node* nodePrev = Layer_GetNode(layerPrev, k);

				nodeCurr->w[k] -= net->learningStep * nodeCurr->d * nodePrev->a;
			}
		}
	}
}

void Network_Learning(Network* net, Data* data)
{
	int dataSize = data->size;
	
	int* index = int_tab_random_norep(dataSize);

	for (int _i = 0; _i < dataSize; _i++)
	{
		int i = index[_i];

		Sample sample = data->samples[i];

		Network_Forward(net, sample.x);
		Network_Backward(net, sample.y);
	}
}

bool Network_CkeckError(Network* net, float outputs[NODE_PER_LAYER], float epsilon)
{
	Layer* layerOutput = Network_GetLayer(net, -1);
	int layerOutputSize = layerOutput->size;

	for (int j = 0; j < layerOutputSize; j++)
	{
		Node* nodeOutput = Layer_GetNode(layerOutput, j);

		if (fabsf(nodeOutput->a - outputs[j]) > epsilon)
		{
			return true;
		}
	}

	return false;
}

int Network_CountError(Network* net, Data* data, float epsilon)
{
	int res = 0;

	int dataSize = data->size;

	for (int i = 0; i < dataSize; i++)
	{
		Sample sample = data->samples[i];

		Network_Forward(net, sample.x);

		res += Network_CkeckError(net, sample.y, epsilon);
	}

	return res;
}
