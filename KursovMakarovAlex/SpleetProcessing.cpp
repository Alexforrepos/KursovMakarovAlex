#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "SpleetProcessing.h"
#include "texturesimport.h"

SpleetÑharacteristic HeroAnimatic[3];

SpleetÑharacteristic HeroRunBack(SDL_Renderer* ren)
{
	SpleetÑharacteristic spleet;
	spleet.texture = CreateUTexture("soul_knight_animation_cuted_run_back.png",ren);
	spleet.drect = RectOfTexture(spleet.texture);
	spleet.drect.x = 400;
	spleet.drect.y = 400;
	spleet.currenfaze = 0;
	spleet.maxfaze = 4;
	spleet.crect[0] = { 0,30,19,24 };
	spleet.crect[1] = { 19,30,19,24 };
	spleet.crect[2] = { 0,0,19,24 };
	spleet.crect[3] = { 19,0,19,24 };
	return spleet;
}

void HeroInit(SDL_Renderer * ren)
{
	HeroAnimatic[Down] = HeroRunBack(ren);
}

void SpleetAnimatic(SDL_Renderer* ren,SpleetÑharacteristic &spleet)
{
	static int  dt, lasttime;
	int currentime = SDL_GetTicks();
	dt += currentime - lasttime;
	lasttime = currentime;
	SDL_RenderCopy(ren, spleet.texture, &spleet.crect[spleet.currenfaze], &spleet.drect);
	if (dt >= 1000 * 10 / 24);
	{
		spleet.currenfaze++;
		SDL_Delay(50);
		dt %= 1000 * 4 / 24;
	}
	spleet.currenfaze %= spleet.maxfaze;
}