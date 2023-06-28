#pragma once

#include "../Settings.h"
#include "../Utils/Utils.h"
#include "../Utils/DList.h"

#define GRID_W 10
#define GRID_H 10

typedef enum eGameState
{
	GAME_IN_PROGRESS = 0,
	GAME_IS_OVER
}GameState;

typedef enum eCellID
{
	CELL_EMPTY	=	0,
	CELL_FOOD	=	1
}CellID;

typedef enum eDirection
{
	LEFT	=	1 << 0,
	RIGHT	=	1 << 1,
	UP		=	1 << 2,
	DOWN	=	1 << 3,
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

inline bool Ant_OutOfDimension(Ant ant);
void        Ant_UpdatePosition(Ant* ant);

typedef struct sGame
{
	// État du jeu.
	GameState state;

	// Grille du jeu.
	int grid[GRID_H][GRID_W];

	// Direction de la fourmi.
	Ant ant;
}Game;

Game* Game_New(void);
Game* Game_Copy(Game* game);
void  Game_Destroy(Game* game);
void  Game_Print(Game* game);
bool  Game_IsOver(Game* game);
void  Game_Update(Game* game);

// AI

#define MAX_FUNCTION	6
#define MAX_DEPTH		4

typedef enum sFunctionID
{
	ADD = '+',
	SUB = '-',
	MUL = '*',
	DIV = '/',
	SRT = 's',
	VAL = 'x'
}FunctionID;

typedef struct sFunction
{
	// Nombre d'arguments.
	int size;

	// 0 argument(s).
	float* T;

	// 1 argument(s).
	float (*f1)(float);
	
	// 2 argument(s).
	float (*f2)(float, float);

	int id;
}Function;

// ------------------------------ Tree ------------------------------

typedef struct sTreeNode
{
	void* value;
	struct sTreeNode* L;
	struct sTreeNode* R;
}TreeNode;

typedef struct sTree
{
	TreeNode* root;
	float fitnessScore;
}Tree;

Tree*     Tree_New(void);
Tree*     Tree_Copy(Tree* tree, void* (*funcCopy)(void*));
void      Tree_Destroy(Tree* tree, void* (*funcDestroy)(void*));
int       Tree_GetSize(Tree* tree); // TODO (-)
void      Tree_Print(Tree* tree);
TreeNode* Tree_Get(Tree* tree, int index, TreeNode** parent);

Tree*     TreeAI_New(DList* F, DList* T);
float     TreeAI_Execute(Tree* tree);
void      TreeAI_UpdateFScore(Tree* tree, DList* F);
void      TreeAI_Crossover(Tree* t1, Tree* t2);
int       TreeAI_CompareFScore(Tree* t1, Tree* t2);

void      main2(void);
