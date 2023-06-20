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
	// ---------- Première couche ----------

	Layer* layerInput = Network_GetLayer(net, 0);

	int nodeCountInput = layerInput->nodeCount;

	for (int j = 0; j < nodeCountInput; j++)
	{
		Node* node = Layer_GetNode(layerInput, j);

		node->a = inputs[j];
	}

	// ---------- Autres couches ----------

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
