#include "Window.h"

ColorRGBA ColorRGBA_Create(int r, int g, int b, int a)
{
	assert((0 <= r) && (r <= 255));
	assert((0 <= g) && (g <= 255));
	assert((0 <= b) && (b <= 255));
	assert((0 <= a) && (a <= 255));

	return ((ColorRGBA) { .r = r, .g = g, .b = b, .a = a });
}

Window* Window_Create(char* title)
{
	Window* window = window = (Window*)calloc(1, sizeof(Window));

	window->__window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_W,
		WINDOW_H,
		SDL_WINDOW_SHOWN
	);

	if (window->__window == NULL)
	{
		printf("ERROR - Window_Create() \n");
		printf("ERROR - SDL_CreateWindow() \n");
		abort();
	}

	window->__renderer = SDL_CreateRenderer(
		window->__window,
		-1,
		SDL_RENDERER_SOFTWARE
	);

	if (window->__renderer == NULL)
	{
		printf("ERROR - Window_Create() \n");
		printf("ERROR - SDL_CreateRenderer() \n");
		abort();
	}

	return window;
}

void Window_Clear(Window* window)
{
	SDL_SetRenderDrawColor(window->__renderer, 0, 0, 0, 255);
	SDL_RenderClear(window->__renderer);
}

void Window_DrawRectangle(Window* window, float x, float y, float w, float h, ColorRGBA color)
{
	SDL_FRect rect = {
		.x = x,
		.y = y,
		.w = w,
		.h = h,
	};

	SDL_SetRenderDrawColor(window->__renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRectF(window->__renderer, &rect);
}

void Window_DrawLine(Window* window, float x0, float y0, float x1, float y1, ColorRGBA color)
{
	SDL_SetRenderDrawColor(window->__renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLineF(window->__renderer, x0, y0, x1, y1);
}

void Window_Update(Window* window)
{
	Input_Update(&window->input);
}

void Window_Refresh(Window* window)
{
	SDL_RenderPresent(window->__renderer);
}

void Window_Destroy(Window* window)
{
	if (!window) return;

	SDL_DestroyRenderer(window->__renderer);
	SDL_DestroyWindow(window->__window);
	free(window);
}
