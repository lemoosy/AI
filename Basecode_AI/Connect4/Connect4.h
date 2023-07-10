#pragma once

#include "../Settings.h"

#ifdef GAME_CONNECT4

#define GRID_W 7
#define GRID_H 6

#include "../NN/Network.h"
#include "../Utils/Type/Int.h"

typedef enum eGameState
{
	GAME_IN_PROGRESS = 0,
	GAME_P1_WON = 1,
	GAME_P2_WON = 2,
	GAME_IS_TIED
}GameState;

typedef enum eDirection { N = 1, S = 2, W = 4, E = 8 } Direction;

typedef enum eTokenID
{
	TOKEN_EMPTY = 0,
	TOKEN_P1 = 1,
	TOKEN_P2 = 2
}TokenID;

typedef enum sPlayerID
{
	PLAYER_NONE,
	PLAYER_1 = 1,
	PLAYER_2 = 2
}PlayerID;

/// @brief Structure représentant une partie.
typedef struct sGame
{
	/// @brief État du jeu.
	GameState state;

	/// @brief Grille du jeu.
	TokenID grid[GRID_H][GRID_W];

	/// @brief Variable indiquant à qui le tour.
	PlayerID turn;
}Game;

/// @brief Crée une partie.
Game* Game_Create();

/// @brief Copie une partie.
Game* Game_Copy(Game* game);

/// @brief Détruit une partie.
void Game_Destroy(Game* game);

/// @brief Affiche une partie.
void Game_Print(Game* game);

/// @brief Lance une partie contre un minimax et un joueur.
void Game_MinimaxVSPlayer(void);

/// @brief Lance une partie contre un minimax et un réseau de neurones (le réseau de neurones copie/apprends le minimax).
void Game_MinimaxVSNN(Network* net, int gameCount);

/// @brief Vérifie si on peut placer un jeton sur une grille à la colonne [column].
bool Game_CanPlayAt(Game* game, int column);

/// @brief Place un jeton à la colonne [column] et actualise la partie.
void Game_PlayAt(Game* game, int column);

/// @brief Vérifie si la grille est pleine.
bool Game_IsFull(Game* game);

/// @brief Renvoie (s'il existe) le gagnant de la partie, sinon renvoie PLAYER_NONE.
PlayerID Game_GetWinner(Game* game);

/// @brief Évalue une partie pour le joueur [turn].
int Game_Heuristic(Game* game, PlayerID turn);

#endif // GAME_CONNECT4
