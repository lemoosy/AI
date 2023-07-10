#pragma once

#include "../NN/Layer.h"
#include "../NN/Network.h"
#include "../Settings.h"
#include "../Utils/Mat.h"
#include "../Utils/Type/Int.h"
#include "Connect4.h"

#ifdef GAME_CONNECT4

// ------------------------------ Minimax ------------------------------

#define DEPTH_MAX 4

typedef struct sNodeAI
{
    Game* game;
    int move;
    int score;
    struct sNodeAI* children[GRID_W];
}NodeAI;

typedef struct sTreeAI
{
    NodeAI* root;
}TreeAI;

void TreeAI_DestroyRec(NodeAI* node);
void TreeAI_Destroy(TreeAI* tree);

NodeAI* TreeAI_Minimax_CreateRec(Game* game, PlayerID turn, int depth, bool minLayer, int A, int B);
TreeAI* TreeAI_Minimax_Create(Game* game);

// ------------------------------ AI ------------------------------

int AI_Minimax_GetMove(Game* game);
int AI_NN_GetMove(Game* game, Network* net);
int AI_Random_GetMove(Game* game);

#endif // GAME_CONNECT4
