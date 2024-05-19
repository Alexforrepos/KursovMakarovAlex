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
	int HP=0, Money=0;
	int dir,dirleft=0,cstage; // для анимации
	weapon W[4]; // оружие
	SDL_Texture* T; // текстура
	SDL_Rect cr[24]; // все анимации
	SDL_FRect dr; 
	double Alpha; // уголповорота
	int currentWeapon; // отображает текущее оружие
	int ItemsInventory[4] = {0}; // все предметы 
};

extern player* Hero;

void HeroDv();

void HeroInit();
