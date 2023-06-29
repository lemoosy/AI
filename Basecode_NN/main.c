//#include "NN/Network.h"
#include "Settings.h"

#ifdef GAME_PG

#include "PG/BTreeAI.h"

int main(void)
{
	srand(time(NULL));

	DList* F[MAX_ARG] = { 0 };
	
	for (int i = 0; i < MAX_ARG; i++)
	{
		F[i] = DList_New();
	}

	DList_InsertLast(F[0], Function_New(FUNCTION_INPUT, calloc(1, sizeof(float))));
	DList_InsertLast(F[0], Function_New(FUNCTION_INPUT, calloc(1, sizeof(float))));

	DList_InsertLast(F[1], Function_New(FUNCTION_SRT, NULL));
	
	DList_InsertLast(F[2], Function_New(FUNCTION_ADD, NULL));
	DList_InsertLast(F[2], Function_New(FUNCTION_SUB, NULL));
	DList_InsertLast(F[2], Function_New(FUNCTION_MUL, NULL));
	DList_InsertLast(F[2], Function_New(FUNCTION_DIV, NULL));

	int populationSize = 100;
	DList* population = DList_New();

	int selectionSize = 10;
	DList* selection = DList_New();

	// Create population:

	for (int i = 0; i < populationSize; i++)
	{
		BTree* tree = BTreeAI_New(F);
		BTreeAI_UpdateScore(tree, F);
		DList_InsertSorted(population, tree, false, &BTreeAI_CompareScore);
	}

	int iterCount = 0;

	while (1)
	{
		// Create selection:

		for (int i = 0; i < selectionSize; i++)
		{
			BTree* tree = (BTree*)DList_PopFirst(population);
			DList_InsertLast(selection, tree);
		}

		// Clear population:

		for (int i = 0; i < populationSize - selectionSize; i++)
		{
			BTree* tree = (BTree*)DList_PopFirst(population);
			BTree_Destroy(tree, NULL);
		}

		// Copy selection x2:

		for (int i = 0; i < selectionSize; i++)
		{
			BTree* tree = (BTree*)DList_Get(selection, i);
			BTree* copy = BTree_Copy(tree, NULL);
			DList_InsertLast(selection, copy);
		}

		// Crossover + Mutation:

		for (int i = 0; i < 3; i++)
		{
			int r1 = int_random(0, selectionSize - 1);
			int r2 = int_random(0, selectionSize - 1);

			BTree* t1 = (BTree*)DList_Get(selection, r1);
			BTree* t2 = (BTree*)DList_Get(selection, r2);

			BTreeAI_Crossover(t1, t2);
			BTreeAI_Mutation(t1, F);
			BTreeAI_Mutation(t2, F);

			BTreeAI_UpdateScore(t1, F);
			BTreeAI_UpdateScore(t2, F);
		}


		// Clear selection:

		for (int i = 0; i < selectionSize * 2; i++)
		{
			BTree* tree = (BTree*)DList_PopFirst(selection);
			DList_InsertSorted(population, tree, false, &BTreeAI_CompareScore);
		}

		// Fill population:

		for (int i = 0; i < populationSize - selectionSize * 2; i++)
		{
			BTree* tree = BTreeAI_New(F);
			BTreeAI_UpdateScore(tree, F);
			DList_InsertSorted(population, tree, false, &BTreeAI_CompareScore);
		}

		// iterCount:

		iterCount += 1;

		printf("iterCount = %d \n", iterCount);

		for (int i = 0; i < 10; i++)
		{
			BTree* tree = DList_Get(population, i);

			if (tree->score == 0.0f)
			{
				BTree_Print(tree, &Function_Print);
				system("pause");
			}
		}
	}


	return EXIT_SUCCESS;
}

#endif

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
