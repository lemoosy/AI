#pragma once

#include "../Settings.h"
#include "../Utils/DList.h"
#include "../Utils/Utils.h"

/// @brief Nombre maximum d'arguments pour une fonction.
#define MAX_ARG 3

/// @brief Types de retour.
typedef enum eTypeID { TYPE_NULL, TYPE_BOOL, TYPE_REAL, TYPE_COUNT } TypeID;

/// @brief Structure représentant une fonction (permet d'avoir plus d'informations sur une fonction).
typedef struct sFunction
{
	/// @brief Nom (pour l'affichage).
	char* name;
	
	/// @brief Nombre d'arguments.
	int size;

	/// @brief Fonction.
	void* f;

	/// @brief Type de retour.
	TypeID res;

	/// @brief Type des paramètres.
	TypeID arg[MAX_ARG + 1];
}Function;

/// @brief Crée une fonction.
Function* Function_Create(char* name, int size, float* f, TypeID res, TypeID arg[MAX_ARG + 1]);

/// @brief Renvoie le pointeur de 'func'.
Function* Function_Copy(Function* func);

/// @brief Détruit une fonction.
void Function_Destroy(Function* func);

/// @brief Compare 2 fonctions par rapport à leur type de retour et de leur type de paramètres.
int Function_Compare(void* _func0, void* _func1);

/// @brief Compare 2 fonctions par rapport à leur type de retour.
int Function_CompareRes(void* _func0, void* _func1);

/// @brief Affiche une fonction.
void Function_Print(Function* func);

/// @brief Renvoie une fonction aléatoire qui a comme type de retour 'res'.
Function* Function_GetRandomByRes(DList*** F, TypeID res);
