#pragma once

#include "../Settings.h"

typedef struct sInput
{
	bool left;
	bool right;
	bool up;
	bool down;

	bool f1;
	bool f2;
	bool f3;
	bool f4;
	bool f5;

	bool quit;
}Input;

void Input_Update(Input* input);
