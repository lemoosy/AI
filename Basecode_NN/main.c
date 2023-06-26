#include "NN/Network.h"
#include "Settings.h"

void Check_Print(Network* net, Batch* batch)
{
	int batchSize = batch->size;
	
	Mat* X = Mat_New(1, 3);

	for (int i = 0; i < batchSize; i++)
	{
		Sample sample = batch->samples[i];

		Network_Forward(net, sample.X);

		printf("res TXT : \n");
		Mat_Print(sample.Y);

		printf("res NN : \n");
		Layer* layerOutput = DList_Get(net->layers, -1);
		Mat_Print(layerOutput->A);

		putchar('\n');
	}

	putchar('\n');
}

int main(void)
{
	srand(time(NULL));

	Batch* batch = Batch_Import("../Data/iris_softmax.txt");

	Network* net = Network_New(0.1f);

	Network_AddLayer(net, batch->xSize, FUNCTION_LINEAR);
	Network_AddLayer(net, 3, FUNCTION_SIGMOID);
	Network_AddLayer(net, batch->ySize, FUNCTION_SOFTMAX);


	Game*




	for (int i = 0; i < 100; i++)
	{
		Network_Learning(net, batch);
		int res = Network_CountError(net, batch, 0.7f);
	}

	Check_Print(net, batch);
	printf("ERROR = %d \n", Network_CountError(net, batch, 0.1f));

	return EXIT_SUCCESS;
}
