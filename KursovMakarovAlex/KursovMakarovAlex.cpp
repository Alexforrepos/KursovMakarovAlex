#include <iostream>
#include "texturesimport.h"
#include "TextProcessing.h"
#include "SDLProcessing.h"
#include "SpleetProcessing.h"
#include "Menu.h"
#include "gamemode.h"
#include "Hero.h"
#include "enemy.h"
#include "FileM.h"
#include "Items.h"
#include "All_TextureInit.h"
#include "Effects.h"

enum mode
{
	menumode = 0,
	gamemode,
};

int main(int argc, char* argv[])
{
	system("chcp 1251 > 0");
	srand(time(NULL));
	Init();
	SDL_Event ev;
#pragma region glavperemen
	int mode = 0;
	bool isrunning = true;
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
#pragma endregion
	InitALLTEXTURES();
	LoadFonts();
	MenuInit();
	HeroInit();
	IdeqInit();
	FileEnemyQGet(mode);
	EffQuue = CreateEffectQueue();
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
				break;
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
			DrowMenu(isrunning, mode);
			break;
		case gamemode:
			Gamemode(mode);
			break;
		}
		SDL_RenderPresent(ren);
	}
	FileHeroStatsSave("TextInformation/Save1.txt");
	FileHeroStatsSave("TextInformation/Save2.txt");
	FileHeroStatsSave("TextInformation/Save3.txt");
	DeinitIDeq();
	CloseFonts();
	Deinit(0);
	return 1;
}