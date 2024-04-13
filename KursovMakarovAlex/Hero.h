#pragma once


typedef	enum BordersOfAnimatic 
{
	BackRun,FrontRun,RightNondir,LeftNondir,Rightrun,LeftRun,
};


struct player
{
	int HP, Money;
	int dir,dirleft=0,cstage;
	bool weap1, weap2, weap3, weap4;
	SDL_Texture* T;
	SDL_Rect cr[24],dr;
};

extern player Hero;

void HeroDv();

void HeroInit();
