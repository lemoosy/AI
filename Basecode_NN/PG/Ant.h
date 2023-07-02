#pragma once

#include "../Settings.h"
#include "../Utils/Utils.h"
#include "../Utils/DList.h"
#include "TreeAI.h"

#define GRID_W 10
#define GRID_H 10


typedef enum eGameState
{
	GAME_IN_PROGRESS = 0,
	GAME_IS_OVER
}GameState;

typedef enum eCellID
{
	CELL_EMPTY = 0,
	CELL_FOOD = 1
}CellID;

typedef enum eDirection
{
	LEFT,
	RIGHT,
	UP,
	DOWN
}Direction;

typedef struct sAnt
{
	// Position de la fourmi.
	int i, j;

	// Direction de la fourmi.
	Direction direction;

	// Nombre de nourritures récoltées.
	int score;
}Ant;

bool Ant_OutOfDimension(Ant ant);
bool Ant_OnFood(Ant ant);

// res = NONE
void* Ant_SetDirectionLeft(TreeNode* node);
void* Ant_SetDirectionRight(TreeNode* node);
void* Ant_SetDirectionUp(TreeNode* node);
void* Ant_SetDirectionDown(TreeNode* node);
void* Ant_Move(TreeNode* node);

// res = BOOL
void* Ant_AheadFood(void* node);

typedef struct sGame
{
	// État du jeu.
	GameState state;

	// Grille du jeu.
	int grid[GRID_H][GRID_W];

	// Fourmi.
	Ant ant;
}Game;

Game g_game;

Game Game_New(void);
void Game_Print(Game game);
bool Game_IsOver(Game game);
void Game_Update(Game* game);
