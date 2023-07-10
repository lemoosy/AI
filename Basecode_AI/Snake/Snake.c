#include "Snake.h"

#ifdef GAME_SNAKE

// Position:

Position Position_Create(int i, int j)
{
	return ((Position) { .i = i, .j = j });
}

bool Position_Equal(Position pos0, Position pos1)
{
	return ((pos0.i == pos1.i) && (pos0.j == pos1.j));
}

bool Position_OutOfDimension(Position pos)
{
	return ((pos.i < 0) || (pos.j < 0) || (pos.i >= GRID_W) || (pos.j >= GRID_H));
}

void Position_Update(Position* pos, Direction dir)
{
	if (dir & N) pos->j -= 1;
	if (dir & S) pos->j += 1;
	if (dir & W) pos->i -= 1;
	if (dir & E) pos->i += 1;
}

bool Position_Check(Position pos, Direction dir, CellID cell, CellID grid[][GRID_W])
{
	while (1)
	{
		Position_Update(&pos, dir);

		if (Position_OutOfDimension(pos))
		{
			return false;
		}

		if (grid[pos.j][pos.i] == cell)
		{
			return true;
		}
	}

	assert(false);
}

// Body:

Body* Body_Create(Position pos, Direction dir)
{
	Body* body = (Body*)calloc(1, sizeof(Body));
	assert(body);

	body->pos = pos;
	body->dir = dir;

	return body;
}

void Body_Destroy(Body* body)
{
	if (!body) return;

	Body_Destroy(body->next);
	free(body);
}

Body* Body_Update(Body* body, Direction dirPrev)
{
	if (!body) return NULL;
	
	Body bodyPrev = *body;

	Position_Update(&body->pos, body->dir);
	
	Body* res = Body_Update(body->next, body->dir);
	
	if (res == NULL)
	{
		res = (Body*)calloc(1, sizeof(Body));
		assert(res);

		*res = bodyPrev;
	}

	body->dir = dirPrev;

	return res;
}

// Snake:

Snake* Snake_Create(void)
{
	Snake* snake = (Snake*)calloc(1, sizeof(Snake));
	assert(snake);

	snake->head = Body_Create(Position_Create(GRID_W / 2, GRID_H / 2), E);
	snake->tail = snake->head;
	snake->size = 1;

	return snake;
}

void Snake_Destroy(Snake* snake)
{
	if (!snake) return;

	Body_Destroy(snake->head);
	free(snake);
}

Body* Snake_UpdatePosition(Snake* snake)
{
	return Body_Update(snake->head, snake->head->dir);
}

void Snake_AddSize(Snake* snake, Body* tail)
{
	snake->tail->next = tail;
	snake->tail = tail;
	snake->size += 1;
}

void Snake_SetDirection(Snake* snake, Direction dir)
{
	if (snake->size == 1)
	{
		snake->head->dir = dir;
	}
	else
	{
		Position pos0 = snake->head->pos;
		Position pos1 = snake->head->next->pos;

		Position_Update(&pos0, dir);

		if (!Position_Equal(pos0, pos1))
		{
			snake->head->dir = dir;
		}
	}
}

void Snake_ToGrid(Snake* snake, CellID grid[][GRID_W])
{
	Body* curr = snake->head;

	while (curr)
	{
		Position pos = curr->pos;

		if (Position_OutOfDimension(pos))
		{
			snake->state = SNAKE_DEAD;
		}
		else if (grid[pos.j][pos.i] == CELL_SNAKE)
		{
			snake->state = SNAKE_DEAD;
		}
		else
		{
			grid[pos.j][pos.i] = CELL_SNAKE;
		}

		curr = curr->next;
	}
}

// Grid:

void Grid_Clear(CellID grid[][GRID_W])
{
	for (int j = 0; j < GRID_H; j++)
	{
		for (int i = 0; i < GRID_W; i++)
		{
			grid[j][i] = CELL_EMPTY;
		}
	}
}

// Food:

