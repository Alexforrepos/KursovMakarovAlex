#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "texturesimport.h"
#include "SpleetProcessing.h"
#include "SDLProcessing.h"
#include "Mouse.h"
#include "gamemode.h"
#include "Hero.h"

enum dirrectionsofhero
{
	LeftHero, RightHero, DownHero, UpHero, StayHero
};

projectile bullets[100];

void HeroMove()
{
	int V = 1;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	if (kstate[SDL_SCANCODE_D] && !(kstate[SDL_SCANCODE_A]) && isin({ Hero.dr.x + V,Hero.dr.y }, { 0,0,WIDTH,HEIGHT - 100 }))
	{
		Hero.dirleft = 0;
		Hero.dir = Rightrun;
		Hero.dr.x += V;
	}
	if (kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]) && isin({ Hero.dr.x - V,Hero.dr.y }, { 0,0,WIDTH,HEIGHT - 100 }))
	{
		Hero.dirleft = 1;
		Hero.dir = LeftRun;
		Hero.dr.x -= V;
	}
	if (kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && isin({ Hero.dr.x,Hero.dr.y - V }, { 0,0,WIDTH,HEIGHT - 100 }))
	{
		Hero.dir = BackRun;
		Hero.dr.y -= V;
	}
	if (kstate[SDL_SCANCODE_S] && !(kstate[SDL_SCANCODE_W]) && isin({ Hero.dr.x,Hero.dr.y + V }, { 0,0,WIDTH,HEIGHT - 100 }))
	{
		Hero.dir = FrontRun;
		Hero.dr.y += V;
	}
	if (!kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && !kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]) && Hero.dirleft)
		Hero.dir = LeftNondir;
	if (!kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && !kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]) && !Hero.dirleft)
		Hero.dir = RightNondir;
}

void HeroShot()
{
	SDL_Point mp;
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	if (mstate & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
	}
}

void Gamemode(int& mode)
{

	static int dt = 0, lt = 0;
	int ct = SDL_GetTicks(),FPS = 24;
	dt += ct - lt;

	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	if (dt > 1000 / FPS)
	{
		HeroMove();
		HeroShot();
	}
	HeroDv();
	lt = ct;
}