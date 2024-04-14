#pragma once


typedef	enum BordersOfAnimatic 
{
	BackRun,FrontRun,RightNondir,LeftNondir,Rightrun,LeftRun,
};


typedef struct
{
	int damage;
	int cd;
	SDL_Texture* T;
	double Alpha;
	bool isanable;
}weapon;

struct player
{
	int HP, Money;
	int dir,dirleft=0,cstage;
	weapon shotgun, lazgan, machine;
	SDL_Texture* T;
	SDL_Rect cr[24],dr;
	int currentWeapon;
};

extern player Hero;

void HeroDv();

void HeroInit();
