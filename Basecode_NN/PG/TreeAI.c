#include "TreeAI.h"

TreeNode* TreeAI_NewRec(int depth, DList*** F, TypeID res)
{
	TreeNode* node = (TreeNode*)calloc(1, sizeof(TreeNode));
	assert(node);
	
	Function* function = NULL;

	if (depth == 0)
	{
		function = (Function*)DList_Get(F[res][0], int_random(0, F[res][0]->size - 1));
	}
	else
	{
		function = Function_GetRandomByRes(F, res);
	}

	if (function == NULL)
	{
		printf("ERROR - TreeAI_NewRec() \n");
		abort();
	}

	node->value = function;

	for (int i = 0; i < function->size; i++)
	{
		node->children[i] = TreeAI_NewRec(depth - 1, F, function->arg[i]);
	}

	return node;
}

Tree* TreeAI_New(DList*** F, TypeID res)
{
	Tree* tree = Tree_New();

	tree->root = TreeAI_NewRec(MAX_DEPTH, F, res);

	return tree;
}

// ------------------------------ TreeAI_Execute() ------------------------------

void* _in0(TreeNode* node)
{
	return Float_New(in0);
}

void* _in1(TreeNode* node)
{
	return Float_New(in1);
}

void* _in2(TreeNode* node)
{
	return Bool_New(in2);
}

void* _not(TreeNode* node)
{
	void* _b = TreeAI_ExecuteRec(node->children[0]);

	void* res = Bool_Not(_b);
	
	free(_b);

	return res;
}

void* _srt(TreeNode* node)
{
	void* _x = TreeAI_ExecuteRec(node->children[0]);

	void* res = Float_Srt(_x);

	free(_x);

	return res;
}

void* _add(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Add(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* _sub(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Sub(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* _mul(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Mul(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* _div(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Div(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* _sup(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Sup(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* _inf(TreeNode* node)
{
	void* _x0 = TreeAI_ExecuteRec(node->children[0]);
	void* _x1 = TreeAI_ExecuteRec(node->children[1]);

	void* res = Float_Inf(_x0, _x1);

	free(_x0);
	free(_x1);

	return res;
}

void* _and(TreeNode* node)
{
	bool* res = (bool*)calloc(1, sizeof(bool));
	assert(res);

	bool* b0 = (bool*)TreeAI_ExecuteRec(node->children[0]);

	if (*b0 == false)
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

void* _or(TreeNode* node)
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

void* _if(TreeNode* node)
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

void* _progn(TreeNode* node)
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

// ------------------------------------------------------------------------------

void TreeAI_UpdateScore(Tree* tree, bool display)
{
	//// SPÉ: Pythagore

	//float triangles[10][2] = {
	//	{3.0f, 4.0f},
	//	{1.0f, 5.0f},
	//	{9.0f, 2.0f},
	//	{9.0f, 2.0f},
	//	{3.0f, 3.0f},
	//	{20.0f, 10.0f},
	//	{30.0f, 40.0f},
	//	{30.0f, 12.0f},
	//	{0.0f, 0.0f},
	//	{20.0f, 20.0f}
	//};

	//tree->score = 0.0f;

	//for (int i = 0; i < 10; i++)
	//{
	//	in0 = triangles[i][0];
	//	in1 = triangles[i][1];

	//	float res = sqrtf(in0 * in0 + in1 * in1);
	//	
	//	void* _resTree = TreeAI_Execute(tree);
	//	float resTree = *(float*)_resTree;
	//	if (_resTree) free(_resTree);

	//	tree->score += (res != resTree);
	//}

	g_game = Game_New();

	int iter = 0;

	while (g_game.state != GAME_IS_OVER && g_game.state != GAME_IS_FINISH && iter < 100)
	{
		int score = g_game.ant.score;
		TreeAI_Execute(tree);
		iter++;
		if (score != g_game.ant.score)
			iter = 0;
	}

	int res0 = g_game.state == GAME_IS_OVER;
	int res1 = g_game.state == GAME_IS_FINISH;

	tree->score = g_game.ant.score;
	
	if (res1)
	{
		tree->score = 100;
	}

	if (res0)
	{
		tree->score -= 10;
	}
}

int TreeAI_CompareScore(Tree* t0, Tree* t1)
{
	if (t0->score < t1->score)
	{
		return +1;
	}
	else if (t0->score > t1->score)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void TreeAI_Crossover(Tree* treeChild, Tree* treeParent)
{
	if (treeChild == treeParent) return;

	int treeChildSize = Tree_GetSize(treeChild);
	int index = int_random(0, treeChildSize - 1);
	TreeNode* parent = NULL;
	int child = -1;
	TreeNode* node = Tree_GetNode(treeChild, index, &parent, &child);


	if (!node) abort();

	Function* func = (Function*)node->value;

	DList* list = Tree_GetNodeList(treeParent, func, &Function_CompareRes);

	if (list->size > 0)
	{
		int r = int_random(0, list->size - 1);

		TreeNode* t2Child = (TreeNode*)DList_Get(list, r);

		TreeNode* insert = Tree_CopyRec(t2Child, &Function_Copy);

		Tree_DestroyRec(node, NULL);

		if (parent)
		{
			parent->children[child] = insert;
		}
		else
		{
			treeChild->root = insert;
		}
	}

	DList_Destroy(list, NULL);
}

void TreeAI_Mutation(Tree* tree, DList*** F)
{
	int treeSize = Tree_GetSize(tree);

	TreeNode* parent = NULL;
	int child = -1;
	TreeNode* node = Tree_GetNode(tree, int_random(0, treeSize - 1), &parent, &child);

	Function* funcOld = (Function*)node->value;
	
	DList* list = F[funcOld->res][funcOld->size];

	Function* funcNew = (Function*)DList_Get(list, int_random(0, list->size - 1));

	for (int i = 0; i < funcNew->size; i++)
	{
		if (funcOld->arg[i] != funcNew->arg[i]) return;
	}

	node->value = funcNew;
}

void TreeAI_Permutation(Tree* tree)
{
}
