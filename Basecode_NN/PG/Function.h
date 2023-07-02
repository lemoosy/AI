#pragma once

#include "../Settings.h"
#include "../Utils/DList.h"
#include "../Utils/Utils.h"

#define MAX_ARG 3

typedef enum eTypeID
{
	TYPE_NONE,
	TYPE_BOOL,
	TYPE_REAL,

	TYPE_COUNT
}TypeID;

typedef struct sFunction
{
	// Nom pour l'affichage.
	char* name;
	
	// Nombre d'arguments.
	int size;

	// Fonction.
	void* f;

	// Type de retour.
	TypeID res;

	// Type des paramètres.
	TypeID arg[MAX_ARG + 1];
}Function;

Function* Function_New(char* name, int size, float* f, TypeID res, TypeID arg[MAX_ARG + 1]);
Function* Function_Copy(Function* func);
void      Function_Destroy(Function* func);
int       Function_CompareRes(void* _func0, void* _func1);
void      Function_Print(Function* func);
Function* Function_GetRandomByRes(DList*** F, TypeID res);
