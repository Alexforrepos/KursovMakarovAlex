#include <iostream>
#include "texturesimport.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Menu.h"


void MenuDrow(SDL_Renderer* ren,int x,int y)
{
	SDL_Color WHITE = { 0,0,255,255 };
	SDL_Texture* backgr = CreateUTexture("proba.png", ren);
	SDL_Texture* TextNewGame = CreateTextTexture("New Game", "Zodchiy-Regular.ttf", WHITE, 32, ren);
	SDL_Rect RectTextNewGame = RectOfTexture(TextNewGame);
	RectTextNewGame.x=x;
	RectTextNewGame.y=y;
	SDL_RenderCopy(ren, backgr, NULL, NULL);
	SDL_RenderCopy(ren, TextNewGame, NULL, &RectTextNewGame);
}