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

		printf("%.2f | ", sample.y[0]);
		Network_PrintLayer(net, -1, 'a');
	}

	putchar('\n');
}

int main(void)
{
	srand(time(NULL));

	Data* data = Data_Import("../Data/iris.txt");

	Network* net = Network_Init();
	Network_AddLayer(net, data->xSize, &linear, NULL);
	Network_AddLayer(net, 3, &sigmoid, &sigmoidDer);
	Network_AddLayer(net, data->ySize, &sigmoid, &sigmoidDer);

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
