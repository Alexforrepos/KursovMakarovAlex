#include  <iostream>
#include "texturesimport.h"
#include "SpleetProcessing.h"
#include "SDLProcessing.h"
#include "Hero.h"

double Maxfaze = 10;

player* Hero = (player*)malloc(sizeof(player));

void HeroDv()
{
	switch (Hero->dir)
	{
	case BackRun:
		SpleetAnimaticHero(Hero->T, Hero->cr, Hero->dr, 4, 2, BackRun);
		break;
	case FrontRun:
		SpleetAnimaticHero(Hero->T, Hero->cr, Hero->dr, 4, 2, FrontRun);
		break;
	case RightNondir:
		SpleetAnimaticHero(Hero->T, Hero->cr, Hero->dr, 4, 2, RightNondir);
		break;
	case LeftNondir:
		SpleetAnimaticHero(Hero->T, Hero->cr, Hero->dr, 4, 2, LeftNondir);
		break;
	case Rightrun:
		SpleetAnimaticHero(Hero->T, Hero->cr, Hero->dr, 4, 2, Rightrun);
		break;
	case LeftRun:
		SpleetAnimaticHero(Hero->T, Hero->cr, Hero->dr, 4, 2, LeftRun);
		break;
	default:
		break;
	}
}

void HeroWeaponInit()
{
	Hero->W[0].bulletspeed = 2;
	Hero->W[0].damage = 50;
	Hero->W[0].isanable = 1;
	Hero->W[0].reloadtime = 500;
	Hero->W[1].bulletspeed = 10;
	Hero->W[1].damage = 100;
	Hero->W[1].isanable = 1;
	Hero->W[1].reloadtime = 1000;
	Hero->W[2].bulletspeed = 5;
	Hero->W[2].damage = 120;
	Hero->W[2].isanable = 1;
	Hero->W[2].reloadtime = 1500;
	Hero->W[3].bulletspeed = 20;
	Hero->W[3].damage = 200;
	Hero->W[3].isanable = 1;
	Hero->W[3].reloadtime = 2000;
}

void HeroIteminit()
{
	for (int i = 0; i < 4; i++)
	{
		Hero->ItemsInventory[i] = 0;
	}
}

void HeroInit()
{
	Hero->HP = 100;
	Hero->Money = 100;
	Hero->currentWeapon = 0;
	Hero->T = CreateUTexture("textures/soul_knight_animation_final.png");
	int textureWidth, textureHeight;
	SDL_QueryTexture(Hero->T, NULL, NULL, &textureWidth, &textureHeight);
	Hero->dr.w = textureWidth;
	Hero->dr.h = textureHeight;
	HeroWeaponInit();
	HeroIteminit();
	Hero->dr = { 100,100,Hero->dr.w / 2,Hero->dr.h / 2 };
	Hero->cr[16] = { 0 ,0 ,23,23 };
	Hero->cr[17] = { 23,0 ,23,23 };
	Hero->cr[18] = { 46,0 ,23,24 };
	Hero->cr[19] = { 69,0 ,23,24 };
	Hero->cr[20] = { 0 ,25,23,24 };
	Hero->cr[21] = { 23,25,23,24 };
	Hero->cr[22] = { 46,25,23,24 };
	Hero->cr[23] = { 69,25,23,24 };
	Hero->cr[8] =  { 0 ,49,19,24 };
	Hero->cr[9] =  { 19,49,19,24 };
	Hero->cr[10] = { 0 ,49,19,24 };
	Hero->cr[11] = { 19,49,20,24 };
	Hero->cr[12] = { 64,49,20,24 };
	Hero->cr[13] = { 44,49,19,24 };
	Hero->cr[14] = { 64,49,20,24 };
	Hero->cr[15] = { 44,49,19,24 };
	Hero->cr[4] =  { 0 ,81,19,24 };
	Hero->cr[5] =  { 19,81,19,24 };
	Hero->cr[6] =  { 0,105,19,24 };
	Hero->cr[7] =  { 19,105,19,24};
	Hero->cr[0] =  { 0 ,130,19,24};
	Hero->cr[1] =  { 19,130,19,24};
	Hero->cr[2] =  { 0 ,156,19,24};
	Hero->cr[3] =  { 19,156,19,24};
	for (int i = 0; i < 4; i++)
	{
		Hero->ItemsInventory[i] = 200;
		Hero->W[i].enabled = 0;
	}
}