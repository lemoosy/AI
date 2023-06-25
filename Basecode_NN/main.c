#include "Network.h"
#include "Settings.h"

void Check_Print(Network* net, Batch* data)
{
	int dataSize = data->size;

	for (int i = 0; i < dataSize; i++)
	{
		Sample sample = data->samples[i];

		Network_Forward(net, sample.x);

		printf("%.2f %.2f %.2f | ", sample.y[0], sample.y[1], sample.y[2]);
		Network_PrintLayer(net, -1, 'a');
	}

	putchar('\n');
}

int main(void)
{
	srand(time(NULL));

	Batch* batch = Batch_Import("../Data/iris.txt");

	Network* net = Network_New(0.1f);
	Network_AddLayer(net, batch->xSize, FUNCTION_LINEAR);
	Network_AddLayer(net, 3, FUNCTION_SIGMOID);
	Network_AddLayer(net, batch->ySize, FUNCTION_SIGMOID);

	Network_PrintLayer(net, 0, 'A');
	Network_PrintLayer(net, 1, 'A');
	Network_PrintLayer(net, 2, 'A');

	for (int i = 0; i < 300; i++)
	{
		Network_Learning(net, batch);
		int res = Network_CountError(net, batch, 0.1f);
		printf("res = %d \n", res);
	}



	return EXIT_SUCCESS;
}