Position* Food_Create(CellID grid[][GRID_W])
{
	Position* pos = (Position*)calloc(1, sizeof(Position));
	assert(pos);

	int* tabI = Int_TabRandomNoRep(GRID_W);
	int* tabJ = Int_TabRandomNoRep(GRID_H);

	bool quit = false;

	for (int y = 0; y < GRID_H; y++)
	{
		for (int x = 0; x < GRID_W; x++)
		{
			int i = tabI[x];
			int j = tabJ[y];

			if (grid[j][i] == CELL_EMPTY)
			{
				*pos = Position_Create(i, j);
				quit = true;
				break;
			}
		}

		if (quit)
		{
			break;
		}
	}

	free(tabI);
	free(tabJ);

	if (!quit)
	{
		free(pos);
		return NULL;
	}

	return pos;
}

void Food_ToGrid(Position food, CellID grid[][GRID_W])
{
	grid[food.j][food.i] = CELL_FOOD;
}

// Game:

Game* Game_Create(void)
{
	Game* game = (Game*)calloc(1, sizeof(Game));
	assert(game);

	game->snake = Snake_Create();

	return game;
}

void Game_Destroy(Game* game)
{
	if (!game) return;

	if (game->food) free(game->food);
	Snake_Destroy(game->snake);
	free(game);
}

void Game_Update(Game* game, Window* window)
{
	Snake* snake = game->snake;

	// Window:

	if (window)
	{
		Input input = window->input;

		if (input.left)
		{
			Snake_SetDirection(snake, W);
		}

		if (input.right)
		{
			Snake_SetDirection(snake, E);
		}

		if (input.up)
		{
			Snake_SetDirection(snake, N);
		}

		if (input.down)
		{
			Snake_SetDirection(snake, S);
		}
	}

	// Snake:

	Grid_Clear(game->grid);
	Body* tail = Snake_UpdatePosition(snake);
	Snake_ToGrid(snake, game->grid);

	// Food:

	Position* food = game->food;

	if (food)
	{
		if (Position_Equal(*food, snake->head->pos))
		{
			Snake_AddSize(game->snake, tail);
			game->grid[tail->pos.j][tail->pos.i] = CELL_SNAKE;
			free(food);
			game->food = Food_Create(game->grid);
		}
		else
		{
			Body_Destroy(tail);
		}
	}
	else
	{
		Body_Destroy(tail);
		game->food = Food_Create(game->grid);
	}

	if (game->food)
	{
		Food_ToGrid(*game->food, game->grid);
	}

	// State:

	if (game->snake->state == SNAKE_DEAD)
	{
		game->state = GAME_IS_OVER;
	}

	if (game->food == NULL)
	{
		game->state = GAME_IS_FULL;
	}
}

void Game_Draw(Game* game, Window* window)
{
	float sizeX = (float)(WINDOW_W / GRID_W);
	float sizeY = (float)(WINDOW_H / GRID_H);

	for (int j = 0; j < GRID_H; j++)
	{
		for (int i = 0; i < GRID_W; i++)
		{
			ColorRGBA color = { 0 };

			switch (game->grid[j][i])
			{
			case CELL_EMPTY:
				color = ColorRGBA_Create(0, 0, 0, 255);
				break;

			case CELL_SNAKE:
				color = ColorRGBA_Create(255, 255, 255, 255);
				break;

			case CELL_FOOD:
				color = ColorRGBA_Create(255, 0, 0, 255);
				break;
			}

			Window_DrawRectangle(
				window,
				(float)i * sizeX,
				(float)j * sizeY,
				sizeX,
				sizeX,
				color	
			);
		}
	}
}

// ------------------------------ TreeAI ------------------------------

void __Snake_Fitness(Tree* tree, Window* window)
{
	int gameMax = 3;
	int iterMax = 150;
	int scoreMax = 0;

	for (int i = 0; i < gameMax; i++)
	{
		g_game = Game_Create();

		int iter = 0;
		int iterTotal = 0;

		while (iter < iterMax)
		{
			int scorePrev = g_game->snake->size;

			Game_Update(g_game, NULL);
			
			TreeAI_Execute(tree, g_game);

			if (window)
			{
				Game_Draw(g_game, window);
				Window_Update(window);
				Window_Refresh(window);

				if (window->input.f1)
				{
					Sleep(10);
				}
				else if (window->input.f3)
				{
					Sleep(200);
				}
				else
				{
					Sleep(50);
				}
			}

			if (g_game->state == GAME_IS_OVER) break;
			if (g_game->state == GAME_IS_FULL) break;
	
			iter += 1;
			iterTotal += 1;
	
			if (scorePrev != g_game->snake->size)
			{
				iter = 0;
			}
		}
	
		int score = g_game->snake->size;

		scoreMax = max(scoreMax, score);

		Game_Destroy(g_game);
	}
	
	tree->score = (float)scoreMax;
}

