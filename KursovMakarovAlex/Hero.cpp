#include  <iostream>
#include "texturesimport.h"
#include "SpleetProcessing.h"
#include "SDLProcessing.h"
#include "Hero.h"

double Maxfaze = 10;

player Hero;

void HeroDv()
{
	switch (Hero.dir)
	{
	case BackRun:
		SpleetAnimaticHero(Hero.T, Hero.cr, Hero.dr, 4, 2, BackRun);
		break;
	case FrontRun:
		SpleetAnimaticHero(Hero.T, Hero.cr, Hero.dr, 4, 2, FrontRun);
		break;
	case RightNondir:
		SpleetAnimaticHero(Hero.T, Hero.cr, Hero.dr, 4, 2, RightNondir);
		break;
	case LeftNondir:
		SpleetAnimaticHero(Hero.T, Hero.cr, Hero.dr, 4, 2, LeftNondir);
		break;
	case Rightrun:
		SpleetAnimaticHero(Hero.T, Hero.cr, Hero.dr, 4, 2, Rightrun);
		break;
	case LeftRun:
		SpleetAnimaticHero(Hero.T, Hero.cr, Hero.dr, 4, 2, LeftRun);
		break;
	default:
		break;
	}
}

void HeroInit()
{
	Hero.T = CreateUTexture("soul_knight_animation_final.png");
	SDL_QueryTexture(Hero.T, NULL,NULL, &Hero.dr.w,&Hero.dr.h);
	Hero.dr = { 100,100,Hero.dr.w/2,Hero.dr.h/2 };
	Hero.cr[16] = { 0 ,0 ,22,23 };
	Hero.cr[17] = { 23,0 ,23,23 };
	Hero.cr[18] = { 46,0 ,23,24 };
	Hero.cr[19] = { 69,0 ,23,24 };
	Hero.cr[20] = { 0 ,25,23,24 };
	Hero.cr[21] = { 23,25,23,24 };
	Hero.cr[22] = { 46,25,23,24 };
	Hero.cr[23] = { 69,25,23,24 };
	Hero.cr[8] = { 0 ,49,19,24 };
	Hero.cr[9] = { 19,49,19,24 };
	Hero.cr[10] = { 0 ,49,19,24 };
	Hero.cr[11] = { 19,49,20,24 };
	Hero.cr[12] = { 64,49,20,24 };
	Hero.cr[13] = { 44,49,19,24 };
	Hero.cr[14] = { 64,49,20,24 };
	Hero.cr[15] = { 44,49,19,24 };
	Hero.cr[4] = { 0 ,81,19,24 };
	Hero.cr[5] = { 19,81,19,24 };
	Hero.cr[6] = { 0,105,19,24 };
	Hero.cr[7] = { 19,105,19,24 };
	Hero.cr[0] = { 0 ,130,19,24 }; 
	Hero.cr[1] = { 19,130,19,24 };
	Hero.cr[2] = { 0 ,156,19,24 };
	Hero.cr[3] = { 19,156,19,24 };
}