#include "Data.h"

void* Bool_New(bool b)
{
	bool* res = (bool*)calloc(1, sizeof(bool));
	assert(res);

	*res = b;

	return res;
}

void* Bool_Not(void* _b)
{
	bool b = *(bool*)_b;

	return Bool_New(!b);
}

void* Float_New(float x)
{
	float* res = (float*)calloc(1, sizeof(float));
	assert(res);

	*res = x;

	return res;
}

void* Float_Srt(void* _x)
{
	float x = *(float*)_x;

	return Float_New(sqrtf(fabsf(x)));
}

void* Float_Add(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Float_New(x0 + x1);
}

void* Float_Sub(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Float_New(x0 - x1);
}

void* Float_Mul(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Float_New(x0 * x1);
}

void* Float_Div(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Float_New(x1 == 0.0f ? 1.0f : x0 / x1);
}

void* Float_Sup(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Bool_New(x0 > x1);
}

void* Float_Inf(void* _x0, void* _x1)
{
	float x0 = *(float*)_x0;
	float x1 = *(float*)_x1;

	return Bool_New(x0 < x1);
}
