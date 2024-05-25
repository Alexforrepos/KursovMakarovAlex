#include  <iostream>
#include "texturesimport.h"
#include "SpleetProcessing.h"
#include "SDLProcessing.h"
#include "Hero.h"

double Maxfaze = 10;

player* Hero = (player*)malloc(sizeof(player));


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

	Hero->TEXTURES = &ALL_TEXTURES->ALL_LOCAL_TEXTURES[Hero_Spleet_Animation];
	Hero->HP = -1;
	Hero->Money = -1;
	Hero->currentWeapon = 0;
	Hero->phaseofanimation = 1;
	Hero->Time = { 0,0,0,1000 };	
	Hero->dr = { 100,100,Hero->dr.h,Hero->dr.h };
	HeroWeaponInit();
	HeroIteminit();

	for (int i = 0; i < 4; i++)
	{
		Hero->ItemsInventory[i] = 0;
		Hero->W[i].enabled = 1;
	}
}