// TYPE_NULL

void* __Snake_SetDirectionN(void* node)
{
	Snake_SetDirection(g_game->snake, N);
	return NULL;
}

void* __Snake_SetDirectionS(void* node)
{
	Snake_SetDirection(g_game->snake, S);
	return NULL;
}

void* __Snake_SetDirectionW(void* node)
{
	Snake_SetDirection(g_game->snake, W);
	return NULL;
}

void* __Snake_SetDirectionE(void* node)
{
	Snake_SetDirection(g_game->snake, E);
	return NULL;
}

// TYPE_BOOL

void* __Snake_HeadFoodN(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, N);
	return Bool_Create(g_game->grid[pos.j][pos.i] == CELL_FOOD);
}

void* __Snake_HeadFoodS(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, S);
	return Bool_Create(g_game->grid[pos.j][pos.i] == CELL_FOOD);
}

void* __Snake_HeadFoodW(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, W);
	return Bool_Create(g_game->grid[pos.j][pos.i] == CELL_FOOD);
}

void* __Snake_HeadFoodE(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, E);
	return Bool_Create(g_game->grid[pos.j][pos.i] == CELL_FOOD);
}

void* __Snake_HeadBodyN(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, N);
	return Bool_Create(g_game->grid[pos.j][pos.i] == CELL_SNAKE);
}

void* __Snake_HeadBodyS(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, S);
	return Bool_Create(g_game->grid[pos.j][pos.i] == CELL_SNAKE);
}

void* __Snake_HeadBodyW(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, W);
	return Bool_Create(g_game->grid[pos.j][pos.i] == CELL_SNAKE);
}

void* __Snake_HeadBodyE(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, E);
	return Bool_Create(g_game->grid[pos.j][pos.i] == CELL_SNAKE);
}

void* __Snake_HeadWallN(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, N);
	return Bool_Create(Position_OutOfDimension(pos));
}

void* __Snake_HeadWallS(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, S);
	return Bool_Create(Position_OutOfDimension(pos));
}

void* __Snake_HeadWallW(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, W);
	return Bool_Create(Position_OutOfDimension(pos));
}

void* __Snake_HeadWallE(void* node)
{
	Position pos = g_game->snake->head->pos;
	Position_Update(&pos, E);
	return Bool_Create(Position_OutOfDimension(pos));
}

void* __Snake_DirectionHeadIsN(void* node)
{
	return Bool_Create(g_game->snake->head->dir == N);
}

void* __Snake_DirectionHeadIsS(void* node)
{
	return Bool_Create(g_game->snake->head->dir == S);
}

void* __Snake_DirectionHeadIsW(void* node)
{
	return Bool_Create(g_game->snake->head->dir == W);
}

void* __Snake_DirectionHeadIsE(void* node)
{
	return Bool_Create(g_game->snake->head->dir == E);
}

void* __Snake_AheadFood(void* node)
{
	Position pos = g_game->snake->head->pos;
	Direction dir = g_game->snake->head->dir;
	return Bool_Create(Position_Check(pos, dir, CELL_FOOD, g_game->grid));
}

void* __Snake_AheadBody(void* node)
{
	Position pos = g_game->snake->head->pos;
	Direction dir = g_game->snake->head->dir;
	return Bool_Create(Position_Check(pos, dir, CELL_SNAKE, g_game->grid));
}

void* __Snake_AheadWall2(void* node)
{
	Position pos = g_game->snake->head->pos;
	Direction dir = g_game->snake->head->dir;

	Position_Update(&pos, dir);

	if (Position_OutOfDimension(pos)) return Bool_Create(false);

	Position_Update(&pos, dir);

	return Bool_Create(Position_OutOfDimension(pos));
}

#endif // GAME_SNAKE
