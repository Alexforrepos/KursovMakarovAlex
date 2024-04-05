#include <iostream>
#include "texturesimport.h"
#include "SDLProcessing.h"
#include "SpleetProcessing.h"
#include "Menu.h"

#pragma region WINDOW_CHARACTERISTIC

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
int WIDTH = 1920;
int HEIGHT = 1080;

#pragma endregion

extern TextureСharacteristic* Textures;

int main(int argc, char* argv[])
{
	system("chcp 1251 > NULL");
	Init();
#pragma region glavperemen
	SDL_Event ev;
	bool isrunning = true;
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	MenuTextureInit(ren);
#pragma endregion
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
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					isrunning = false;
					break;
				default:
					break;
				}
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

		MenuDrow(ren);
		SDL_RenderPresent(ren);
	}
	FreeTextures();
	FreeAllHeroTextures(HeroAnimatic);
	Deinit(1);
	return 0;
}
