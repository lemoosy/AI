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

void Network_AddLayer(Network* net, int nodeCount, float(*activation)(float), float(*activationDer)(float))
{
	assert(net->layerCount < LAYER_PER_NETWORK);

	net->layers[net->layerCount] = Layer_New(nodeCount, activation, activationDer);
	net->layerCount += 1;
}

void Network_Forward(Network* net, float inputs[NODE_PER_LAYER])
{

}
