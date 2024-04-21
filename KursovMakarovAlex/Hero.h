#pragma once


enum BordersOfAnimatic
{
	BackRun,FrontRun,RightNondir,LeftNondir,Rightrun,LeftRun,
};

typedef enum
{
	machine, shotgun, lazgan, lazgun
}currentweapon;

struct weapon
{

	int damage,bulletspeed = 10;
	int cd,reloadtime;
	SDL_Texture* T;
	double Alpha;
	bool isanable;
};

struct player
{
	int HP, Money;
	int dir,dirleft=0,cstage;
	weapon W[4];
	SDL_Texture* T;
	SDL_Rect cr[24];
	SDL_FRect dr;
	int currentWeapon;
};

extern player* Hero;

void HeroDv();

void HeroInit();
