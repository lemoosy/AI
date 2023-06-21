#include "Utils.h"

float float_random(float a, float b)
{
	float r = rand();	// [0.0f, RAND_MAX]

	r /= RAND_MAX;		// [0.0f, 1.0f]
	r *= (b - a);		// [0.0f, (b - a)]
	r += a;				// [a, b]

	return r;
}

float sigmoid(float x)
{
	return (1.0f / (1.0f + expf(-x)));
}

float sigmoidDer(float x)
{
	return (sigmoid(x) * (1.0f - sigmoid(x)));
}
