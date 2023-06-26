#include "Utils.h"

float float_random(float a, float b)
{
	float res = rand();	// [0, RAND_MAX]

	res /= RAND_MAX;	// [0, 1]
	res *= (b - a);		// [0, (b - a)]
	res += a;			// [a, b]

	return res;
}

int int_random(int a, int b)
{
	return (a + rand() % (b - a + 1));
}

void int_swap(int* a, int* b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

int* int_tab(int size)
{
	int* tab = (int*)calloc(size, sizeof(int));
	assert(tab);

	for (int i = 0; i < size; i++)
	{
		tab[i] = i;
	}

	return tab;
}

int* int_tab_random_norep(int size)
{
	int* tab = int_tab(size);

	for (int i = 0; i < size; i++)
	{
		int_swap(&(tab[i]), &(tab[int_random(0, size - 1)]));
	}

	return tab;
}
