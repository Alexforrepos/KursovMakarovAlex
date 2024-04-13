#include <iostream>
#include "texturesimport.h"
#include "SDLProcessing.h"
#include "SpleetProcessing.h"
#include "Menu.h"
#include "Mouse.h"
#include "gamemode.h"

enum mode
{
	menumode = 0,
	gamemode,
};

int main(int argc, char* argv[])
{
	system("chcp 1251 > NULL");
	Init();
#pragma region glavperemen
	int mode = 0;
	SDL_Event ev;
	bool isrunning = true;
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
#pragma endregion
	MenuTextureInit();
	while (isrunning)
	{
#pragma region event
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				isrunning = false;
				break;
			case SDL_WINDOWEVENT:
				if (ev.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					WIDTH = ev.window.data1;
					HEIGHT = ev.window.data2;
				}
			default:
				break;
			}
		}
#pragma endregion

		SDL_RenderClear(ren);
		if (!isrunning)
		{
			break;
		}
		switch (mode)
		{
		case menumode:
			MenuDrow(isrunning, mode);
			break;
		case gamemode:
			//Gamemode(mode);
		default:
			break;
		}
		SDL_RenderPresent(ren);
	}
	free(HeroAnimatic);
	FreeTextures();
	Deinit(0);
	return 1;
}
