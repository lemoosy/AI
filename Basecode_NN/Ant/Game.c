#include "Game.h"

// ------------------------------ Ant ------------------------------

bool Ant_OutOfDimension(Ant ant)
{
	return ((ant.i < 0) || (ant.j < 0) || (ant.i >= GRID_W) || (ant.j >= GRID_H));
}

void Ant_UpdatePosition(Ant* ant)
{
	if (ant->direction & LEFT)	ant->i -= 1;
	if (ant->direction & RIGHT)	ant->i += 1;
	if (ant->direction & UP)	ant->j -= 1;
	if (ant->direction & DOWN)	ant->j += 1;
}

bool Ant_OnFood(int grid[GRID_H][GRID_W], Ant ant)
{
	return (grid[ant.j][ant.i] == CELL_FOOD);
}

bool Ant_FoodAhead(int grid[GRID_H][GRID_W], Ant ant)
{
	Ant_UpdatePosition(&ant);

	return (!Ant_OutOfDimension(ant) && Ant_OnFood(grid, ant));
}

// ------------------------------ Game ------------------------------

Game* Game_New(void)
{
	Game* game = (Game*)calloc(1, sizeof(Game));
	assert(game);

	int grid[GRID_H][GRID_W] = {
		{ 0, 1, 1, 0, 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 }
	};

	memcpy(game->grid, grid, GRID_W * GRID_H * sizeof(int));

	game->ant.direction = RIGHT;

	return game;
}

Game* Game_Copy(Game* game)
{
	Game* res = (Game*)calloc(1, sizeof(Game));
	assert(res);

	*res = *game;

	return res;
}

void Game_Destroy(Game* game)
{
	if (!game) return;

	free(game);
}

void Game_Print(Game* game)
{
	for (int j = 0; j < GRID_H; j++)
	{
		for (int i = 0; i < GRID_W; i++)
		{
			if ((i == game->ant.i) && (j == game->ant.j))
			{
				printf("X ");
			}
			else
			{
				printf("%c ", ((game->grid[j][i] == CELL_EMPTY) ? '.' : 'o'));
			}
		}

		putchar('\n');
	}

	putchar('\n');
}

bool Game_IsOver(Game* game)
{
	if (Ant_OutOfDimension(game->ant))
	{
		return true;
	}

	for (int j = 0; j < GRID_H; j++)
	{
		for (int i = 0; i < GRID_W; i++)
		{
			if (game->grid[j][i] == CELL_FOOD)
			{
				return false;
			}
		}
	}

	return true;
}

void Game_Update(Game* game)
{
	Ant_UpdatePosition(&(game->ant));

	if (Game_IsOver(game))
	{
		game->state = GAME_IS_OVER;
		return;
	}

	if (Ant_OnFood(game->grid, game->ant))
	{
		game->grid[game->ant.j][game->ant.i] = CELL_EMPTY;
		game->ant.score += 1;
	}
}





// ------------------------------ Opérations ------------------------------

float add(float a, float b)
{
	return (a + b);
}

float sub(float a, float b)
{
	return (a - b);
}

float multiply(float a, float b)
{
	return (a * b);
}

float divide(float a, float b)
{
	return ((b == 0.0f) ? 1.0f : (a / b));
}

float srt(float a)
{
	return sqrtf(fabsf(a));
}

Function* Function_New_T(DList* T)
{
	Function* function = (Function*)calloc(1, sizeof(Function));
	assert(function);

	int index = int_random(0, T->size - 1);

	float* value = (float*)DList_Get(T, index);

	function->size = 0;
	function->T = value;
	function->id = VAL;

	return function;
}

Function* Function_New_F(DList* F)
{
	Function* function = (Function*)calloc(1, sizeof(Function));
	assert(function);

	int index = int_random(0, F->size - 1);

	float (*f)(float) = (float (*)(float))DList_Get(F, index);

	if (f == &add)
	{
		function->size = 2;
		function->f2 = f;
		function->id = ADD;
	}
	else if (f == &sub)
	{
		function->size = 2;
		function->f2 = f;
		function->id = SUB;
	}
	else if (f == &multiply)
	{
		function->size = 2;
		function->f2 = f;
		function->id = MUL;
	}
	else if (f == &divide)
	{
		function->size = 2;
		function->f2 = f;
		function->id = DIV;
	}
	else if (f == &srt)
	{
		function->size = 1;
		function->f1 = f;
		function->id = SRT;
	}

	return function;
}

