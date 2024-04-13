#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "texturesimport.h"
#include "Menu.h"
#include "Mouse.h"
#include "SDLProcessing.h"


void NewGame()
{
	SDL_RenderCopy(ren, BackgrTextures[SaveMenu].texture, NULL, NULL);
}

void MenuDrow(bool& isrun, int &mod)
{
	SDL_Point mp;
	static int mods = StandartMode;
	Uint8 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	switch (mods)
	{
	case StandartMode:
		SDL_RenderCopy(ren, BackgrTextures[BackGroundMenu].texture, NULL, NULL);
		for (int i = TextMenuStart; i <= TextMenuEnd; i += 2)
		{
			if (isin(mp, TextTextures[i].drect))
			{
				SDL_RenderCopy(ren, TextTextures[i + 1].texture, NULL, &TextTextures[i].drect);
				if (mstate & SDL_BUTTON(SDL_BUTTON_LEFT))
					switch (i)
					{
					case 0:
						mods = NewGameMode;
						break;
					case 2:
						mods = InfoMode;
						break;
					case 4:
						isrun = false;
						break;
					default:
						break;
					}
			}
			else
			{
				SDL_RenderCopy(ren, TextTextures[i].texture, NULL, &TextTextures[i].drect);
			}
		}
		break;
	case InfoMode:
		SDL_RenderCopy(ren, BackgrTextures[InfoMenu].texture, NULL, NULL);
		if (kstate[SDL_SCANCODE_ESCAPE])
			mods = StandartMode;
		break;
	case NewGameMode:
		if (kstate[SDL_SCANCODE_ESCAPE])
			mods = StandartMode;
		if (kstate[SDL_SCANCODE_TAB])
			mod = 0;
		break;
	default:
		break;
	}

}