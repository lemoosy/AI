#pragma once

#include "Settings.h"

typedef enum eFunctionID
{
	FUNCTION_LINEAR,
	FUNCTION_SIGMOID,
	FUNCTION_TANH,
	FUNCTION_RELU,
	FUNCTION_SOFTMAX
}FunctionID;

float linear(float x);
float linearDer(float x);

float sigmoid(float x);
float sigmoidDer(float x);

float ReLU(float x);
float ReLUDer(float x);

float tanhfDer(float x);
