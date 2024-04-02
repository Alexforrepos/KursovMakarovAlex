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

int main(int argc, char* argv[])
{
	Init();
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	while (1)
	{
	
	}

	Deinit(1);
	return 0;
}
