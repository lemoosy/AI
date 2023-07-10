#pragma once

#include "../Settings.h"

#ifdef GAME_SNAKE

#include "../SDL/Window.h"

#define GRID_W 10
#define GRID_H 10

typedef enum eCellID { CELL_EMPTY, CELL_SNAKE, CELL_FOOD } CellID;
typedef enum eDirection { N = 1, S = 2, W = 4, E = 8 } Direction;
typedef enum eGameState { GAME_IN_PROGRESS, GAME_IS_OVER, GAME_IS_FULL } GameState;
typedef enum eSnakeState { SNAKE_ALIVE, SNAKE_DEAD } SnakeState;

// Position:

typedef struct sPosition
{
	int i;
	int j;
}Position;

Position Position_Create(int i, int j);
bool     Position_Equal(Position pos0, Position pos1);
bool     Position_OutOfDimension(Position pos);
void     Position_Update(Position* pos, Direction dir);
bool     Position_Check(Position pos, Direction dir, CellID cell, CellID grid[][GRID_W]);

// Body:

typedef struct sBody
{
	Position pos;
	Direction dir;
	struct sBody* next;
}Body;

Body* Body_Create(Position pos, Direction dir);
void  Body_Destroy(Body* body);
Body* Body_Update(Body* body, Direction directionPrevious);

// Snake:

typedef struct sSnake
{
	SnakeState state;
	Body* head;
	Body* tail;
	int size;
}Snake;

Snake* Snake_Create(void);
void   Snake_Destroy(Snake* snake);
Body*  Snake_UpdatePosition(Snake* snake); // return tail (previous frame)
void   Snake_AddSize(Snake* snake, Body* tail);
void   Snake_SetDirection(Snake* snake, Direction direction);
void   Snake_ToGrid(Snake* snake, CellID grid[][GRID_W]); // (+) Update state

// Food:

Position* Food_Create(CellID grid[][GRID_W]); // (!) After Snake_ToGrid()
void      Food_ToGrid(Position food, CellID grid[][GRID_W]);

// Grid:

void Grid_Clear(CellID grid[][GRID_W]);

// Game:

typedef struct sGame
{
	GameState state;
	CellID grid[GRID_H][GRID_W];
	Snake* snake;
	Position* food;
}Game;

Game* Game_Create(void);
void  Game_Destroy(Game* game);
void  Game_Update(Game* game, Window* window);
void  Game_Draw(Game* game, Window* window);

// ------------------------------ TreeAI ------------------------------

#include "../PG/TreeAI.h"
#include "../Utils/Type/Float.h"

Game* g_game;

void __Snake_Fitness(Tree* tree, Window* window);

// TYPE_NULL

void* __Snake_SetDirectionN(void* node);
void* __Snake_SetDirectionS(void* node);
void* __Snake_SetDirectionW(void* node);
void* __Snake_SetDirectionE(void* node);

// TYPE_BOOL

void* __Snake_HeadBodyN(void* node);
void* __Snake_HeadBodyS(void* node);
void* __Snake_HeadBodyW(void* node);
void* __Snake_HeadBodyE(void* node);

void* __Snake_HeadFoodN(void* node);
void* __Snake_HeadFoodS(void* node);
void* __Snake_HeadFoodW(void* node);
void* __Snake_HeadFoodE(void* node);

void* __Snake_HeadWallN(void* node);
void* __Snake_HeadWallS(void* node);
void* __Snake_HeadWallW(void* node);
void* __Snake_HeadWallE(void* node);

void* __Snake_DirectionHeadIsN(void* node);
void* __Snake_DirectionHeadIsS(void* node);
void* __Snake_DirectionHeadIsW(void* node);
void* __Snake_DirectionHeadIsE(void* node);

void* __Snake_AheadFood(void* node);
void* __Snake_AheadBody(void* node);
void* __Snake_AheadWall2(void* node);

#endif // GAME_SNAKE
