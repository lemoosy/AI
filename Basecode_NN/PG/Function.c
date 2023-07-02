#include "Function.h"

Function* Function_New(char* name, int size, float* f, TypeID res, TypeID arg[MAX_ARG + 1])
{
	Function* function = (Function*)calloc(1, sizeof(Function));
	assert(function);

	function->name = _strdup(name);
	function->size = size;
	function->f = f;
	function->res = res;
	memcpy(function->arg, arg, sizeof(int) * (MAX_ARG + 1));

	return function;
}

Function* Function_Copy(Function* func)
{
	return func;
}

void Function_Destroy(Function* func)
{
	if (!func) return;

	free(func->name);
	free(func);
}

int Function_CompareRes(void* _func0, void* _func1)
{
	Function* func0 = (Function*)_func0;
	Function* func1 = (Function*)_func1;

	return (func0->res - func1->res);
}

void Function_Print(Function* func)
{
	if (func)
	{
		printf("%s", func->name);
	}
	else
	{
		printf("NULL");
	}
}

Function* Function_GetRandomByRes(DList*** F, TypeID res)
{
	int tabSize = (MAX_ARG + 1);
	int* tab = int_tab_random_norep(tabSize);
	int tabIndex = 0;

	DList* list = NULL;

	while (tabIndex < tabSize)
	{
		int i = tab[tabIndex];

		list = F[res][i];

		if (list->size > 0)
		{
			break;
		}

		tabIndex++;
	}

	if (tabIndex == tabSize)
	{
		printf("ERROR - Function_GetRandomByRes()\n");
		abort();
	}

	int k = int_random(0, list->size - 1);

	free(tab);

	return DList_Get(list, k);
}
