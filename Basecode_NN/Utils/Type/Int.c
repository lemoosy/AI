#include "Int.h"

void* Int_Create(int n)
{
	int* res = (int*)calloc(1, sizeof(int));
	assert(res);

	*res = n;

	return res;
}

void Int_Print(void* _n)
{
	if (_n)
	{
		int n = *(int*)_n;

		printf("%d ", n);
	}
	else
	{
		printf("NULL ");
	}
}

int Int_Compare(void* _n0, void* _n1)
{
	int n0 = *(int*)_n0;
	int n1 = *(int*)_n1;

	return (n0 - n1);
}

void* Int_Add(void* _n0, void* _n1)
{
	int n0 = *(int*)_n0;
	int n1 = *(int*)_n1;

	return Int_Create(n0 + n1);
}

void* Int_Sub(void* _n0, void* _n1)
{
	int n0 = *(int*)_n0;
	int n1 = *(int*)_n1;

	return Int_Create(n0 - n1);
}

void* Int_Mul(void* _n0, void* _n1)
{
	int n0 = *(int*)_n0;
	int n1 = *(int*)_n1;

	return Int_Create(n0 * n1);
}

void* Int_Div(void* _n0, void* _n1)
{
	int n0 = *(int*)_n0;
	int n1 = *(int*)_n1;

	return Int_Create(n1 == 0 ? 1 : n0 / n1);
}

void* Int_Equal(void* _n0, void* _n1)
{
	int n0 = *(int*)_n0;
	int n1 = *(int*)_n1;

	return Bool_Create(n0 == n1);
}

void* Int_Sup(void* _n0, void* _n1)
{
	int n0 = *(int*)_n0;
	int n1 = *(int*)_n1;

	return Bool_Create(n0 > n1);
}

void* Int_Inf(void* _n0, void* _n1)
{
	int n0 = *(int*)_n0;
	int n1 = *(int*)_n1;

	return Bool_Create(n0 < n1);
}

void* Int_SupEqual(void* _n0, void* _n1)
{
	int n0 = *(int*)_n0;
	int n1 = *(int*)_n1;

	return Bool_Create(n0 >= n1);
}

void* Int_InfEqual(void* _n0, void* _n1)
{
	int n0 = *(int*)_n0;
	int n1 = *(int*)_n1;

	return Bool_Create(n0 <= n1);
}

int Int_Random(int n0, int n1)
{
	assert(n0 <= n1);

	return (n0 + rand() % (n1 - n0 + 1));
}

int* Int_Tab(int size)
{
	assert(size > 0);

	int* tab = (int*)calloc(size, sizeof(int));
	assert(tab);

	for (int i = 0; i < size; i++)
	{
		tab[i] = i;
	}

	return tab;
}

void Int_Swap(int* n0, int* n1)
{
	*n0 = *n0 ^ *n1;
	*n1 = *n0 ^ *n1;
	*n0 = *n0 ^ *n1;
}

int* Int_TabRandomNoRep(int size)
{
	int* tab = Int_Tab(size);

	for (int i = 0; i < size; i++)
	{
		Int_Swap(&(tab[i]), &(tab[Int_Random(0, size - 1)]));
	}

	return tab;
}
