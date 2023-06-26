#pragma once

#include "../Settings.h"
#include "../Utils/Utils.h"

#define GRID_W 6
#define GRID_H 7

typedef enum eGameState
{
	GAME_IN_PROGRESS = 0,
	GAME_P1_WON,
	GAME_P2_WON,
	GAME_IS_OVER
}GameState;

typedef enum eDirection
{
	LEFT	=	1 << 0,
	RIGHT	=	1 << 1,
	UP		=	1 << 2,
	DOWN	=	1 << 3
}Direction;

typedef enum eCellID
{
	CELL_EMPTY = 0,
	CELL_P1 = 1,
	CELL_P2 = 2
}CellID;

typedef enum sPlayerID
{
	PLAYER_NONE,
	PLAYER_1 = 1,
	PLAYER_2 = 2
}PlayerID;

// Structure représentant une partie.
typedef struct sGame
{
	// État du jeu.
	GameState state;

	// Grille du jeu.
	CellID grid[GRID_H][GRID_W];

	// Variable indiquant à qui de jouer.
	PlayerID turn;
}Game;

// Crée une partie.
Game* Game_New();

// Détruit une partie.
void Game_Destroy(Game* game);

// Affiche une partie.
void Game_Print(Game* game);

// Vérifie si on peut placé un jeton à la colonne 'column'.
bool Game_CanPlayAt(Game* game, int column);

// Place un jeton à la colonne 'column'.
void Game_PlayAt(Game* game, int column);

bool Game_IsOver(Game* game);

PlayerID Game_GetWinner(Game* game);
