#include "BTreeAI.h"

BTreeNode* BTreeAI_NewRec(int depth, DList* T, DList* F1, DList* F2)
{
	BTreeNode* node = (BTreeNode*)calloc(1, sizeof(BTreeNode));
	assert(node);

	Function* function = NULL;

	if (depth == 0)
	{
		function = (Function*)DList_Get(T, int_random(0, T->size - 1));
	}
	else
	{
		int size = (T->size + F1->size + F2->size);

		int random = int_random(0, size - 1);

		if (random < T->size)
		{
			function = (Function*)DList_Get(T, int_random(0, T->size - 1));
		}
		else if (random < T->size + F1->size)
		{
			function = (Function*)DList_Get(F1, int_random(0, F1->size - 1));
		}
		else
		{
			function = (Function*)DList_Get(F2, int_random(0, F2->size - 1));
		}
	}

	node->value = function;

	if (function->size > 0)
	{
		node->left = BTreeAI_NewRec(depth - 1, T, F1, F2);
	}

	if (function->size > 1)
	{
		node->right = BTreeAI_NewRec(depth - 1, T, F1, F2);
	}

	return node;
}

BTree* BTreeAI_New(DList* T, DList* F1, DList* F2)
{
	BTree* tree = BTree_New();

	tree->root = BTreeAI_NewRec(MAX_DEPTH, T, F1, F2);

	return tree;
}

float BTreeAI_ExecuteRec(BTreeNode* node)
{
	Function* function = (Function*)node->value;

	if (function->size == 0)
	{
		return *(function->input);
	}

	float a = BTreeAI_ExecuteRec(node->left);

	if (function->size == 1)
	{
		return function->f1(a);
	}

	float b = BTreeAI_ExecuteRec(node->right);

	return function->f2(a, b);
}

float BTreeAI_Execute(BTree* tree)
{
	return BTreeAI_ExecuteRec(tree->root);
}

void BTreeAI_UpdateScore(BTree* tree, DList* T)
{
	// SPÉ

	float triangles[10][2] = {
		{3.0f, 4.0f},
		{1.0f, 5.0f},
		{9.0f, 2.0f},
		{9.0f, 2.0f},
		{3.0f, 3.0f},
		{20.0f, 10.0f},
		{30.0f, 40.0f},
		{30.0f, 12.0f},
		{0.0f, 0.0f},
		{20.0f, 20.0f}
	};

	tree->score = 0.0f;

	Function* func0 = (Function*)DList_Get(T, 0);
	Function* func1 = (Function*)DList_Get(T, 1);

	float* a = func0->input;
	float* b = func1->input;

	for (int i = 0; i < 10; i++)
	{
		*a = triangles[i][0];
		*b = triangles[i][1];

		float res = sqrtf(*a * *a + *b * *b);
		float resBTree = BTreeAI_Execute(tree);

		tree->score += (res != resBTree);
	}
}

int BTreeAI_CompareScore(BTree* t1, BTree* t2)
{
	if (t1->score > t2->score)
	{
		return +1;
	}
	else if (t1->score < t2->score)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void BTreeAI_Crossover(BTree* t1, BTree* t2)
{
	int t1Size = BTree_GetSize(t1);
	int r1 = int_random(0, t1Size - 1);
	BTreeNode* p1 = NULL;
	BTreeNode* n1 = BTree_GetNode(t1, r1, &p1);

	int t2Size = BTree_GetSize(t2);
	int r2 = int_random(0, t2Size - 1);
	BTreeNode* p2 = NULL;
	BTreeNode* n2 = BTree_GetNode(t2, r2, &p2);

	if (p1)
	{
		if (p1->left == n1)
		{
			p1->left = n2;
		}
		else
		{
			p1->right = n2;
		}
	}
	else
	{
		t1->root = n2;
	}

	if (p2)
	{
		if (p2->left == n2)
		{
			p2->left = n1;
		}
		else
		{
			p2->right = n1;
		}
	}
	else
	{
		t2->root = n1;
	}
}

void BTreeAI_Mutation(BTree* tree, DList* T, DList* F1, DList* F2)
{
	int treeSize = BTree_GetSize(tree);
	
	BTreeNode* parent = NULL;
	BTreeNode* node = BTree_GetNode(tree, int_random(0, treeSize - 1), &parent);

	Function* func = (Function*)node->value;

	if (func->size == 0)
	{
		node->value = DList_Get(T, int_random(0, T->size - 1));
	}
	else if (func->size == 1)
	{
		node->value = DList_Get(F1, int_random(0, F1->size - 1));
	}
	else
	{
		node->value = DList_Get(F2, int_random(0, F2->size - 1));
	}
}
