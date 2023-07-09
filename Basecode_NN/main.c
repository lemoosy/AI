#include "Settings.h"

#ifdef GAME_SNAKE

#include "PG/Function.h"
#include "PG/Tree.h"
#include "PG/TreeAI.h"
#include "SDL/Window.h"
#include "Snake/Snake.h"
#include "Utils/DList.h"
#include "Utils/Utils.h"

int main(void)
{
	Settings_Init();

	// #####################
	// ##### Fonctions #####
	// #####################

	DList* functions = DList_Create();

	DList_InsertLast(functions, Function_Create("__Snake_SetDirectionN", 0, &__Snake_SetDirectionN, TYPE_NULL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_SetDirectionS", 0, &__Snake_SetDirectionS, TYPE_NULL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_SetDirectionW", 0, &__Snake_SetDirectionW, TYPE_NULL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_SetDirectionE", 0, &__Snake_SetDirectionE, TYPE_NULL, (TypeID[]) { 0 }));

	DList_InsertLast(functions, Function_Create("__Snake_HeadBodyN", 0, &__Snake_HeadBodyN, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_HeadBodyS", 0, &__Snake_HeadBodyS, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_HeadBodyW", 0, &__Snake_HeadBodyW, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_HeadBodyE", 0, &__Snake_HeadBodyE, TYPE_BOOL, (TypeID[]) { 0 }));

	DList_InsertLast(functions, Function_Create("__Snake_HeadWallN", 0, &__Snake_HeadWallN, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_HeadWallS", 0, &__Snake_HeadWallS, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_HeadWallW", 0, &__Snake_HeadWallW, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_HeadWallE", 0, &__Snake_HeadWallE, TYPE_BOOL, (TypeID[]) { 0 }));

	DList_InsertLast(functions, Function_Create("__Snake_DirectionHeadIsN", 0, &__Snake_DirectionHeadIsN, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_DirectionHeadIsS", 0, &__Snake_DirectionHeadIsS, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_DirectionHeadIsW", 0, &__Snake_DirectionHeadIsW, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_DirectionHeadIsE", 0, &__Snake_DirectionHeadIsE,	TYPE_BOOL, (TypeID[]) { 0 }));
	
	DList_InsertLast(functions, Function_Create("__Snake_AheadFood", 0, &__Snake_AheadFood, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_AheadBody", 0, &__Snake_AheadBody, TYPE_BOOL, (TypeID[]) { 0 }));
	DList_InsertLast(functions, Function_Create("__Snake_AheadWall2", 0, &__Snake_AheadWall2, TYPE_BOOL, (TypeID[]) { 0 }));
	
	DList_InsertLast(functions, Function_Create("PROGN2", 2, &__progn, TYPE_NULL, (TypeID[]) { TYPE_NULL, TYPE_NULL }));
	DList_InsertLast(functions, Function_Create("NOT", 1, &__not, TYPE_BOOL, (TypeID[]) { TYPE_BOOL }));
	DList_InsertLast(functions, Function_Create("AND", 2, &__and, TYPE_BOOL, (TypeID[]) { TYPE_BOOL, TYPE_BOOL }));
	DList_InsertLast(functions, Function_Create("OR", 2, &__or, TYPE_BOOL, (TypeID[]) { TYPE_BOOL, TYPE_BOOL }));
	DList_InsertLast(functions, Function_Create("IF", 3, &__if, TYPE_NULL, (TypeID[]) { TYPE_BOOL, TYPE_NULL, TYPE_NULL }));

	// Création du tableau 2D de toutes les fonctions (* est un DList):
	//
	//				-----------------
	//				| 0 | 1 | 2 | 3 | ... | MAX_ARG + 1 |
	//				-----------------
	// TYPE_NULL	| * | * | * | * |
	//				-----------------
	// TYPE_BOOL	| * | * | * | * |
	//				-----------------
	// TYPE_REAL	| * | * | * | * |
	//				-----------------
	// TYPE_COUNT

	DList*** F = (DList***)calloc(TYPE_COUNT, sizeof(DList**));
	assert(F);

	for (int j = 0; j < TYPE_COUNT; j++)
	{
		F[j] = (DList**)calloc(MAX_ARG + 1, sizeof(DList*));
		assert(F[j]);

		for (int i = 0; i < MAX_ARG + 1; i++)
		{
			F[j][i] = DList_Create();
		}
	}

	while (functions->size > 0)
	{
		Function* function = (Function*)DList_PopFirst(functions);
		DList_InsertLast(F[function->res][function->size], function);
	}

	DList_Destroy(functions, NULL);

	// ######################
	// ##### Paramètres #####
	// ######################
	
	int populationSize	=	5000;
	int selectionSize	=	500;
	int childrenSize	=	1000;
	int generationMod	=	10;
	int scoreEnd		=	100;

	TypeID res			=	TYPE_NULL;

	// ##############
	// ##### PG #####
	// ##############

	assert(childrenSize % 2 == 0);

	DList* population = DList_Create();
	DList* selection = DList_Create();

	int generation = 0;
	int scoreMax = 0;

	while (1)
	{
		// Remplissage de la population.

		int size = populationSize - population->size;

		for (int i = 0; i < size; i++)
		{
			Tree* tree = TreeAI_Create(F, res, MAX_DEPTH);
			__Snake_Fitness(tree, NULL);
			scoreMax = max(scoreMax, tree->score);
			DList_InsertLast(population, tree);
		}

		if (scoreMax >= scoreEnd) break;

		// Affichage des 5 meilleurs.

		generation += 1;

		if (generation % generationMod == 0)
		{
			printf("__________ Generation (%d) __________ \n\n", generation);

			printf("scoreMax = %d \n\n", scoreMax);

			for (int i = 0; i < 5; i++)
			{
				Tree* tree = DList_Get(population, i);

				printf("%d) treeSize = %.3d | score = %.2f \n", i, Tree_GetSize(tree), tree->score);
			}

			putchar('\n');
		}

		// On déplace les meilleurs dans la sélection.

		for (int i = 0; i < selectionSize; i++)
		{
			Tree* tree = (Tree*)DList_PopFirst(population);
			DList_InsertLast(selection, tree);
		}

		// On supprime les individus mauvais dans la population.

		for (int i = 0; i < populationSize - selectionSize; i++)
		{
			Tree* tree = (Tree*)DList_PopFirst(population);
			Tree_Destroy(tree, NULL);
		}

		// On génère les enfants.

		for (int i = 0; i < childrenSize / 2; i++)
		{
			int r0 = int_random(0, selectionSize - 1);
			int r1 = int_random(0, selectionSize - 1);

			Tree* parent0 = (Tree*)DList_Get(selection, r0);
			Tree* parent1 = (Tree*)DList_Get(selection, r1);

			Tree* child0 = Tree_Copy(parent0, &Function_Copy);
			Tree* child1 = Tree_Copy(parent1, &Function_Copy);

			TreeAI_Crossover(child0, child1);

			TreeAI_Mutation(child0, F);
			TreeAI_Mutation(child1, F);

			DList_InsertLast(selection, child0);
			DList_InsertLast(selection, child1);
		}

		// On déplace les enfants ainsi que les sélectionnés dans la population.

		size = selectionSize + childrenSize;

		for (int i = 0; i < size; i++)
		{
			Tree* tree = (Tree*)DList_PopFirst(selection);
			__Snake_Fitness(tree, NULL);
			scoreMax = max(scoreMax, tree->score);
			DList_InsertSorted(population, tree, false, &TreeAI_CompareScore);
		}
	}

	Tree* treeBest = (Tree*)DList_Get(population, 0);
	Tree_Print(treeBest, &Function_Print);
	Window* window = Window_Create("Snake 2023 - PG - LEMOOSY");
	__Snake_Fitness(treeBest, window);
	Window_Destroy(window);

	// ###################
	// ##### Mémoire #####
	// ###################

	for (int i = 0; i < populationSize; i++)
	{
		Tree* tree = (Tree*)DList_PopFirst(population);
		Tree_Destroy(tree, NULL);
	}

	DList_Destroy(selection, NULL);
	DList_Destroy(population, NULL);

	for (int j = 0; j < TYPE_COUNT; j++)
	{
		for (int i = 0; i < MAX_ARG + 1; i++)
		{
			DList_Destroy(F[j][i], &Function_Destroy);
		}
	}

	Settings_Quit();

	return EXIT_SUCCESS;
}

#endif // GAME_SNAKE

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
