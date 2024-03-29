#include <iostream>
#include "texturesimport.h"
#include "SDLProcessing.h"
#include "SpleetProcessing.h"

#pragma region WINDOW_CHARACTERISTIC

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
int WIDTH = 1200;
int HEIGHT = 1000;

#pragma endregion

extern TextureСharacteristic* Textures;
extern SpleetСharacteristic HeroAnimatic[3];

int main(int argc, char* argv[])
{
	Init();
	HeroInit(ren);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	while (1)
	{
		SDL_RenderClear(ren);
		SpleetAnimatic(ren, HeroAnimatic[0]);

		SDL_RenderPresent(ren);
		SDL_Delay(1000 / 25);
	}
	Deinit(1);
	return 0;
}
