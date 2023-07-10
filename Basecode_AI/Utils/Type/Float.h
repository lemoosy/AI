#pragma once

#include "../../Settings.h"
#include "Bool.h"

void* Float_Create(float x);
void  Float_Print(void* _x);
int   Float_Compare(void* _x0, void* _x1);
void* Float_Srt(void* _x);
void* Float_Add(void* _x0, void* _x1);
void* Float_Sub(void* _x0, void* _x1);
void* Float_Mul(void* _x0, void* _x1);
void* Float_Div(void* _x0, void* _x1);
void* Float_Equal(void* _x0, void* _x1);
void* Float_Sup(void* _x0, void* _x1);
void* Float_Inf(void* _x0, void* _x1);
void* Float_SupEqual(void* _x0, void* _x1);
void* Float_InfEqual(void* _x0, void* _x1);

float Float_Random(float x0, float x1);
