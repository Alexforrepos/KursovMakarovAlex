#include  <iostream>
#include "texturesimport.h"
#include "SpleetProcessing.h"
#include "SDLProcessing.h"
#include "Hero.h"

double Maxfaze = 10;

player Hero;

Spleet—haracteristic* HeroAnimatic = (Spleet—haracteristic*)malloc(sizeof(Spleet—haracteristic) * 10);

void DHero()
{
	
}

Spleet—haracteristic HeroRunBack(double scale)
{
	Spleet—haracteristic spleet;
	spleet.texture = CreateUTexture("soul_knight_animation_cuted_run_back.png", ren);
	spleet.drect = RectOfTexture(spleet.texture, 400, 400); //pos 
	spleet.currenfaze = 0;
	spleet.maxfaze = 4;
	spleet.drect.h = 24 * scale * spleet.maxfaze * Maxfaze / spleet.maxfaze;
	spleet.drect.w = 20 * scale * spleet.maxfaze * Maxfaze / spleet.maxfaze;
	spleet.crect[0] = { 0 ,0 ,20,24 };
	spleet.crect[2] = { 20,0 ,20,24 };
	spleet.crect[1] = { 0 ,24,20,24 };
	spleet.crect[3] = { 20,24,20,24 };
	return spleet;
}

Spleet—haracteristic HeroRunStay(double scale)
{
	Spleet—haracteristic spleet;
	spleet.texture = CreateUTexture("soul_knight_animation_cuted_run_front_stay.png", ren);
	spleet.drect = RectOfTexture(spleet.texture, 500, 400);
	spleet.currenfaze = 0;
	spleet.maxfaze = 2;
	spleet.drect.h = 24 * scale * spleet.maxfaze * Maxfaze / spleet.maxfaze;
	spleet.drect.w = 20 * scale * spleet.maxfaze * Maxfaze / spleet.maxfaze;
	spleet.crect[0] = { 0,0,20,24 };
	spleet.crect[1] = { 20,0,20,24 };
	return spleet;
}

Spleet—haracteristic HeroFrontRun(double scale)
{
	Spleet—haracteristic spleet;
	spleet.texture = CreateUTexture("soul_knight_animation_cuted_run_front_right.png", ren);
	spleet.drect = RectOfTexture(spleet.texture, 600, 400);
	spleet.currenfaze = 0;
	spleet.maxfaze = 4;
	spleet.drect.h = (int)(24 * scale * spleet.maxfaze * Maxfaze / spleet.maxfaze);
	spleet.drect.w = (int)(20 * scale * spleet.maxfaze * Maxfaze / spleet.maxfaze);
	spleet.crect[0] = { 0,0,20,24 };
	spleet.crect[2] = { 20,0,20,24 };
	spleet.crect[1] = { 0,24,20,24 };
	spleet.crect[3] = { 20,24,20,24 };
	return spleet;
}

Spleet—haracteristic HeroFrontRunRight(double scale)
{
	Spleet—haracteristic spleet;
	spleet.texture = CreateUTexture("soul_knight_animation_cuted_run_right.png", ren);
	spleet.drect = RectOfTexture(spleet.texture, 700, 400);

	spleet.currenfaze = 0;
	spleet.maxfaze = 4;

	spleet.drect.h = 24 * scale * spleet.maxfaze * (Maxfaze / spleet.maxfaze);
	spleet.drect.w = 20 * scale * spleet.maxfaze * (Maxfaze / spleet.maxfaze);
	spleet.crect[0] = { 0,0,23,24 };
	spleet.crect[1] = { 23,0,23,24 };
	spleet.crect[2] = { 46,0,23,24 };
	spleet.crect[3] = { 69,0,23,24 };

	return spleet;
}

void HeroInit(int scale)
{
	HeroAnimatic[Nondirect] = HeroRunStay(scale);
	HeroAnimatic[Back] = HeroRunBack(scale);
	HeroAnimatic[Right] = HeroFrontRunRight(scale);
	HeroAnimatic[FrontRun] = HeroFrontRun(scale);
}