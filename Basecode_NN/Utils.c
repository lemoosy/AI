#include "Utils.h"

float Float_Random(float a, float b)
{
	float r = rand();	// [0.0f, RAND_MAX]

	r /= RAND_MAX;		// [0.0f, 1.0f]
	r *= (b - a);		// [0.0f, (b - a)]
	r += a;				// [a, b]

	return r;
}
