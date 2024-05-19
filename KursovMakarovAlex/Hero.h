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
	int dir,dirleft=0,cstage; // ��� ��������
	weapon W[4]; // ������
	SDL_Texture* T; // ��������
	SDL_Rect cr[24]; // ��� ��������
	SDL_FRect dr; 
	double Alpha; // ������������
	int currentWeapon; // ���������� ������� ������
	int ItemsInventory[4] = {0}; // ��� �������� 
};

extern player* Hero;

void HeroDv();

void HeroInit();
