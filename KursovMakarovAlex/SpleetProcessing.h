#pragma once
#include <SDL.h>

enum HeroDirection
{
	Nondirect = 0,
	Back = 1,
	Right = 2,
	FrontRun = 3
};

struct Spleet—haracteristic
{
	SDL_Texture* texture;
	SDL_Rect drect;
	SDL_Rect crect[10];
	int currenfaze;
	int maxfaze;
};

extern Spleet—haracteristic* HeroAnimatic;

void FreeAllHeroTextures(Spleet—haracteristic* Herot);

void SpleetAnimatic(SDL_Renderer* ren, Spleet—haracteristic& spleet);

void HeroInit(SDL_Renderer* ren, double scale);