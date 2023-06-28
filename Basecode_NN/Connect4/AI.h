//#pragma once
//
//#include "../Settings.h"
//#include "../NN/Network.h"
//#include "../Utils/Utils.h"
//#include "Game.h"
//
//#define DEPTH_MAX 4
//
////
//typedef struct sAINode
//{
//    // Partie du noeud.
//    Game* game;
// 
//    // Colonne choisit pour cette partie.
//    int move;
//    
//    // Score de la partie.
//    int score;
//    
//    // Les 'GRID_W' possibilités.
//    struct sAINode* children[GRID_W];
//}AINode;
//
//// 
//typedef struct sAITree
//{
//    AINode* root;
//}AITree;
//
////
//int AI_Minimax_GetMove(Game* game, PlayerID turn);
//
//int AI_NN_GetMove(Game* game, Network* net);
//
////
//int AI_Random_GetMove(Game* game);
