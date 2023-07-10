#include "Connect4.h"

#ifdef GAME_CONNECT4

Game* Game_Create()
{
	Game* game = (Game*)calloc(1, sizeof(Game));
	assert(game);

	game->turn = Int_Random(PLAYER_1, PLAYER_2);

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
	printf("-------------------- Game --------------------\n\n");

	for (int i = 0; i < GRID_W; i++)
	{
		printf("%d ", i);
	}

	for (int j = 0; j < GRID_H; j++)
	{
		putchar('\n');
	
		for (int i = 0; i < GRID_W; i++)
		{
			switch (game->grid[j][i])
			{
			case PLAYER_1:
				printf("O ");
				break;

			case PLAYER_2:
				printf("X ");
				break;

			default:
				printf(". ");
				break;
			}
		}
	}

	switch (game->turn)
	{
	case PLAYER_1:
		printf("\n\nTurn: O \n\n");
		break;

	case PLAYER_2:
		printf("\n\nTurn: X \n\n");
		break;

	default:
		printf("\n\nTurn: ? \n\n");
		break;
	}
}

void Game_MinimaxVSPlayer(void)
{
	Game* game = Game_Create();

	while (game->state == GAME_IN_PROGRESS)
	{
		Game_Print(game);

		int move = -1;

		if (game->turn == PLAYER_1)
		{
			printf("player >> ");
			scanf("%d", &move);
			putchar('\n');
		}
		else
		{
			printf("minimax >> ");
			move = AI_Minimax_GetMove(game);
			Sleep(500);
			printf("%d\n\n", move);
		}

		if (!Game_CanPlayAt(game, move)) continue;

		Game_PlayAt(game, move);
	}

	Game_Print(game);

	switch (game->state)
	{
	case GAME_P1_WON:
		printf("##### GG player 1! #####\n\n");
		break;

	case GAME_P2_WON:
		printf("##### GG player 2! #####\n\n");
		break;

	default:
		printf("##### Game is tied! #####\n\n");
		break;
	}

	Game_Destroy(game);
}

void Game_MinimaxVSNN(Network* net, int gameCount)
{
	FILE* file = fopen("../Data/scores.txt", "w");

	if (file == NULL)
	{
		printf("ERROR - Game_MinimaxVSNN() \n");
		printf("ERROR - fopen() \n");
		abort();
	}
	
	int scores[3] = { 0 };

	for (int i = 0; i < gameCount; i++)
	{
		Game* game = Game_Create();

		for (int j = 0; j < 4; j++)
		{
			int move = AI_Random_GetMove(game);
			Game_PlayAt(game, move);
		}

		while (game->state == GAME_IN_PROGRESS)
		{
			int move = -1;

			if (game->turn == PLAYER_1)
			{
				move = AI_Minimax_GetMove(game);
			}
			else
			{
				move = AI_NN_GetMove(game, net);
			}

			Game_PlayAt(game, move);
		}

		if (i % 100 == 0)
		{
			Game_Print(game);

			switch (game->state)
			{
			case GAME_P1_WON:
				scores[1] += 1;
				printf("##### GG player 1! #####\n\n");
				break;

			case GAME_P2_WON:
				scores[2] += 1;
				printf("##### GG player 2! #####\n\n");
				break;

			default:
				scores[0] += 1;
				printf("##### Game is tied! #####\n\n");
				break;
			}
		
			printf("Score (%d): %d | %d | %d | %d\n\n", i, scores[0], scores[1], scores[2], scores[1] - scores[2]);

			time_t timeNow = time(NULL);
			struct tm* timeLocal = localtime(&timeNow);

			fprintf(file, "%.2d %.2d %d\n", timeLocal->tm_hour, timeLocal->tm_min, scores[1] - scores[2]);
		}

		Game_Destroy(game);
	}

	fclose(file);
}

bool Game_CanPlayAt(Game* game, int column)
{
	bool outOfDimension = ((column < 0) || (column >= GRID_W));

	return (!outOfDimension && (game->grid[0][column] == TOKEN_EMPTY));
}

void Game_PlayAt(Game* game, int column)
{
	assert(Game_CanPlayAt(game, column));

	int line = 0;

	while ((line + 1 < GRID_H) && (game->grid[line + 1][column] == TOKEN_EMPTY))
	{
		line++;
	}

	game->grid[line][column] = game->turn;
	
	int winner = Game_GetWinner(game);

	if (winner != PLAYER_NONE)
	{
		if (winner == PLAYER_1)
		{
			game->state = GAME_P1_WON;
		}
		else
		{
			game->state = GAME_P2_WON;
		}

		return;
	}

	if (Game_IsFull(game))
	{
		game->state = GAME_IS_TIED;

		return;
	}

	game->turn = game->turn == PLAYER_1 ? PLAYER_2 : PLAYER_1;
}

bool Game_IsFull(Game* game)
{
	for (int i = 0; i < GRID_W; i++)
	{
		if (game->grid[0][i] == TOKEN_EMPTY)
		{
			return false;
		}
	}

	return true;
}

bool __Game_HasConnection(Game* game, int i, int j, Direction direction)
{
	TokenID token = game->grid[j][i];

	for (int k = 0; k < 3; k++)
	{
		if (direction & N)	j--;
		if (direction & S)	j++;
		if (direction & W)	i--;
		if (direction & E)	i++;

		if ((i < 0) || (i >= GRID_W) ||
			(j < 0) || (j >= GRID_H) ||
			(game->grid[j][i] != token))
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
			TokenID token = game->grid[j][i];

			if (token == TOKEN_EMPTY) continue;

			if (__Game_HasConnection(game, i, j, S) ||
				__Game_HasConnection(game, i, j, E) ||
				__Game_HasConnection(game, i, j, S + E) ||
				__Game_HasConnection(game, i, j, N + E))
			{
				if (token == TOKEN_P1)
				{
					return PLAYER_1;
				}
				else
				{
					return PLAYER_2;
				}
			}
		}
	}

	return PLAYER_NONE;
}

int Game_Heuristic(Game* game, PlayerID turn)
{
	// URL: https://www.christian-schmidt.fr/puissance4

	int connections[GRID_H][GRID_W] = {
		{3,  4,  5,  7,  5,  4,  3},
		{4,  6,  8,  10, 8,  6,  4},
		{5,  8,  11, 13, 11, 8,  5},
		{5,  8,  11, 13, 11, 8,  5},
		{4,  6,  8,  10, 8,  6,  4},
		{3,  4,  5,  7,  5,  4,  3}
	};

	int res = 0;

	for (int j = 0; j < GRID_H; j++)
	{
		for (int i = 0; i < GRID_W; i++)
		{
			TokenID token = game->grid[j][i];

			if (token != TOKEN_EMPTY)
			{
				if (token == turn)
				{
					res += connections[j][i];
				}
				else
				{
					res -= connections[j][i];
				}
			}
		}
	}

	return res;
}

#endif // GAME_CONNECT4
