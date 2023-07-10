#pragma once

#include "../../Settings.h"

void* Bool_Create(bool b);
void  Bool_Print(void* _b);
void* Bool_Not(void* _b);
void* Bool_And(void* _b0, void* _b1);
void* Bool_Or(void* _b0, void* _b1);
