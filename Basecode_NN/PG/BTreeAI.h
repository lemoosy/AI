#pragma once

#include "BTree.h"
#include "Function.h"
#include "../Utils/DList.h"
#include "../Utils/Utils.h"

#define MAX_DEPTH 3

BTree* BTreeAI_New(DList* T, DList* F1, DList* F2);

float  BTreeAI_Execute(BTree* tree);

void   BTreeAI_UpdateScore(BTree* tree, DList* T);
int    BTreeAI_CompareScore(BTree* t1, BTree* t2);

void   BTreeAI_Crossover(BTree* t1, BTree* t2);
void   BTreeAI_Mutation(BTree* tree, DList* T, DList* F1, DList* F2);
