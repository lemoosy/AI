//#pragma once
//
//#include "../Settings.h"
//#include "../NN/Network.h"
//#include "../Utils/Utils.h"
//
//#define GRID_W 7
//#define GRID_H 6
//
//typedef enum eGameState
//{
//	GAME_IN_PROGRESS = 0,
//	GAME_P1_WON = 1,
//	GAME_P2_WON = 2,
//	GAME_IS_TIED
//}GameState;
//
//typedef enum eDirection
//{
//	LEFT = 1 << 0,
//	RIGHT = 1 << 1,
//	UP = 1 << 2,
//	DOWN = 1 << 3
//}Direction;
//
//typedef enum eTokenID
//{
//	TOKEN_EMPTY = 0,
//	TOKEN_P1 = 1,
//	TOKEN_P2 = 2
//}TokenID;
//
//typedef enum sPlayerID
//{
//	PLAYER_NONE,
//	PLAYER_1 = 1,
//	PLAYER_2 = 2
//}PlayerID;
//
//// Structure représentant une partie.
//typedef struct sGame
//{
//	// État du jeu.
//	GameState state;
//
//	// Grille du jeu.
//	TokenID grid[GRID_H][GRID_W];
//
//	// Variable indiquant à qui c'est le tour de jouer.
//	PlayerID turn;
//}Game;
//
//// Crée une partie.
//Game* Game_Create();
//
//// Copie une partie.
//Game* Game_Copy(Game* game);
//
//// Détruit une partie.
//void Game_Destroy(Game* game);
//
//// Affiche une partie.
//void Game_Print(Game* game);
//
//// Lance une partie contre un minimax.
//void Game_MinimaxVSPlayer(void);
//
//// Lance une partie contre un minimax.
//void Game_MinimaxVSNN(Network* net, int gameCount);
//
//// Vérifie si on peut placer un jeton sur la grille à la colonne 'column'.
//bool Game_CanPlayAt(Game* game, int column);
//
//// Place un jeton à la colonne 'column'.
//void Game_PlayAt(Game* game, int column);
//
//// Vérifie si la grille est pleine.
//bool Game_IsTied(Game* game);
//
//// Renvoie (s'il existe) le gagnant de la partie, sinon renvoie PLAYER_NONE.
//PlayerID Game_GetWinner(Game* game);
//
//// Évalue une partie pour le joueur 'turn'.
//int Game_Heuristic(Game* game, PlayerID turn);
