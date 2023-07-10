#include "FunctionID.h"

float linear(float x)
{
	return x;
}

float linearDer(float x)
{
	return 1.0f;
}

float sigmoid(float x)
{
	return (1.0f / (1.0f + expf(-x)));
}

float sigmoidDer(float x)
{
	float res = sigmoid(x);

	return (res * (1.0f - res));
}

float ReLU(float x)
{
	return ((x > 0.0f) ? x : 0.0f);
}

float ReLUDer(float x)
{
	return ((x > 0.0f) ? 1.0f : 0.0f);
}

float tanhfDer(float x)
{
	float res = tanhf(x);

	return (1.0f - (res * res));
}
