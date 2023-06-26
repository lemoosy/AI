#include "Connect4.h"

Game* Game_New()
{
	Game* game = (Game*)calloc(1, sizeof(Game));
	assert(game);

	game->turn = int_random(PLAYER_1, PLAYER_2);

	return game;
}

void Game_Destroy(Game* game)
{
	if (!game) return;

	free(game);
}

void Game_Print(Game* game)
{
	printf("---------- Game ----------\n\n");

	for (int j = 0; j < GRID_H; j++)
	{
		for (int i = 0; i < GRID_W; i++)
		{
			switch (game->grid[j][i])
			{
			case PLAYER_1:
				putchar('O');
				break;

			case PLAYER_2:
				putchar('X');
				break;

			default:
				putchar(' ');
				break;
			}

			putchar(' ');
		}

		putchar('\n');
	}

	printf("\nTurn: %d\n\n", game->turn);
	printf("--------------------------\n\n");
}

bool Game_CanPlayAt(Game* game, int column)
{
	assert((0 <= column) && (column < GRID_W));

	return (game->grid[0][column] == CELL_EMPTY);
}

void Game_PlayAt(Game* game, int column)
{
	assert(Game_CanPlayAt(game, column));

	int line = 0;

	while (game->grid[line + 1][column] == CELL_EMPTY)
	{
		line++;
	}

	game->grid[line][column] = game->turn;
	
	int winner = Game_GetWinner(game);

	if (winner != PLAYER_NONE)
	{
		game->state == winner;
		return;
	}

	if (Game_IsOver(game))
	{
		game->state = GAME_IS_OVER;
		return;
	}

	game->turn = game->turn == PLAYER_1 ? PLAYER_2 : PLAYER_1;
}

bool Game_IsOver(Game* game)
{
	for (int i = 0; i < GRID_W; i++)
	{
		if (game->grid[0][i] == CELL_EMPTY)
		{
			return false;
		}
	}

	return true;
}

bool __Game_HasConnection(Game* game, int i, int j, Direction dir)
{
	CellID cell = game->grid[j][i];

	for (int k = 0; k < 3; k++)
	{
		if (dir & LEFT)
		{
			i--;
		}

		if (dir & RIGHT)
		{
			i++;
		}

		if (dir & UP)
		{
			j--;
		}

		if (dir & DOWN)
		{
			j++;
		}

		if ((i < 0) || (i >= GRID_W) ||
			(j < 0) || (j >= GRID_H) ||
			(game->grid[j][i] != cell))
		{
			return false;
		}
	}

	return true;
}

PlayerID Game_GetWinner(Game* game)
{
	for (int j = 0; j < GRID_H; j++)
	{
		for (int i = 0; i < GRID_W; i++)
		{
			CellID cell = game->grid[j][i];

			if (cell == CELL_EMPTY) continue;

			if (__Game_HasConnection(game, i, j, LEFT) ||
				__Game_HasConnection(game, i, j, RIGHT) ||
				__Game_HasConnection(game, i, j, UP) ||
				__Game_HasConnection(game, i, j, DOWN) ||
				__Game_HasConnection(game, i, j, LEFT | UP) ||
				__Game_HasConnection(game, i, j, RIGHT | UP))
			{
				return cell;
			}
		}
	}

	return PLAYER_NONE;
}
