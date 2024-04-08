#include <iostream>
#include "texturesimport.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Menu.h"
#include "Mouse.h"

enum mods
{
	standart = 0,
	Info = 1,
	Load = 2,
	NewGame = 3
};

void MenuDrow(SDL_Renderer* ren, Mouse mos,bool &isrun)
{
	SDL_Point mp;
	static int mods = standart;
	Uint8 state = SDL_GetMouseState(&mp.x, &mp.y);
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	switch (mods)
	{
	case standart:
		SDL_RenderCopy(ren, BackgrTextures[BackGroundMenu].texture, NULL, NULL);
		for (int i = TextMenuStart; i <= TextMenuEnd; i += 2)
	{
		if (isin(mp, TextTextures[i].drect))
		{
			SDL_RenderCopy(ren, TextTextures[i + 1].texture, NULL, &TextTextures[i].drect);
			if (mos.isLKM)
				switch (i)
				{
				case 0:
					isrun = false;
					break;
				case 2:
					isrun = false;
					break;
				case 4:
					mods = 1;
					break;
				case 6:
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
	case Info:
		SDL_RenderCopy(ren, BackgrTextures[InfoMenu].texture, NULL, NULL);
			if (kstate[SDL_SCANCODE_Q])
				mods = standart;
		break;
	default:
		break;
	}

}