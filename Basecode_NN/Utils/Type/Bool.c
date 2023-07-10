#include "Bool.h"

void* Bool_Create(bool b)
{
	bool* res = (bool*)calloc(1, sizeof(bool));
	assert(res);

	*res = b;

	return res;
}

void Bool_Print(void* _b)
{
	if (_b)
	{
		bool b = *(bool*)_b;

		if (b)
		{
			printf("true ");
		}
		else
		{
			printf("false ");
		}
	}
	else
	{
		printf("NULL ");
	}
}

void* Bool_Not(void* _b)
{
	bool b = *(bool*)_b;

	return Bool_Create(!b);
}

void* Bool_And(void* _b0, void* _b1)
{
	bool b0 = *(bool*)_b0;
	bool b1 = *(bool*)_b1;

	return Bool_Create(b0 && b1);
}

void* Bool_Or(void* _b0, void* _b1)
{
	bool b0 = *(bool*)_b0;
	bool b1 = *(bool*)_b1;

	return Bool_Create(b0 || b1);
}
