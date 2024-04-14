#pragma once
#include <SDL.h>


typedef struct
{
	int damage, speed, alpha;
	bool friendly;
	SDL_Rect Klshn;
	SDL_Texture* T;
	bool izable;
}projectile;

void Gamemode(int& mode);