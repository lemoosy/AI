#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdarg.h>
#include <SDL.h>

typedef float data;

//#define GAME_CONNECT4
#define GAME_SNAKE

void Settings_Init(void);
void Settings_Quit(void);
