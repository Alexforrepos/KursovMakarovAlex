#include  <iostream>
#include "texturesimport.h"
#include "SpleetProcessing.h"
#include "SDLProcessing.h"
#include "Hero.h"
#include "All_TextureInit.h"

double Maxfaze = 10;

player* Hero = (player*)malloc(sizeof(player));

void HeroWeaponInit()
{
	Hero->W[0].bulletspeed = 2;
	Hero->W[0].damage = 50;
	Hero->W[0].isanable = 1;
	Hero->W[0].reloadtime = 500;
	Hero->W[0].T = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Guns_Textures].PrivateTexture[0];
	Hero->W[0].cr = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Guns_Textures].SR[0];
	Hero->W[0].dr = { (float)Hero->W[0].cr.x,(float)Hero->W[0].cr.y,(float)Hero->W[0].cr.w,(float)Hero->W[0].cr.h };
	Hero->W[1].bulletspeed = 10;
	Hero->W[1].damage = 100;
	Hero->W[1].isanable = 1;
	Hero->W[1].reloadtime = 1500;
	Hero->W[1].T = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Guns_Textures].PrivateTexture[3];
	Hero->W[1].cr = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Guns_Textures].SR[3];
	Hero->W[1].dr = { (float)Hero->W[1].cr.x,(float)Hero->W[1].cr.y,(float)Hero->W[1].cr.w,(float)Hero->W[1].cr.h };
	Hero->W[2].bulletspeed = 5;
	Hero->W[2].damage = 120;
	Hero->W[2].isanable = 1;
	Hero->W[2].reloadtime = 100;
	Hero->W[2].T = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Guns_Textures].PrivateTexture[2];
	Hero->W[2].cr = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Guns_Textures].SR[2];
	Hero->W[2].dr = { (float)Hero->W[2].cr.x,(float)Hero->W[2].cr.y,(float)Hero->W[2].cr.w,(float)Hero->W[2].cr.h };
	Hero->W[3].bulletspeed = 20;
	Hero->W[3].damage = 200;
	Hero->W[3].isanable = 1;
	Hero->W[3].reloadtime = 0;
	Hero->W[3].T = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Guns_Textures].PrivateTexture[1];
	Hero->W[3].cr = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Guns_Textures].SR[1];
	Hero->W[3].dr = { (float)Hero->W[3].cr.x,(float)Hero->W[3].cr.y,(float)Hero->W[3].cr.w,(float)Hero->W[3].cr.h };
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

	Hero->TEXTURES[0] = &ALL_TEXTURES->ALL_LOCAL_TEXTURES[Hero_Spleet_Animation];
	Hero->TEXTURES[1] = &ALL_TEXTURES->ALL_LOCAL_TEXTURES[Hero_Spleet_Animation_R];
	Hero->HP = 1000;
	Hero->Money = -1;
	Hero->currentWeapon = 0;
	Hero->phaseofanimation = 1;
	Hero->Time = { 0,0,0,1000 };	
	Hero->dr = { 100,100,Hero->dr.h,Hero->dr.h };
	Hero->enemK = 0;
	HeroWeaponInit();
	HeroIteminit();

	for (int i = 0; i < 4; i++)
	{
		Hero->ItemsInventory[i] = 0;
		Hero->W[i].enabled = 1;
	}
}