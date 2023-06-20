#include "Network.h"

Network* Network_Init(void)
{
	Network* net = (Network*)calloc(1, sizeof(Network));
	assert(net);

	return net;
}

void Network_Copy(Network* net)
{
	if (!net) return NULL;

	Network* res = (Network*)calloc(1, sizeof(Network));
	assert(res);

	*res = *net;

	int layerCount = net->layerCount;

	for (int i = 0; i < layerCount; i++)
	{
		res->layers[i] = Layer_Copy(net->layers[i]);
	}

	return res;
}

void Network_Destroy(Network* net)
{
	if (!net) return;

	int layerCount = net->layerCount;

	for (int i = 0; i < layerCount; i++)
	{
		Layer_Destroy(net->layers[i]);
	}

	free(net);
}

Layer* Network_GetLayer(Network* net, int index)
{
	if (index < 0)
	{
		index += net->layerCount;
	}

	assert((0 <= index) && (index < net->layerCount));

	return net->layers[index];
}

void Network_AddLayer(Network* net, int nodeCount, float(*activation)(float), float(*activationDer)(float))
{
	assert(net->layerCount < LAYER_PER_NETWORK);

	net->layers[net->layerCount] = Layer_New(nodeCount, activation, activationDer);
	net->layerCount += 1;
}

void Network_Forward(Network* net, float inputs[NODE_PER_LAYER])
{
	// Première couche:

	Layer* layerInput = Network_GetLayer(net, 0);

	int nodeCountInput = layerInput->nodeCount;

	for (int j = 0; j < nodeCountInput; j++)
	{
		Node* node = Layer_GetNode(layerInput, j);

		node->a = inputs[j];
	}

	// Autres couches:

	int layerCount = net->layerCount;

	for (int i = 1; i < layerCount; i++)
	{
		Layer* layerPrev = Network_GetLayer(net, i - 1);
		Layer* layerCurr = Network_GetLayer(net, i);
		
		int nodeCountCurr = layerCurr->nodeCount;
		int nodeCountPrev = layerPrev->nodeCount;

		for (int j = 0; j < nodeCountCurr; j++)
		{
			Node* nodeCurr = Layer_GetNode(layerCurr, j);

			nodeCurr->z = nodeCurr->b;

			for (int k = 0; k < nodeCountPrev; k++)
			{
				Node* nodePrev = Layer_GetNode(layerPrev, k);

				nodeCurr->z += nodePrev->a * nodeCurr->w[k];
			}

			nodeCurr->a = layerCurr->activation(nodeCurr->z);
		}
	}
}

void Network_InitDelta(Network* net, float outputs[NODE_PER_LAYER])
{
	// Dernière couche:

	Layer* layerOutput = Network_GetLayer(net, -1);

	int layerOutputNodeCount = layerOutput->nodeCount;

	for (int j = 0; j < layerOutputNodeCount; j++)
	{
		Node* node = Layer_GetNode(layerOutput, j);

		node->delta = (node->a - outputs[j]) * layerOutput->activationDer(node->z);
	}

	// Autres couches:

	int layerCount = net->layerCount;

	for (int i = layerCount - 2; i > 0; i--)
	{
		Layer* layerCurr = Network_GetLayer(net, i);

		int layerCurrNodeCount = layerCurr->nodeCount;

		for (int j = 0; j < layerCurrNodeCount; j++)
		{
			Node* nodeCurr = Layer_GetNode(layerOutput, j);

			Layer* layerNext = Network_GetLayer(net, i + 1);

			int layerNextNodeCount = layerNext->nodeCount;

			float sum = 0.0f;

			for (int k = 0; k < layerNextNodeCount; k++)
			{
				Node* nodeNext = Layer_GetNode(layerNext, k);

				sum += nodeNext->w[j] * nodeNext->delta;
			}

			nodeCurr->delta = sum * layerOutput->activationDer(nodeCurr->z);
		}
	}
}

void Network_Backward(Network* net, float outputs[NODE_PER_LAYER])
{
	Network_InitDelta(net, outputs);



}
