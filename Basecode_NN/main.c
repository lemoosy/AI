#include "Network.h"
#include "Data.h"
#include "Settings.h"

int main(void)
{
	srand(time(NULL));

	Data* data = Data_Import("../Data/iris.txt");

	Network* net = Network_Init();
	Network_AddLayer(net, data->xSize, &linear, NULL);
	Network_AddLayer(net, 3, &sigmoid, &sigmoidDer);
	Network_AddLayer(net, data->ySize, &sigmoid, &sigmoidDer);

	while (1)
	{






	}

	Network_Destroy(net);
	Data_Destroy(data);

	return EXIT_SUCCESS;
}
