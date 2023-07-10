#pragma once

#include "../../Settings.h"
#include "Bool.h"
#include "Void.h"

void* Int_Create(int n);
void  Int_Print(void* _n);
int   Int_Compare(void* _n0, void* _n1);
void* Int_Add(void* _n0, void* _n1);
void* Int_Sub(void* _n0, void* _n1);
void* Int_Mul(void* _n0, void* _n1);
void* Int_Div(void* _n0, void* _n1);
void* Int_Equal(void* _n0, void* _n1);
void* Int_Sup(void* _n0, void* _n1);
void* Int_Inf(void* _n0, void* _n1);
void* Int_SupEqual(void* _n0, void* _n1);
void* Int_InfEqual(void* _n0, void* _n1);

int   Int_Random(int n0, int n1);
int*  Int_Tab(int size);
void  Int_Swap(int* n0, int* n1);
int*  Int_TabRandomNoRep(int size);
