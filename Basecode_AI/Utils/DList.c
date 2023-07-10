#include "DList.h"

DNode* DNode_Create(void* value)
{
	DNode* node = (DNode*)calloc(1, sizeof(DNode));
	assert(node);

	node->value = value;

	return node;
}

DList* DList_Create(void)
{
	DList* list = (DList*)calloc(1, sizeof(DList));
	assert(list);

	list->sentinel = (DNode*)calloc(1, sizeof(DNode));
	assert(list->sentinel);

	list->sentinel->prev = list->sentinel;
	list->sentinel->next = list->sentinel;

	return list;
}

DList* DList_Copy(DList* list, void* (*dataCopy)(void*))
{
	if (!list) return NULL;

	DList* res = DList_Create();

	DNode* sent = list->sentinel;
	DNode* curr = sent->next;

	while (curr != sent)
	{
		DList_InsertLast(res, dataCopy(curr->value));
		curr = curr->next;
	}

	return res;
}

void DList_Destroy(DList* list, void (*dataDestroy)(void*))
{
	if (!list) return;

	DNode* remove;

	DNode* sent = list->sentinel;
	DNode* curr = sent->next;

	if (dataDestroy)
	{
		while (curr != sent)
		{
			remove = curr;
			curr = curr->next;
			dataDestroy(remove->value);
			free(remove);
		}
	}
	else
	{
		while (curr != sent)
		{
			remove = curr;
			curr = curr->next;
			free(remove);
		}
	}

	free(sent);
	free(list);
}

void DList_Print(DList* list, void (*dataPrint)(void*))
{
	printf("(size=%d) : ", list->size);

	DNode* sent = list->sentinel;
	DNode* curr = sent->next;

	while (curr != sent)
	{
		dataPrint(curr->value);
		curr = curr->next;
	}

	putchar('\n');
}

bool DList_IsEmpty(DList* list)
{
	return (list->size == 0);
}

bool DList_IsIn(DList* list, void* value, int (*dataCompare)(void*, void*))
{
	DNode* sent = list->sentinel;
	DNode* curr = sent->next;

	while (curr != sent)
	{
		if (dataCompare(curr->value, value) == 0)
		{
			return true;
		}

		curr = curr->next;
	}

	return false;
}

DNode* __DList_Get(DList* list, int index)
{
	DNode* curr = NULL;

	if ((0 <= index) && (index < list->size))
	{
		curr = list->sentinel->next;

		while (index > 0)
		{
			index -= 1;
			curr = curr->next;
		}
	}
	else if ((0 > index) && (index >= -list->size))
	{
		curr = list->sentinel->prev;

		while (index < -1)
		{
			index += 1;
			curr = curr->prev;
		}
	}

	return curr;
}

void* DList_Get(DList* list, int index)
{
	DNode* node = __DList_Get(list, index);

	return (node ? node->value : NULL);
}

void __DList_InsertFirst(DList* list, DNode* node)
{
	node->prev = list->sentinel;
	node->next = list->sentinel->next;

	node->prev->next = node;
	node->next->prev = node;

	list->size += 1;
}

void DList_InsertFirst(DList* list, void* value)
{
	DNode* node = DNode_Create(value);

	__DList_InsertFirst(list, node);
}

void __DList_InsertLast(DList* list, DNode* node)
{
	node->prev = list->sentinel->prev;
	node->next = list->sentinel;

	node->prev->next = node;
	node->next->prev = node;

	list->size += 1;
}

void DList_InsertLast(DList* list, void* value)
{
	DNode* node = DNode_Create(value);

	__DList_InsertLast(list, node);
}

void __DList_InsertSorted(DList* list, DNode* node, bool reverse, int (*dataCompare)(void*, void*))
{
	void* value = node->value;

	DNode* sent = list->sentinel;
	DNode* curr = sent->next;

	if (reverse)
	{
		while ((curr != sent) && (dataCompare(curr->value, value) > 0))
		{
			curr = curr->next;
		}
	}
	else
	{
		while ((curr != sent) && (dataCompare(curr->value, value) < 0))
		{
			curr = curr->next;
		}
	}

	node->prev = curr->prev;
	node->next = curr;

	node->prev->next = node;
	node->next->prev = node;

	list->size += 1;
}

void DList_InsertSorted(DList* list, void* value, bool reverse, int (*dataCompare)(void*, void*))
{
	DNode* node = DNode_Create(value);

	__DList_InsertSorted(list, node, reverse, dataCompare);
}

void __DList_InsertBefore(DList* list, DNode* node, int index)
{
	DNode* curr = __DList_Get(list, index);
	assert(curr);

	node->prev = curr->prev;
	node->next = curr;

	node->prev->next = node;
	node->next->prev = node;

	list->size += 1;
}

void DList_InsertBefore(DList* list, void* value, int index)
{
	DNode* node = DNode_Create(value);

	__DList_InsertBefore(list, node, index);
}

void __DList_InsertAfter(DList* list, DNode* node, int index)
{
	DNode* curr = __DList_Get(list, index);
	assert(curr);

	node->prev = curr;
	node->next = curr->next;

	node->prev->next = node;
	node->next->prev = node;

	list->size += 1;
}

void DList_InsertAfter(DList* list, void* value, int index)
{
	DNode* node = DNode_Create(value);

	__DList_InsertAfter(list, node, index);
}

DNode* __DList_FirstOf(DList* list, void* value, int (*dataCompare)(void*, void*))
{
	DNode* sent = list->sentinel;
	DNode* curr = sent->next;

	while ((curr != sent) && (dataCompare(value, curr->value) != 0))
	{
		curr = curr->next;
	}

	return curr;
}

void* DList_FirstOf(DList* list, void* value, int (*dataCompare)(void*, void*))
{
	DNode* node = __DList_FirstOf(list, value, dataCompare);

	return (node ? node->value : NULL);
}

DNode* __DList_LastOf(DList* list, void* value, int (*dataCompare)(void*, void*))
{
	DNode* sent = list->sentinel;
	DNode* curr = sent->prev;

	while ((curr != sent) && (dataCompare(value, curr->value) != 0))
	{
		curr = curr->prev;
	}

	return curr;
}

void* DList_LastOf(DList* list, void* value, int (*dataCompare)(void*, void*))
{
	DNode* node = __DList_LastOf(list, value, dataCompare);

	return (node ? node->value : NULL);
}

DNode* __DList_PopFirst(DList* list)
{
	assert(list->size > 0);

	DNode* node = list->sentinel->next;

	node->prev->next = node->next;
	node->next->prev = node->prev;

	list->size -= 1;

	return node;
}

void* DList_PopFirst(DList* list)
{
	DNode* node = __DList_PopFirst(list);

	void* value = node->value;

	free(node);

	return value;
}

DNode* __DList_PopLast(DList* list)
{
	assert(list->size > 0);

	DNode* node = list->sentinel->prev;

	node->prev->next = node->next;
	node->next->prev = node->prev;

	list->size -= 1;

	return node;
}

void* DList_PopLast(DList* list)
{
	DNode* node = __DList_PopLast(list);

	void* value = node->value;

	free(node);

	return value;
}

DNode* __DList_RemoveAt(DList* list, int index)
{
	DNode* node = __DList_Get(list, index);
	assert(node);

	node->prev->next = node->next;
	node->next->prev = node->prev;

	list->size -= 1;

	return node;
}

void* DList_RemoveAt(DList* list, int index)
{
	DNode* node = __DList_RemoveAt(list, index);

	void* value = node->value;

	free(node);

	return value;
}