Function* Function_New(DList* F, DList* T)
{
	int size = (F->size + T->size);

	int index = int_random(0, size - 1);

	if (index < F->size)
	{
		return Function_New_F(F);
	}
	else
	{
		return Function_New_T(T);
	}
}

Function* Function_Copy(Function* function)
{
	Function* res = (Function*)calloc(1, sizeof(Function));
	assert(res);

	*res = *function;

	return res;
}

// ------------------------------ Tree ------------------------------

Tree* Tree_New(void)
{
	Tree* tree = (Tree*)calloc(1, sizeof(Tree));
	assert(tree);

	return tree;
}

TreeNode* Tree_CopyRec(TreeNode* node, void* (*funcCopy)(void*))
{
	if (!node) return NULL;

	TreeNode* res = (TreeNode*)calloc(1, sizeof(TreeNode));
	assert(res);

	res->value = funcCopy(node->value);
	res->L = Tree_CopyRec(node->L, funcCopy);
	res->R = Tree_CopyRec(node->R, funcCopy);

	return res;
}

Tree* Tree_Copy(Tree* tree, void* (*funcCopy)(void*))
{
	if (!tree) return NULL;

	Tree* res = (Tree*)calloc(1, sizeof(Tree));
	assert(res);

	res->root = Tree_CopyRec(tree->root, funcCopy);

	return res;
}

void Tree_DestroyRec(TreeNode* node, void* (*funcDestroy)(void*))
{
	if (!node) return;

	Tree_DestroyRec(node->L, funcDestroy);
	Tree_DestroyRec(node->R, funcDestroy);

	funcDestroy(node->value);
	free(node);
}

void Tree_Destroy(Tree* tree, void* (*funcDestroy)(void*))
{
	if (!tree) return;

	Tree_DestroyRec(tree->root, funcDestroy);
	free(tree);
}

int Tree_GetSizeRec(TreeNode* node)
{
	if (!node) return 0;

	return Tree_GetSizeRec(node->L) + Tree_GetSizeRec(node->R) + 1;
}

int Tree_GetSize(Tree* tree)
{
	return Tree_GetSizeRec(tree->root);
}

void Tree_PrintRec(TreeNode* node, int w)
{
	if (!node) return;

	int space = 10;

	w += space;

	Tree_PrintRec(node->R, w);

	printf("\n");

	for (int i = space; i < w; i++)
	{
		putchar(' ');
	}

	Function* function = node->value;

	/*if (function->size == 0)
	{
		printf("[%f]\n", *(function->T));
	}
	else*/
	{
		printf("[%c]\n", function->id);
	}

	Tree_PrintRec(node->L, w);
}

void Tree_Print(Tree* tree)
{
	Tree_PrintRec(tree->root, 10);
}

TreeNode* Tree_GetRec(TreeNode* node, int* index, TreeNode** parent)
{
	if (!node) return NULL;

	if (*index == 0) return node;

	*index -= 1;

	*parent = node;
	TreeNode* res = Tree_GetRec(node->L, index, parent);

	if (res)
	{
		return res;
	}
	else
	{
		*parent = node;
		return Tree_GetRec(node->R, index, parent);
	}
}

TreeNode* Tree_Get(Tree* tree, int index, TreeNode** parent)
{
	int size = Tree_GetSize(tree);

	assert((0 <= index) && (index < size));

	*parent = NULL;

	return Tree_GetRec(tree->root, &index, parent);
}

TreeNode* TreeAI_NewRec(int depth, DList* F, DList* T)
{
	TreeNode* node = (TreeNode*)calloc(1, sizeof(TreeNode));
	assert(node);

	Function* function = NULL;

	if (depth == 0)
	{
		function = Function_New_T(T);
		node->value = function;
		return;
	}
	else
	{
		function = Function_New(F, T);
	}

	node->value = function;

	if (function->size > 0)
	{
		node->L = TreeAI_NewRec(depth - 1, F, T);
	}

	if (function->size > 1)
	{
		node->R = TreeAI_NewRec(depth - 1, F, T);
	}

	return node;
}

Tree* TreeAI_New(DList* F, DList* T)
{
	Tree* tree = (Tree*)calloc(1, sizeof(Tree));
	assert(tree);

	tree->root = TreeAI_NewRec(MAX_DEPTH, F, T);

	return tree;
}

