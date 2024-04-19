#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cmath>

#include "texturesimport.h"
#include "SpleetProcessing.h"
#include "SDLProcessing.h"
#include "Mouse.h"
#include "gamemode.h"
#include "Hero.h"
#include "projectile.h"


enum dirrectionsofhero
{
	LeftHero, RightHero, DownHero, UpHero, StayHero
};

void CreateProjectile()
{
	SDL_Point mp;
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);

	projectiledata tmpprojectile;
	tmpprojectile.damage = Hero->W[Hero->currentWeapon].damage;
	tmpprojectile.livetime = 3000;
	tmpprojectile.speed = Hero->W[Hero->currentWeapon].bulletspeed;
	tmpprojectile.drect = { Hero->dr.x,Hero->dr.y,20,20 };
	tmpprojectile.angle = atan2(mp.x - Hero->dr.x,mp.y - Hero->dr.y);

	PushProjectile(Projectiles, tmpprojectile);
}

void HeroShot()
{
	SDL_Point mp;
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);

	static int dt = 0,lt = 0;
	int ct = SDL_GetTicks();
	dt += ct - lt;
#pragma region createProjectile
	if (mstate & SDL_BUTTON(SDL_BUTTON_LEFT) )
	{
		CreateProjectile();

	}
#pragma endregion

#pragma region drowprojectile

	for (projectile* cur = Projectiles.head; cur != NULL; cur = cur->next)
	{
		if (cur->data.livetime < 0)
		{
			PullProjectileData(Projectiles);
			continue;
		}
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		cur->data.livetime -= ct - lt;
		cur->data.drect.x += cos(cur->data.angle) * cur->data.speed;
		cur->data.drect.y += sin(cur->data.angle) * cur->data.speed;
		SDL_RenderFillRect(ren,&cur->data.drect);
	}
	Hero->W[Hero->currentWeapon].cd -= ct - lt;
	lt = ct;
#pragma endregion
}

void HeroMove()
{
	int V = 1;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	if (kstate[SDL_SCANCODE_D] && !(kstate[SDL_SCANCODE_A]) && isin({ Hero->dr.x + V,Hero->dr.y }, { 0,0,WIDTH * 2,HEIGHT - 100 }))
	{
		Hero->dirleft = 0;
		Hero->dir = Rightrun;
		Hero->dr.x += V;
	}
	if (kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]) && isin({ Hero->dr.x - V,Hero->dr.y }, { 0,0,WIDTH * 2,HEIGHT - 100 }))
	{
		Hero->dirleft = 1;
		Hero->dir = LeftRun;
		Hero->dr.x -= V;
	}
	if (kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && isin({ Hero->dr.x,Hero->dr.y - V }, { 0,0,WIDTH * 2,HEIGHT - 100 }))
	{
		Hero->dir = BackRun;
		Hero->dr.y -= V;
	}
	if (kstate[SDL_SCANCODE_S] && !(kstate[SDL_SCANCODE_W]) && isin({ Hero->dr.x,Hero->dr.y + V }, { 0,0,WIDTH * 2 ,HEIGHT - 100 }))
	{
		Hero->dir = FrontRun;
		Hero->dr.y += V;
	}
	if (!kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && !kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]) && Hero->dirleft)
		Hero->dir = LeftNondir;
	if (!kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && !kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]) && !Hero->dirleft)
		Hero->dir = RightNondir;
}

void Gamemode(int& mode)
{

	static int dt = 0, lt = 0;
	int ct = SDL_GetTicks(), FPS = 24;
	dt += ct - lt;

	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	if (dt > 1000 / FPS)
	{
		HeroMove();
		HeroShot();
	}
	if (kstate[SDL_SCANCODE_ESCAPE])
	{
		mode = 0;
		Hero->dr = { 0,0,Hero->dr.w,Hero->dr.h };
	}
	HeroDv();
	lt = ct;
}