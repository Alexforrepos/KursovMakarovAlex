#include <iostream>
#include "texturesimport.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Menu.h"


void MenuDrow(SDL_Renderer* ren)
{

	SDL_RenderCopy(ren, BackgrTextures[BackGroundMenu].texture, NULL, NULL);
	for (int i = TextMenuStart; i < TextMenuEnd; i += 2)
		SDL_RenderCopy(ren, TextTextures[i].texture, NULL, &TextTextures[i].drect);
}