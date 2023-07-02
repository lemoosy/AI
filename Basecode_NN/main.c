//#include "NN/Network.h"
#include "Settings.h"

#ifdef GAME_PG

#include "PG/TreeAI.h"
#include "PG/Function.h"
#include "PG/Ant.h"


int main(void)
{
	srand(time(NULL));

	DList*** F = (DList***)calloc(TYPE_COUNT, sizeof(DList**));
	assert(F);

	for (int j = 0; j < TYPE_COUNT; j++)
	{
		F[j] = (DList**)calloc(MAX_ARG + 1, sizeof(DList*));
		assert(F[j]);

		for (int i = 0; i < MAX_ARG + 1; i++)
		{
			F[j][i] = DList_New();
		}
	}

	in2 = false;

	/*DList_InsertLast(F[TYPE_REAL][0], Function_New("x0", 0, &_in0, TYPE_REAL, (TypeID[]) { 0 }));
	DList_InsertLast(F[TYPE_REAL][0], Function_New("x1", 0, &_in1, TYPE_REAL, (TypeID[]) { 0 }));
	DList_InsertLast(F[TYPE_REAL][1], Function_New("SRT", 1, &_srt, TYPE_REAL, (TypeID[]) { TYPE_REAL }));
	DList_InsertLast(F[TYPE_REAL][2], Function_New("+", 2, &_add, TYPE_REAL, (TypeID[]) { TYPE_REAL, TYPE_REAL }));
	DList_InsertLast(F[TYPE_REAL][2], Function_New("-", 2, &_sub, TYPE_REAL, (TypeID[]) { TYPE_REAL, TYPE_REAL }));
	DList_InsertLast(F[TYPE_REAL][2], Function_New("*", 2, &_mul, TYPE_REAL, (TypeID[]) { TYPE_REAL, TYPE_REAL }));
	DList_InsertLast(F[TYPE_REAL][2], Function_New("/", 2, &_div, TYPE_REAL, (TypeID[]) { TYPE_REAL, TYPE_REAL }));
	DList_InsertLast(F[TYPE_REAL][3], Function_New("IF", 3, &_if, TYPE_REAL, (TypeID[]) { TYPE_BOOL, TYPE_REAL, TYPE_REAL }));*/

	//DList_InsertLast(F[TYPE_BOOL][0], Function_New("b0", 0, &_in2, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(F[TYPE_BOOL][0], Function_New("AheadFood", 0, &Ant_AheadFood, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(F[TYPE_BOOL][1], Function_New("NOT", 1, &_not, TYPE_BOOL, (TypeID[]) { TYPE_BOOL }));
	/*DList_InsertLast(F[TYPE_BOOL][2], Function_New(">", 2, &_sup, TYPE_BOOL, (TypeID[]) { TYPE_REAL, TYPE_REAL }));
	DList_InsertLast(F[TYPE_BOOL][2], Function_New("<", 2, &_inf, TYPE_BOOL, (TypeID[]) { TYPE_REAL, TYPE_REAL }));*/
	DList_InsertLast(F[TYPE_BOOL][2], Function_New("AND", 2, &_and, TYPE_BOOL, (TypeID[]) { TYPE_BOOL, TYPE_BOOL }));
	DList_InsertLast(F[TYPE_BOOL][2], Function_New("OR", 2, &_or, TYPE_BOOL, (TypeID[]) { TYPE_BOOL, TYPE_BOOL }));
	DList_InsertLast(F[TYPE_BOOL][3], Function_New("IF", 3, &_if, TYPE_BOOL, (TypeID[]) { TYPE_BOOL, TYPE_BOOL, TYPE_BOOL }));

	DList_InsertLast(F[TYPE_NONE][0], Function_New("SetDirLeft", 0, &Ant_SetDirectionLeft, TYPE_NONE, (TypeID[]) { 0 }));
	DList_InsertLast(F[TYPE_NONE][0], Function_New("SetDirRight", 0, &Ant_SetDirectionRight, TYPE_NONE, (TypeID[]) { 0 }));
	DList_InsertLast(F[TYPE_NONE][0], Function_New("SetDirUp", 0, &Ant_SetDirectionUp, TYPE_NONE, (TypeID[]) { 0 }));
	DList_InsertLast(F[TYPE_NONE][0], Function_New("SetDirDown", 0, &Ant_SetDirectionDown, TYPE_NONE, (TypeID[]) { 0 }));
	DList_InsertLast(F[TYPE_NONE][0], Function_New("Move", 0, &Ant_Move, TYPE_NONE, (TypeID[]) { 0 }));
	DList_InsertLast(F[TYPE_NONE][2], Function_New("PROGN2", 2, &_progn, TYPE_NONE, (TypeID[]) { TYPE_NONE, TYPE_NONE }));
	DList_InsertLast(F[TYPE_NONE][3], Function_New("PROGN3", 3, &_progn, TYPE_NONE, (TypeID[]) { TYPE_NONE, TYPE_NONE, TYPE_NONE }));
	DList_InsertLast(F[TYPE_NONE][3], Function_New("IF", 3, &_if, TYPE_NONE, (TypeID[]) { TYPE_BOOL, TYPE_NONE, TYPE_NONE }));

	int populationSize = 500;
	DList* population = DList_New();

	int selectionSize = 50;
	DList* selection = DList_New();

	// Create population:

	for (int i = 0; i < populationSize; i++)
	{
		Tree* tree = TreeAI_New(F, TYPE_NONE);
		TreeAI_UpdateScore(tree, false);
		DList_InsertSorted(population, tree, false, &TreeAI_CompareScore);
	}

	int generation = 0;

	while (1)
	{
		// Create selection:

		for (int i = 0; i < selectionSize; i++)
		{
			Tree* tree = (Tree*)DList_PopFirst(population);
			DList_InsertLast(selection, tree);
		}

		// Clear population:

		for (int i = 0; i < populationSize - selectionSize; i++)
		{
			Tree* tree = (Tree*)DList_PopFirst(population);
			Tree_Destroy(tree, NULL);
		}

		// Children:

		for (int i = 0; i < selectionSize; i++)
		{
			Tree* tree = (Tree*)DList_Get(selection, i);
			Tree* copy = Tree_Copy(tree, &Function_Copy);
			DList_InsertLast(selection, copy);
		}

		// Crossover + Mutation:

		for (int i = 0; i < selectionSize; i++)
		{
			int r1 = i;
			int r2 = int_random(selectionSize, selectionSize * 2 - 1);

			Tree* t1 = (Tree*)DList_Get(selection, r1);
			Tree* t2 = (Tree*)DList_Get(selection, r2);

			TreeAI_Crossover(t1, t2);
			//TreeAI_Mutation(t1, F);
			//TreeAI_Permutation(t1);

			TreeAI_UpdateScore(t1, false);
		}

		// Clear selection:

		for (int i = 0; i < selectionSize * 2; i++)
		{
			Tree* tree = (Tree*)DList_PopFirst(selection);
			DList_InsertSorted(population, tree, false, &TreeAI_CompareScore);
		}

		// Fill population:

		for (int i = 0; i < populationSize - selectionSize * 2; i++)
		{
			Tree* tree = TreeAI_New(F, TYPE_NONE);
			TreeAI_UpdateScore(tree, false);
			DList_InsertSorted(population, tree, false, &TreeAI_CompareScore);
		}

		// generation:

		generation += 1;

		printf("\n---------- generation : %d ----------\n\n", generation);

		for (int i = 0; i < 3; i++)
		{
			Tree* tree = DList_Get(population, i);
			printf("score (%d) : %f\n", i, tree->score);

			if (tree->score == 41)
			{
				Tree_Print(tree, &Function_Print);

				system("pause");

				in2 = true;
				TreeAI_UpdateScore(tree, false);
				in2 = false;
				break;
			}
		}
	}

	system("pause");
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
