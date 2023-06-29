#include "Function.h"

float srt(float x)
{
	return sqrtf(fabsf(x));
}

float add(float a, float b)
{
	return (a + b);
}

float sub(float a, float b)
{
	return (a - b);
}

float multiply(float a, float b)
{
	return (a * b);
}

float divide(float a, float b)
{
	return ((b == 0.0f) ? 1.0f : (a / b));
}

// ------------------------------------------------------------------------------------------

Function* Function_New(FunctionID id, float* input)
{
	Function* func = (Function*)calloc(1, sizeof(Function));
	assert(func);

	func->id = id;

	switch (id)
	{
	case FUNCTION_INPUT:
		func->input = input;
		break;

	case FUNCTION_SRT:
		func->size = 1;
		func->f1 = &srt;
		break;

	case FUNCTION_ADD:
		func->size = 2;
		func->f2 = &add;
		break;

	case FUNCTION_SUB:
		func->size = 2;
		func->f2 = &sub;
		break;

	case FUNCTION_MUL:
		func->size = 2;
		func->f2 = &multiply;
		break;

	case FUNCTION_DIV:
		func->size = 2;
		func->f2 = &divide;
		break;

	default:
		printf("ERROR - Function_New() \n");
		printf("ERROR - [id=%d] \n", id);
		abort();
		break;
	}

	return func;
}

Function* Function_Copy(Function* func)
{
	Function* res = (Function*)calloc(1, sizeof(Function));
	assert(res);

	*res = *func;

	return res;
}

void Function_Destroy(Function* func)
{
	if (!func) return;

	if (func->input) free(func->input);
	free(func);
}

void Function_Print(Function* func)
{
	if (func)
	{
		printf("[%c]", func->id);
	}
	else
	{
		printf("[NULL]");
	}
}
