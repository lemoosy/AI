#include "NN/Network.h"
#include "Settings.h"

#ifdef GAME_ANT

#include "Ant/Game.h"

int main(void)
{
	srand(time(NULL));

	/*Game* game = Game_New();

	while (game->state == GAME_IN_PROGRESS)
	{
		system("cls");
		Game_Print(game);
		Game_Update(game);
		Sleep(500);
	}

	Game_Destroy(game);*/

	main2();

	return EXIT_SUCCESS;
}

#endif // GAME_ANT

#ifdef GAME_CONNECT4

#include "Connect4/Game.h"
#include "Connect4/AI.h"

int main(void)
{
	srand(time(NULL));

	Batch* batch = Batch_Import("../Data/iris_softmax.txt");

	Network* net = Network_New(0.1f);
	Network_AddLayer(net, GRID_W * GRID_H * 2, FUNCTION_LINEAR);
	Network_AddLayer(net, 256, FUNCTION_SIGMOID);
	Network_AddLayer(net, 256, FUNCTION_SIGMOID);
	Network_AddLayer(net, 256, FUNCTION_SIGMOID);
	Network_AddLayer(net, 256, FUNCTION_SIGMOID);
	Network_AddLayer(net, 256, FUNCTION_SIGMOID);
	Network_AddLayer(net, GRID_W, FUNCTION_SOFTMAX);
	
	//Game_MinimaxVSPlayer();
	Game_MinimaxVSNN(net, 20000);

	Batch_Destroy(batch);
	Network_Destroy(net);

	return EXIT_SUCCESS;
}

#endif // GAME_CONNECT4
