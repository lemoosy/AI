#include "TreeAI.h"

// ------------------------------ Fonctions basiques ------------------------------

// Type de retour: TYPE_NULL

void* __progn(TreeNode* node)
{
	for (int i = 0; i < MAX_CHILDREN; i++)
	{
		if (node->children[i])
		{
			TreeAI_ExecuteRec(node->children[i]);
		}
		else
		{
			break;
		}
	}

	return NULL;
}

// Type de retour: TYPE_REAL

void* __not(TreeNode* node)
{
	void* _b = TreeAI_ExecuteRec(node->children[0]);

	void* res = Bool_Not(_b);
	
	free(_b);

	return res;
}

void* __srt(TreeNode* node)
{
	void* _x = TreeAI_ExecuteRec(node->children[0]);

	void* res = Float_Srt(_x);

	free(_x);

	return res;
}

void* __add(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Add(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* __sub(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Sub(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* __mul(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Mul(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* __div(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Div(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

// Type de retour: TYPE_BOOL

void* __equal(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Equal(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* __sup(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Sup(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* __inf(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Inf(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* __and(TreeNode* node)
{
	bool* res = (bool*)calloc(1, sizeof(bool));
	assert(res);

	bool* b0 = (bool*)TreeAI_ExecuteRec(node->children[0]);

	if (*b0 == true)
	{
		free(b0);
		
		return res;
	}

	bool* b1 = (bool*)TreeAI_ExecuteRec(node->children[1]);

	*res = *b1;

	free(b0);
	free(b1);
	
	return res;
}

void* __or(TreeNode* node)
{
	bool* res = (bool*)calloc(1, sizeof(bool));
	assert(res);

	bool* b0 = (bool*)TreeAI_ExecuteRec(node->children[0]);

	if (*b0 == true)
	{
		*res = true;

		free(b0);
		
		return res;
	}

	bool* b1 = (bool*)TreeAI_ExecuteRec(node->children[1]);

	*res = *b1;
	
	free(b0);
	free(b1);
	
	return res;
}

// Type de retour: *

void* __if(TreeNode* node)
{
	bool* b = (bool*)TreeAI_ExecuteRec(node->children[0]);

	if (*b == true)
	{
		free(b);
		return TreeAI_ExecuteRec(node->children[1]);
	}
	else
	{
		free(b);
		return TreeAI_ExecuteRec(node->children[2]);
	}
}

// ------------------------------ TreeAI >> Programme ------------------------------

TreeNode* TreeAI_CreateRec(DList*** F, TypeID res, int depth)
{
	TreeNode* node = (TreeNode*)calloc(1, sizeof(TreeNode));
	assert(node);

	Function* function = NULL;

	if (depth == 0)
	{
		function = (Function*)DList_Get(F[res][0], Int_Random(0, F[res][0]->size - 1));
	}
	else
	{
		function = Function_GetRandomByRes(F, res);
	}

	if (function == NULL)
	{
		printf("ERROR - TreeAI_CreateRec() \n");
		abort();
	}

	node->value = function;

	for (int i = 0; i < function->size; i++)
	{
		node->children[i] = TreeAI_CreateRec(F, function->arg[i], depth - 1);
	}

	return node;
}

Tree* TreeAI_Create(DList*** F, TypeID res, int depth)
{
	Tree* tree = Tree_Create();

	tree->root = TreeAI_CreateRec(F, res, depth);

	Tree_UpdateSize(tree);

	return tree;
}

void* TreeAI_ExecuteRec(TreeNode* node)
{
	Function* function = (Function*)node->value;

	void* (*f)(TreeNode*) = (void* (*)(TreeNode*))function->f;

	return f(node);
}

void* TreeAI_Execute(Tree* tree)
{
	return TreeAI_ExecuteRec(tree->root);
}

int TreeAI_CompareScore(Tree* tree0, Tree* tree1)
{
	if (tree0->score > tree1->score)
	{
		return +1;
	}
	else if (tree0->score < tree1->score)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void TreeAI_Crossover(Tree* tree0, Tree* tree1)
{
	if (tree0 == tree1) return;

	int treeSize0 = Tree_GetSize(tree0);
	int treeSize1 = Tree_GetSize(tree1);

	TreeSearch* search0 = Tree_GetNodeByIndex(tree0, Int_Random(0, treeSize0 - 1));
	Function* function0 = (Function*)search0->node->value;

	DList* list = Tree_GetNodeByValue(tree1, function0, &Function_CompareRes);

	if (list->size > 0)
	{
		int* tab = Int_TabRandomNoRep(list->size);

		for (int i = 0; i < list->size; i++)
		{
			TreeSearch* search1 = (TreeSearch*)DList_Get(list, tab[i]);

			if ((treeSize0 - search0->node->size + search1->node->size < MAX_NODE) &&
				(treeSize1 - search1->node->size + search0->node->size < MAX_NODE))
			{
				if (search0->parent)
				{
					search0->parent->children[search0->child] = search1->node;
				}
				else
				{
					tree0->root = search1->node;
				}

				Tree_UpdateSize(tree0);

				if (search1->parent)
				{
					search1->parent->children[search1->child] = search0->node;
				}
				else
				{
					tree1->root = search0->node;
				}

				Tree_UpdateSize(tree1);

				break;
			}
		}

		free(tab);
	}

	free(search0);
	DList_Destroy(list, &free);
}

void TreeAI_Mutation(Tree* tree, DList*** F)
{
	int treeSize = Tree_GetSize(tree);

	TreeSearch* search = Tree_GetNodeByIndex(tree, Int_Random(0, treeSize - 1));

	Function* funcOld = (Function*)search->node->value;
	
	DList* list = F[funcOld->res][funcOld->size];

	Function* funcNew = (Function*)DList_Get(list, Int_Random(0, list->size - 1));

	if (Function_Compare(funcOld, funcNew) == 0)
	{
		search->node->value = funcNew;
	}

	free(search);
}
