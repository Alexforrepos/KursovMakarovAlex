#pragma once
#include <SDL.h>

enum HeroDirection
{
	Down = 0,
	Up = 1,
	right = 2
};

struct Spleet—haracteristic
{
	SDL_Texture* texture;
	SDL_Rect drect;
	SDL_Rect crect[10];
	int currenfaze;
	int maxfaze;
};

void SpleetAnimatic(SDL_Renderer* ren, Spleet—haracteristic& spleet);

void HeroInit(SDL_Renderer* ren);