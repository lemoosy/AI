#pragma once

#include "Tree.h"
#include "Function.h"
#include "../Utils/DList.h"
#include "../Utils/Data.h"
#include "../Utils/Utils.h"
#include "Ant.h"

#define MAX_DEPTH 2

float in0;
float in1;
bool in2;

Tree* TreeAI_New(DList*** F, TypeID res);

// res = TYPE_NONE
void* _if(TreeNode* node);
void* _progn(TreeNode* node);

// res = TYPE_REAL
void* _in0(TreeNode* node);
void* _in1(TreeNode* node);
void* _srt(TreeNode* node);
void* _add(TreeNode* node);
void* _sub(TreeNode* node);
void* _mul(TreeNode* node);
void* _div(TreeNode* node);

// res = TYPE_BOOL
void* _in2(TreeNode* node);
void* _not(TreeNode* node);
void* _sup(TreeNode* node);
void* _inf(TreeNode* node);
void* _and(TreeNode* node);
void* _or(TreeNode* node);

void* TreeAI_ExecuteRec(TreeNode* node);
void* TreeAI_Execute(Tree* tree);

void  TreeAI_UpdateScore(Tree* tree, bool display);
int   TreeAI_CompareScore(Tree* t1, Tree* t2);

void  TreeAI_Crossover(Tree* t1, Tree* t2);
void  TreeAI_Mutation(Tree* tree, DList*** F);
void  TreeAI_Permutation(Tree* tree);
