#include "BinHeap.h"

BinHeap* BinHeap_Create(bool minimum, int capacity)
{
	assert(capacity > 0);

	BinHeap* heap = (BinHeap*)calloc(1, sizeof(BinHeap));
	assert(heap);

	heap->minimum = minimum;

	heap->values = (void**)calloc(capacity, sizeof(void*));
	assert(heap->values);

	heap->capacity = capacity;

	return heap;
}

void BinHeap_Destroy(BinHeap* heap, void (*dataDestroy)(void*))
{
	if (!heap) return;

	int size = heap->size;

	if (dataDestroy)
	{
		for (int i = 0; i < size; i++)
		{
			dataDestroy(heap->values[i]);
		}
	}

	free(heap->values);
	free(heap);
}

void BinHeap_Print(BinHeap* heap, void (*dataPrint)(void*))
{
	printf("(size=%d) : ", heap->size);

	int size = heap->size;

	for (int i = 0; i < size; i++)
	{
		dataPrint(heap->values[i]);
	}

	putchar('\n');
}

void BinHeap_Insert(BinHeap* heap, void* value, int (*dataCompare)(void*, void*))
{
	assert(heap->size < heap->capacity);

	int childIdx = heap->size;
	int parentIdx = (childIdx - 1) / 2;

	heap->values[childIdx] = value;
	heap->size += 1;

	bool minimum = heap->minimum;

	while (1)
	{
		void* parent = heap->values[parentIdx];
		void* child = heap->values[childIdx];

		if (minimum && (dataCompare(parent, child) > 0))
		{
			Void_Swap(&(heap->values[parentIdx]), &(heap->values[childIdx]));
		}
		else if (!minimum && (dataCompare(parent, child) < 0))
		{
			Void_Swap(&(heap->values[parentIdx]), &(heap->values[childIdx]));
		}
		else
		{
			break;
		}

		childIdx = parentIdx;
		parentIdx = (childIdx - 1) / 2;
	}
}

void* BinHeap_PopFirst(BinHeap* heap, int (*dataCompare)(void*, void*))
{
	assert(heap->size > 0);

	void* res = heap->values[0];

	heap->values[0] = heap->values[heap->size - 1];
	heap->size -= 1;

	int parentIdx = 0;
	int leftIdx = 1;
	int rightIdx = 2;

	bool minimum = heap->minimum;

	while (1)
	{
		int childIdx = -1;

		if ((leftIdx < heap->size) && (rightIdx < heap->size))
		{
			if (minimum && (dataCompare(heap->values[leftIdx], heap->values[rightIdx]) < 0))
			{
				childIdx = leftIdx;
			}
			else if (!minimum && (dataCompare(heap->values[leftIdx], heap->values[rightIdx]) > 0))
			{
				childIdx = leftIdx;
			}
			else
			{
				childIdx = rightIdx;
			}
		}
		else if (leftIdx < heap->size)
		{
			childIdx = leftIdx;
		}
		else
		{
			break;
		}
		
		Void_Swap(&(heap->values[parentIdx]), &(heap->values[childIdx]));

		parentIdx = childIdx;
		leftIdx = ((2 * childIdx) + 1);
		rightIdx = ((2 * childIdx) + 2);
	}

	return res;
}
