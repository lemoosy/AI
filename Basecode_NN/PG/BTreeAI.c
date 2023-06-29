#include "BTreeAI.h"

BTreeNode* BTreeAI_NewRec(int depth, DList* F[MAX_ARG])
{
	BTreeNode* node = (BTreeNode*)calloc(1, sizeof(BTreeNode));
	assert(node);

	Function* function = NULL;

	if (depth == 0)
	{
		function = (Function*)DList_Get(F[0], int_random(0, F[0]->size - 1));
	}
	else
	{
		int i = int_random(0, MAX_ARG - 1);
		int j = int_random(0, F[i]->size - 1);

		function = (Function*)DList_Get(F[i], j);
	}

	node->value = function;

	if (function->size > 0)
	{
		node->left = BTreeAI_NewRec(depth - 1, F);
	}

	if (function->size > 1)
	{
		node->right = BTreeAI_NewRec(depth - 1, F);
	}

	return node;
}

BTree* BTreeAI_New(DList* F[MAX_ARG])
{
	BTree* tree = BTree_New();

	tree->root = BTreeAI_NewRec(MAX_DEPTH, F);

	return tree;
}

float BTreeAI_ExecuteRec(BTreeNode* node)
{
	Function* function = (Function*)node->value;

	if (function->size == 0)
	{
		return *((float*)function->f);
	}

	float a = BTreeAI_ExecuteRec(node->left);

	if (function->size == 1)
	{
		float (*f1)(float) = (float (*)(float))function->f;
		return f1(a);
	}

	float b = BTreeAI_ExecuteRec(node->right);

	float (*f2)(float, float) = (float (*)(float, float))function->f;
	return f2(a, b);
}

float BTreeAI_Execute(BTree* tree)
{
	return BTreeAI_ExecuteRec(tree->root);
}

void BTreeAI_UpdateScore(BTree* tree, DList* F[MAX_ARG])
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

	Function* func0 = (Function*)DList_Get(F[0], 0);
	Function* func1 = (Function*)DList_Get(F[0], 1);

	float* a = (float*)func0->f;
	float* b = (float*)func1->f;

	for (int i = 0; i < 10; i++)
	{
		*a = triangles[i][0];
		*b = triangles[i][1];

		float res = sqrtf(*a * *a + *b * *b);
		float resTree = BTreeAI_Execute(tree);

		tree->score += (res != resTree);
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

void BTreeAI_Mutation(BTree* tree, DList* F[MAX_ARG])
{
	int treeSize = BTree_GetSize(tree);
	
	BTreeNode* parent = NULL;
	BTreeNode* node = BTree_GetNode(tree, int_random(0, treeSize - 1), &parent);

	Function* func = (Function*)node->value;

	node->value = DList_Get(F[func->size], int_random(0, F[func->size]->size - 1));
}
