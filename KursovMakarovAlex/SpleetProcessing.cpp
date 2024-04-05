#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "SpleetProcessing.h"
#include "texturesimport.h"

SpleetÑharacteristic* HeroAnimatic = (SpleetÑharacteristic*)malloc(sizeof(SpleetÑharacteristic) * 10);

double Maxfaze = 10;

SpleetÑharacteristic HeroRunBack(SDL_Renderer* ren, double scale)
{
	SpleetÑharacteristic spleet;
	spleet.texture = CreateUTexture("soul_knight_animation_cuted_run_back.png", ren);
	spleet.drect = RectOfTexture(spleet.texture,400,400); //pos 
	spleet.currenfaze = 0;
	spleet.maxfaze = 4;
	spleet.drect.h = 24 * scale * spleet.maxfaze * Maxfaze / spleet.maxfaze;
	spleet.drect.w = 20 * scale * spleet.maxfaze * Maxfaze / spleet.maxfaze;
	spleet.crect[0] = { 0,0,20,24 };
	spleet.crect[2] = { 20,0,20,24 };
	spleet.crect[1] = { 0,24,20,24 };
	spleet.crect[3] = { 20,24,20,24 };
	return spleet;
}

SpleetÑharacteristic HeroRunStay(SDL_Renderer* ren, double scale)
{
	SpleetÑharacteristic spleet;
	spleet.texture = CreateUTexture("soul_knight_animation_cuted_run_front_stay.png", ren);
	spleet.drect = RectOfTexture(spleet.texture,500,400);
	spleet.currenfaze = 0;
	spleet.maxfaze = 2;
	spleet.drect.h = 24 * scale * spleet.maxfaze* Maxfaze / spleet.maxfaze;
	spleet.drect.w = 20 * scale * spleet.maxfaze * Maxfaze / spleet.maxfaze;
	spleet.crect[0] = { 0,0,20,24 };
	spleet.crect[1] = { 20,0,20,24 };
	return spleet;
}

SpleetÑharacteristic HeroFrontRun(SDL_Renderer* ren, double scale)
{
	SpleetÑharacteristic spleet;
	spleet.texture = CreateUTexture("soul_knight_animation_cuted_run_front_right.png", ren);
	spleet.drect = RectOfTexture(spleet.texture,600,400);
	spleet.currenfaze = 0;
	spleet.maxfaze = 4;
	spleet.drect.h =(int)(24 * scale * spleet.maxfaze * Maxfaze / spleet.maxfaze);
	spleet.drect.w = (int)(20 * scale * spleet.maxfaze * Maxfaze / spleet.maxfaze);
	spleet.crect[0] = { 0,0,20,24 };
	spleet.crect[2] = { 20,0,20,24 };
	spleet.crect[1] = { 0,24,20,24 };
	spleet.crect[3] = { 20,24,20,24 };
	return spleet;
}

SpleetÑharacteristic HeroFrontRunRight(SDL_Renderer* ren, double scale)
{
	SpleetÑharacteristic spleet;
	spleet.texture = CreateUTexture("soul_knight_animation_cuted_run_right.png", ren);
	spleet.drect = RectOfTexture(spleet.texture,700,400);

	spleet.currenfaze = 0;
	spleet.maxfaze = 4;

	spleet.drect.h = 24 * scale * spleet.maxfaze * (Maxfaze / spleet.maxfaze);
	spleet.drect.w = 20 * scale * spleet.maxfaze * (Maxfaze / spleet.maxfaze);
	spleet.crect[0] = { 0,0,23,24 };
	spleet.crect[1] = { 23,0,23,24 };
	spleet.crect[2] = { 46,0,23,24 };
	spleet.crect[3] = { 69,0,23,24 };

	return spleet;
}

void HeroInit(SDL_Renderer* ren,double scale)
{
	HeroAnimatic[Nondirect] = HeroRunStay(ren, scale);
	HeroAnimatic[Back] = HeroRunBack(ren, scale);
	HeroAnimatic[FrontRun] = HeroFrontRun(ren, scale);
	HeroAnimatic[Right] = HeroFrontRunRight(ren, scale);
}

void SpleetAnimatic(SDL_Renderer* ren, SpleetÑharacteristic& spleet)
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

void FreeAllHeroTextures(SpleetÑharacteristic* Herot)
{
	for (int i = 0; Herot->texture != NULL; i++)
	{
		SDL_DestroyTexture(Herot->texture);
	}
	free(Herot);
}