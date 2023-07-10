#include "Void.h"

void Void_Swap(void** a, void** b)
{
	void* tmp = *a;
	*a = *b;
	*b = tmp;
}
