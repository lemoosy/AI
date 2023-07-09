#pragma once

#include "../Settings.h"
#include "Input.h"

#define WINDOW_W 800
#define WINDOW_H 800

typedef SDL_Color ColorRGBA;

ColorRGBA ColorRGBA_Create(int r, int g, int b, int a);

typedef struct sWindow
{
	Input input;
	SDL_Window* __window;
	SDL_Renderer* __renderer;
}Window;

Window* Window_Create(char* title);
void    Window_Clear(Window* window);
void    Window_DrawRectangle(Window* window, float x, float y, float w, float h, ColorRGBA color);
void    Window_DrawLine(Window* window, float x0, float y0, float x1, float y1, ColorRGBA color);
void    Window_Update(Window* window);
void    Window_Refresh(Window* window);
void    Window_Destroy(Window* window);
