#include <iostream>
#include "texturesimport.h"
#include "SDLProcessing.h"
#include "SpleetProcessing.h"
#include "Menu.h"
#include "Mouse.h"

#pragma region WINDOW_CHARACTERISTIC

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
extern int WIDTH;
extern int HEIGHT;

#pragma endregion

extern TextureСharacteristic* Textures;

int main(int argc, char* argv[])
{
	system("chcp 1251 > NULL");
	Init();
#pragma region glavperemen
	SDL_Event ev;
	bool isrunning = true;
	Mouse mos;
#pragma endregion
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	MenuTextureInit(ren);
	HeroInit(ren, 0.4);
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
			case SDL_MOUSEBUTTONDOWN:
				switch (ev.button.button)
				{
				case SDL_BUTTON_LEFT:
					mos.isLKM = true;
				default:
					break;
				}
			default:
				break;
			}
		}
#pragma endregion

		if (!isrunning)
		{
			break;
		}
			SDL_RenderClear(ren);

			MenuDrow(ren,mos,isrunning);
			SpleetAnimatic(ren, HeroAnimatic[Nondirect],1);
			if (!isrunning)
			{
				break;
			}
			SDL_RenderPresent(ren);
			mos.isLKM = false;
	}
	//FreeTextures();
	//FreeAllHeroTextures(HeroAnimatic);
	Deinit(0);
	return 1;
}
