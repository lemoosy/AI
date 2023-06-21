#include "Network.h"
#include "Data.h"
#include "Settings.h"



int main(void)
{
	Data* data = Data_Import("../Data/iris.txt");

	Network* net = Network_Init();
	Network_AddLayer(net, data->xCount, NULL, NULL);
	Network_AddLayer(net, 3, &sigmoid, &sigmoidDer);
	Network_AddLayer(net, data->yCount, &sigmoid, &sigmoidDer);

	






	Network_Destroy(net);
	Data_Destroy(data);

	return EXIT_SUCCESS;
}
