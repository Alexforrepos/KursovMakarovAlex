#pragma once
#include "All_TextureInit.h"
#include <SDL.h>


enum currentweapon
{
	machine, shotgun, lazgan, lazgun

};

struct weapon
{
	bool enabled;
	int damage, bulletspeed = 10;
	int cd, reloadtime;
	SDL_Texture* T;
	SDL_Rect cr;
	SDL_FRect dr;
	
	double Alpha;
	bool isanable;
};


struct player
{
	int HP = 0, Money = 0;

	LOCAL_MASS_TEXTURE_DESCRIPTOR* TEXTURES[2];
	TimeStruct Time;
	int phaseofanimation = 0;
	SDL_FRect dr;
	bool isfliped;

	weapon W[4];
	double Alpha; // уголповорота
	int currentWeapon; // отображает текущее оружие


	int ItemsInventory[4] = { 0 }; // все предметы 
};


extern player* Hero;

void HeroInit();
