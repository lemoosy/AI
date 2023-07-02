#pragma once

#include "../Settings.h"

void* Bool_New(bool b);
void* Bool_Not(void* _b);

void* Float_New(float x);
void* Float_Srt(void* _x);
void* Float_Add(void* _x0, void* _x1);
void* Float_Sub(void* _x0, void* _x1);
void* Float_Mul(void* _x0, void* _x1);
void* Float_Div(void* _x0, void* _x1);
void* Float_Sup(void* _x0, void* _x1);
void* Float_Inf(void* _x0, void* _x1);
