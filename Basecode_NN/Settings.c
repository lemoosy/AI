#include "Settings.h"

void Settings_Init(void)
{
	srand(time(NULL));

	int res = SDL_Init(SDL_INIT_VIDEO);

	if (res != 0)
	{
		printf("ERROR - Settings_Init() \n");
		printf("ERROR - SDL_Init() \n");
		abort();
	}
}

void Settings_Quit(void)
{
	SDL_Quit();
}
