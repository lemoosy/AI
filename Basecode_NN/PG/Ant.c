#include "Ant.h"

bool Ant_OutOfDimension(Ant ant)
{
	return ((ant.i < 0) || (ant.j < 0) || (ant.i >= GRID_W) || (ant.j >= GRID_H));
}

bool Ant_OnFood(Ant ant)
{
	return (g_game.grid[ant.j][ant.i] == CELL_FOOD);
}

bool Ant_OnBomb(Ant ant)
{
	return (g_game.grid[ant.j][ant.i] == CELL_BOMB);
}

// ------------------------------ TreeAI ------------------------------

// res = TYPE_NONE

void* Ant_SetDirectionLeft(TreeNode* node)
{
	Ant* ant = &(g_game.ant);

	ant->direction = LEFT;

	return NULL;
}

void* Ant_SetDirectionRight(TreeNode* node)
{
	Ant* ant = &(g_game.ant);

	ant->direction = RIGHT;

	return NULL;
}

void* Ant_SetDirectionUp(TreeNode* node)
{
	Ant* ant = &(g_game.ant);

	ant->direction = UP;

	return NULL;
}

void* Ant_SetDirectionDown(TreeNode* node)
{
	Ant* ant = &(g_game.ant);

	ant->direction = DOWN;

	return NULL;
}

void* Ant_Move(TreeNode* node)
{
	if (g_game.state == GAME_IS_OVER || g_game.state == GAME_IS_FINISH) return NULL;

	Ant ant = g_game.ant;

	if (ant.direction == LEFT)	ant.i -= 1;
	if (ant.direction == RIGHT)	ant.i += 1;
	if (ant.direction == UP)	ant.j -= 1;
	if (ant.direction == DOWN)	ant.j += 1;

	if (!Ant_OutOfDimension(ant))
	{
		g_game.ant = ant;

		if (Ant_OnFood(ant))
		{
			g_game.grid[g_game.ant.j][g_game.ant.i] = CELL_EMPTY;
			g_game.ant.score += 1;

			if (Game_IsOver(g_game))
			{
				g_game.state = GAME_IS_FINISH;
			}
		}

		else if (Ant_OnBomb(ant))
		{
			g_game.state = GAME_IS_OVER;
		}
	}

	if (in2)
	{
		Game_Print(g_game);
		system("pause");
	}

	return NULL;
}

// res = TYPE_BOOL

void* Ant_AheadFood(void* node)
{
	Ant ant = g_game.ant;

	bool res = false;

	if (ant.direction == LEFT && ant.i > 0 && g_game.grid[ant.j][ant.i - 1] == CELL_FOOD)
	{
		res = true;
	}

	if (ant.direction == RIGHT && ant.i < GRID_W - 1 && g_game.grid[ant.j][ant.i + 1] == CELL_FOOD)
	{
		res = true;
	}

	if (ant.direction == UP && ant.j > 0 && g_game.grid[ant.j - 1][ant.i] == CELL_FOOD)
	{
		res = true;
	}

	if (ant.direction == DOWN && ant.j < GRID_H - 1 && g_game.grid[ant.j + 1][ant.i] == CELL_FOOD)
	{
		res = true;
	}

	return Bool_New(res);
}

void* Ant_AheadBomb(void* node)
{
	Ant ant = g_game.ant;

	bool res = false;

	if (ant.direction == LEFT && ant.i > 0 && g_game.grid[ant.j][ant.i - 1] == CELL_BOMB)
	{
		res = true;
	}

	if (ant.direction == RIGHT && ant.i < GRID_W - 1 && g_game.grid[ant.j][ant.i + 1] == CELL_BOMB)
	{
		res = true;
	}

	if (ant.direction == UP && ant.j > 0 && g_game.grid[ant.j - 1][ant.i] == CELL_BOMB)
	{
		res = true;
	}

	if (ant.direction == DOWN && ant.j < GRID_H - 1 && g_game.grid[ant.j + 1][ant.i] == CELL_BOMB)
	{
		res = true;
	}

	return Bool_New(res);
}


// ------------------------------ Game ------------------------------

Game Game_New(void)
{
	Game game = { 0 };

	int grid[GRID_H][GRID_W] = {
		{ 0, 1, 1, 0, 0, 0, 1, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 2, 1 },
		{ 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
		{ 0, 2, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 2, 0, 1, 1, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 2 },
		{ 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 }
	};

	memcpy(game.grid, grid, GRID_W * GRID_H * sizeof(int));

	game.ant.direction = RIGHT;

	return game;
}

void Game_Print(Game game)
{
	for (int j = 0; j < GRID_H; j++)
	{
		for (int i = 0; i < GRID_W; i++)
		{
			if ((i == game.ant.i) && (j == game.ant.j))
			{
				printf("X ");
			}
			else
			{
				switch (game.grid[j][i])
				{
				case CELL_EMPTY:
					printf(". ");
					break;

				case CELL_FOOD:
					printf("o ");
					break;

				case CELL_BOMB:
					printf("# ");
					break;

				default:
					break;
				}
			}
		}

		putchar('\n');
	}

	putchar('\n');
}

bool Game_IsOver(Game game)
{
	for (int j = 0; j < GRID_H; j++)
	{
		for (int i = 0; i < GRID_W; i++)
		{
			if (game.grid[j][i] == CELL_FOOD)
			{
				return false;
			}
		}
	}

	return true;
}

void Game_Update(Game* game)
{
	
}
