#pragma once
#include <SDL.h>

struct Spleet—haracteristic
{
	SDL_Texture* texture;
	SDL_Rect drect;
	SDL_Rect crect[10];
	int currenfaze;
	int maxfaze;
};

extern Spleet—haracteristic* HeroAnimatic; 

void SpleetAnimatic(SDL_Renderer* ren, Spleet—haracteristic& spleet,int FPS);