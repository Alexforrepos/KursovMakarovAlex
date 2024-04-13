#pragma once

enum HeroDirection
{
	Nondirect = 0,
	Back = 1,
	Right = 2,
	FrontRun = 3
};


struct player
{
	int x, y, dir;
	bool weap1, weap2, weap3, weap4;
};

extern player Hero;

void HeroInit();

void FreeAllHeroTextures(Spleet—haracteristic* Herot);