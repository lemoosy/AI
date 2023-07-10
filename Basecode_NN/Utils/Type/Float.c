#include "Float.h"

void* Float_Create(float x)
{
	float* res = (float*)calloc(1, sizeof(float));
	assert(res);

	*res = x;

	return res;
}

void Float_Print(void* _x)
{
	if (_x)
	{
		float x = *(float*)_x;

		printf("%.2f ", x);
	}
	else
	{
		printf("NULL ");
	}
}

int Float_Compare(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	if (x0 > x1)
	{
		return +1;
	}
	else if (x1 < x0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void* Float_Srt(void* _x)
{
	float x = *(float*)_x;

	return Float_Create(sqrtf(fabsf(x)));
}

void* Float_Add(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Float_Create(x0 + x1);
}

void* Float_Sub(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Float_Create(x0 - x1);
}

void* Float_Mul(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Float_Create(x0 * x1);
}

void* Float_Div(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Float_Create(x1 == 0.0f ? 1.0f : x0 / x1);
}

void* Float_Equal(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Bool_Create(x0 == x1);
}

void* Float_Sup(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Bool_Create(x0 > x1);
}

void* Float_Inf(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Bool_Create(x0 < x1);
}

void* Float_SupEqual(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Bool_Create(x0 >= x1);
}

void* Float_InfEqual(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Bool_Create(x0 <= x1);
}

float Float_Random(float x0, float x1)
{
	assert(x0 <= x1);

	float res = rand();	// [0, RAND_MAX]

	res /= RAND_MAX;	// [0, 1]
	res *= (x1 - x0);	// [0, (x1 - x0)]
	res += x0;			// [x0, x1]

	return res;
}