float TreeAI_ExecuteRec(TreeNode* node)
{
	Function* function = (Function*)node->value;

	if (function->size == 0)
	{
		return *(function->T);
	}

	float a = TreeAI_ExecuteRec(node->L);

	if (function->size == 1)
	{
		return function->f1(a);
	}

	float b = TreeAI_ExecuteRec(node->R);

	return function->f2(a, b);
}

float TreeAI_Execute(Tree* tree)
{
	return TreeAI_ExecuteRec(tree->root);
}

void TreeAI_UpdateFScore(Tree* tree, DList* T)
{
	// SPÉ

	float triangles[10][2] = {
		{3.0f, 4.0f},
		{1.0f, 5.0f},
		{9.0f, 2.0f},
		{9.0f, 2.0f},
		{3.0f, 3.0f},
		{20.0f, 10.0f},
		{30.0f, 40.0f},
		{30.0f, 12.0f},
		{0.0f, 0.0f},
		{20.0f, 20.0f}
	};

	float* a = (float*)DList_Get(T, 0);
	float* b = (float*)DList_Get(T, 1);

	tree->fitnessScore = 0.0f;

	for (int i = 0; i < 10; i++)
	{
		*a = triangles[i][0];
		*b = triangles[i][1];

		float res = sqrtf(*a * *a + *b * *b);
		float resTree = TreeAI_Execute(tree);

		tree->fitnessScore += fabsf(res - resTree);
	}
}

int TreeAI_CompareFScore(Tree* t1, Tree* t2)
{
	if (t1->fitnessScore > t2->fitnessScore)
	{
		return 1;
	}
	else if (t1->fitnessScore < t2->fitnessScore)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void TreeAI_Crossover(Tree* t1, Tree* t2)
{
	int t1Size = Tree_GetSize(t1);
	int r1 = int_random(0, t1Size - 1);
	TreeNode* p1 = NULL;
	TreeNode* n1 = Tree_Get(t1, r1, &p1);

	int t2Size = Tree_GetSize(t2);
	int r2 = int_random(0, t2Size - 1);
	TreeNode* p2 = NULL;
	TreeNode* n2 = Tree_Get(t2, r2, &p2);

	if (p1)
	{
		if (p1->L == n1)
		{
			p1->L = n2;
		}
		else
		{
			p1->R = n2;
		}
	}
	else
	{
		t1->root = n2;
	}

	if (p2)
	{
		if (p2->L == n2)
		{
			p2->L = n1;
		}
		else
		{
			p2->R = n1;
		}
	}
	else
	{
		t2->root = n1;
	}
}





void main2(void)
{
	DList* F = DList_New();
	DList_InsertLast(F, &add);
	DList_InsertLast(F, &sub);
	DList_InsertLast(F, &multiply);
	DList_InsertLast(F, &divide);
	DList_InsertLast(F, &srt);

	DList* T = DList_New();
	DList_InsertLast(T, calloc(1, sizeof(int)));
	DList_InsertLast(T, calloc(1, sizeof(int)));

	int populationSize = 100;
	DList* population = DList_New();

	int selectionSize = 10;
	DList* selection = DList_New();

	int iterCount = 0;

	while (1)
	{
		// Création de la population:

		for (int i = 0; i < populationSize; i++)
		{
			Tree* tree = TreeAI_New(F, T);
			TreeAI_UpdateFScore(tree, T);

			if (tree->fitnessScore == 0.0f && Tree_GetSize(tree) == 8)
			{
				printf("BANGER FIND : \n\n");
				Tree_Print(tree);
				system("pause");
			}

			DList_InsertSorted(population, tree, false, &TreeAI_CompareFScore);
		}

		// Sélection:

		for (int i = 0; i < selectionSize; i++)
		{
			DList_InsertLast(selection, DList_PopFirst(population));
		}

		// Suppression:

		for (int i = 0; i < populationSize - selectionSize; i++)
		{
			Tree* tree = (Tree*)DList_PopFirst(population);
			Tree_Destroy(tree, &free);
		}

		// Copie:

		for (int i = 0; i < selectionSize; i++)
		{
			Tree* tree = (Tree*)DList_Get(selection, i);
			Tree* copy = Tree_Copy(tree, &Function_Copy);

			DList_InsertLast(selection, copy);
		}
		
		// Crossover:

		for (int i = 0; i < selectionSize - 1; i++)
		{
			Tree* t1 = (Tree*)DList_Get(selection, i);
			Tree* t2 = (Tree*)DList_Get(selection, i + 1);

			TreeAI_Crossover(t1, t2);
		}

		iterCount += 1;

		printf("iterCount = %d \n", iterCount);
	}
}
