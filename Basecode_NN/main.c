#include "Network.h"
#include "Data.h"
#include "Settings.h"

void Check_Print(Network* net, Data* data)
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

	Data* data = Data_Import("../Data/iris_softmax.txt");

	Network* net = Network_Init(0.1f);
	Network_AddLayer(net, data->xSize, FUNCTION_LINEAR);
	Network_AddLayer(net, 3, FUNCTION_SIGMOID);
	Network_AddLayer(net, data->ySize, FUNCTION_SOFTMAX);

	for (int i = 0; i < 100; i++)
	{
		Network_Learning(net, data);
		int res = Network_CountError(net, data, 0.1f);
		printf("res = %d \n", res);
	}

	Check_Print(net, data);


	Network_Destroy(net);
	Data_Destroy(data);

	return EXIT_SUCCESS;
}
