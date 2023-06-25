#include "Data.h"

data Data_Add(data a, data b)
{
	return (a + b);
}

data Data_Sub(data a, data b)
{
	return (a - b);
}

data Data_Multiply(data a, data b)
{
	return (a * b);
}

data Data_Divide(data a, data b)
{
	assert(b != (data)0);

	return (a / b);
}

data Data_Random(data a, data b)
{
	assert(a <= b);

	data r = rand();	// [0, RAND_MAX]

	r /= RAND_MAX;		// [0, 1]
	r *= (b - a);		// [0, (b - a)]
	r += a;				// [a, b]

	return r;
}
