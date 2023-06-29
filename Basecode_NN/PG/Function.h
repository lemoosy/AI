#pragma once

#include "../Settings.h"

typedef enum eFunctionID
{
	// 0 argument:
	FUNCTION_INPUT		=	'x',

	// 1 argument:
	FUNCTION_SRT		=	'#',

	// 2 arguments:
	FUNCTION_ADD		=	'+',
	FUNCTION_SUB		=	'-',
	FUNCTION_MUL		=	'*',
	FUNCTION_DIV		=	'/'
}FunctionID;

float srt(float x);
float add(float a, float b);
float sub(float a, float b);
float multiply(float a, float b);
float divide(float a, float b);

typedef struct sFunction
{
	// ID de la fonction.
	FunctionID id;

	// Nombre d'arguments.
	int size;
	
	// 0 argument.
	float* input;

	// 1 argument.
	float (*f1)(float);
	
	// 2 arguments.
	float (*f2)(float, float);
}Function;

Function* Function_New(FunctionID id, float* input);
Function* Function_Copy(Function* func);
void      Function_Destroy(Function* func);
void      Function_Print(Function* func);
