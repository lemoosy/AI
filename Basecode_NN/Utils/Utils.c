#include "Utils.h"

float float_random(float a, float b)
{
	float r = rand();	// [0.0f, RAND_MAX]

	r /= RAND_MAX;		// [0.0f, 1.0f]
	r *= (b - a);		// [0.0f, (b - a)]
	r += a;				// [a, b]

	return r;
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

int* int_tab_random(int size)
{
	int* tab = (int*)calloc(size, sizeof(int));
	assert(tab);

	for (int i = 0; i < size; i++)
	{
		tab[i] = int_random(0, size - 1);
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
