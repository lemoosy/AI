//#include "Game.h"
//#include "Game.h"
//
//Game* Game_New()
//{
//	Game* game = (Game*)calloc(1, sizeof(Game));
//	assert(game);
//
//	game->turn = int_random(PLAYER_1, PLAYER_2);
//
//	return game;
//}
//
//Game* Game_Copy(Game* game)
//{
//	Game* res = (Game*)calloc(1, sizeof(Game));
//	assert(res);
//
//	*res = *game;
//
//	return res;
//}
//
//void Game_Destroy(Game* game)
//{
//	if (!game) return;
//
//	free(game);
//}
//
//void Game_Print(Game* game)
//{
//	printf("-------------------- Game --------------------\n\n");
//
//	for (int i = 0; i < GRID_W; i++)
//	{
//		printf("%d ", i);
//	}
//
//	for (int j = 0; j < GRID_H; j++)
//	{
//		putchar('\n');
//	
//		for (int i = 0; i < GRID_W; i++)
//		{
//			switch (game->grid[j][i])
//			{
//			case PLAYER_1:
//				printf("O ");
//				break;
//
//			case PLAYER_2:
//				printf("X ");
//				break;
//
//			default:
//				printf(". ");
//				break;
//			}
//		}
//	}
//
//	switch (game->turn)
//	{
//	case PLAYER_1:
//		printf("\n\nTurn: O \n\n");
//		break;
//
//	case PLAYER_2:
//		printf("\n\nTurn: X \n\n");
//		break;
//	}
//}
//
//void Game_MinimaxVSPlayer(void)
//{
//	Game* game = Game_New();
//
//	while (game->state == GAME_IN_PROGRESS)
//	{
//		Game_Print(game);
//
//		int move = -1;
//
//		if (game->turn == PLAYER_1)
//		{
//			printf("player >> ");
//			scanf("%d", &move);
//			putchar('\n');
//		}
//		else
//		{
//			move = AI_Minimax_GetMove(game, game->turn);
//			Sleep(500);
//			printf("minimax >> %d\n\n", move);
//		}
//
//		Game_PlayAt(game, move);
//	}
//
//	Game_Print(game);
//
//	switch (game->state)
//	{
//	case GAME_IS_TIED:
//		printf("##### Game is tied ! #####\n\n");
//		break;
//
//	default:
//		printf("##### GG player (%d) ! #####\n\n", game->state);
//		break;
//	}
//
//	Game_Destroy(game);
//}
//
//void Game_MinimaxVSNN(Network* net, int gameCount)
//{
//	FILE* file = fopen("../Data/scores.txt", "w");
//
//	if (!file)
//	{
//		printf("ERROR - Game_MinimaxVSNN() \n");
//		printf("ERROR - fopen() \n");
//		abort();
//	}
//	
//	int scores[3] = { 0 };
//
//	for (int i = 0; i < gameCount; i++)
//	{
//		Game* game = Game_New();
//
//		for (int j = 0; j < 4; j++)
//		{
//			int move = AI_Random_GetMove(game);
//			Game_PlayAt(game, move);
//		}
//
//		while (game->state == GAME_IN_PROGRESS)
//		{
//			int move = -1;
//
//			if (game->turn == PLAYER_1)
//			{
//				move = AI_NN_GetMove(game, net);
//			}
//			else
//			{
//				move = AI_Minimax_GetMove(game, game->turn);
//			}
//
//			Game_PlayAt(game, move);
//		}
//
//		if (i % 10 == 0)
//		{
//			Game_Print(game);
//
//			switch (game->state)
//			{
//			case GAME_IS_TIED:
//				scores[0]++;
//				printf("##### Game is tied ! #####\n\n");
//				break;
//
//			default:
//				scores[game->state]++;
//				printf("##### GG player (%d) ! #####\n\n", game->state);
//				break;
//			}
//		
//			printf("Score (%d): %d | %d | %d | %d\n\n", i, scores[0], scores[1], scores[2], scores[2] - scores[1]);
//		}
//
//		Game_Destroy(game);
//
//		fprintf(file, "%d\n", scores[2] - scores[1]);
//	}
//
//	fclose(file);
//}
//
//bool Game_CanPlayAt(Game* game, int column)
//{
//	bool outOfDimension = ((column < 0) || (column >= GRID_W));
//
//	return (!outOfDimension && (game->grid[0][column] == TOKEN_EMPTY));
//}
//
//void Game_PlayAt(Game* game, int column)
//{
//	assert(Game_CanPlayAt(game, column));
//
//	int line = 0;
//
//	while ((line + 1 < GRID_H) && (game->grid[line + 1][column] == TOKEN_EMPTY))
//	{
//		line++;
//	}
//
//	game->grid[line][column] = game->turn;
//	
//	int winner = Game_GetWinner(game);
//
//	if (winner != PLAYER_NONE)
//	{
//		game->state = winner;
//		return;
//	}
//
//	if (Game_IsTied(game))
//	{
//		game->state = GAME_IS_TIED;
//		return;
//	}
//
//	game->turn = game->turn == PLAYER_1 ? PLAYER_2 : PLAYER_1;
//}
//
//bool Game_IsTied(Game* game)
//{
//	for (int i = 0; i < GRID_W; i++)
//	{
//		if (game->grid[0][i] == TOKEN_EMPTY)
//		{
//			return false;
//		}
//	}
//
//	return true;
//}
//
//bool __Game_HasConnection(Game* game, int i, int j, Direction direction)
//{
//	TokenID token = game->grid[j][i];
//
//	for (int k = 0; k < 3; k++)
//	{
//		if (direction & LEFT)	i--;
//		if (direction & RIGHT)	i++;
//		if (direction & UP)		j--;
//
//		if ((i < 0) || (i >= GRID_W) ||
//			(j < 0) || (j >= GRID_H) ||
//			(game->grid[j][i] != token))
//		{
//			return false;
//		}
//	}
//
//	return true;
//}
//
//PlayerID Game_GetWinner(Game* game)
//{
//	for (int j = 0; j < GRID_H; j++)
//	{
//		for (int i = 0; i < GRID_W; i++)
//		{
//			TokenID token = game->grid[j][i];
//
//			if (token == TOKEN_EMPTY) continue;
//
//			if (__Game_HasConnection(game, i, j, LEFT) ||
//				__Game_HasConnection(game, i, j, UP) ||
//				__Game_HasConnection(game, i, j, LEFT + UP) ||
//				__Game_HasConnection(game, i, j, RIGHT + UP))
//			{
//				return token;
//			}
//		}
//	}
//
//	return PLAYER_NONE;
//}
//
//int Game_Heuristic(Game* game, PlayerID turn)
//{
//	// URL: https://www.christian-schmidt.fr/puissance4
//
//	int connections[GRID_H][GRID_W] = {
//		{3,  4,  5,  7,  5,  4,  3},
//		{4,  6,  8,  10, 8,  6,  4},
//		{5,  8,  11, 13, 11, 8,  5},
//		{5,  8,  11, 13, 11, 8,  5},
//		{4,  6,  8,  10, 8,  6,  4},
//		{3,  4,  5,  7,  5,  4,  3}
//	};
//
//	int res = 0;
//
//	for (int j = 0; j < GRID_H; j++)
//	{
//		for (int i = 0; i < GRID_W; i++)
//		{
//			TokenID token = game->grid[j][i];
//
//			if (token != TOKEN_EMPTY)
//			{
//				if (token == turn)
//				{
//					res += connections[j][i];
//				}
//				else
//				{
//					res -= connections[j][i];
//				}
//			}
//		}
//	}
//
//	return res;
//}
