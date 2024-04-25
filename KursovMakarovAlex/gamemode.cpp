#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "texturesimport.h"
#include "SpleetProcessing.h"
#include "SDLProcessing.h"
#include "gamemode.h"
#include "Hero.h"
#include "projectile.h"
#include "enemy.h"
#include "Geometry.h"

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
	tmpprojectile.drect = { Hero->dr.x + Hero->dr.w / 2,Hero->dr.y + Hero->dr.h / 2,20,20 };
	tmpprojectile.angle = SDL_atan2(mp.y - Hero->dr.y, mp.x - Hero->dr.x);
	printf("angle %lf\n", tmpprojectile.angle);
	PushProjectile(Projectiles, tmpprojectile);
}

void HeroShot()
{
	bool ispooled = false;
	SDL_Point mp;
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
#pragma region timeofHeroshot
	static int dt = 0, lt = 0;
	int ct = SDL_GetTicks();
	dt += ct - lt;
#pragma endregion

#pragma region createProjectile
	if (mstate & SDL_BUTTON(SDL_BUTTON_LEFT) && Hero->W[Hero->currentWeapon].cd < 0)
	{
		CreateProjectile();
		Hero->W[Hero->currentWeapon].cd = Hero->W[Hero->currentWeapon].reloadtime;
	}
#pragma endregion
	projectile* cur = Projectiles.head;
	while(cur != nullptr)
	{	
		projectile* nextProjectile = cur->next;
		if (cur->data.livetime < 0 )
		{
			PullProjectile(Projectiles, cur);
			break;
		}
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		cur->data.livetime -= ct - lt;
		cur->data.drect.x += cos(cur->data.angle) * (double)cur->data.speed;
		cur->data.drect.y += sin(cur->data.angle) * (double)cur->data.speed;
		for (enemy* curenemy = Equeue.head; curenemy != nullptr; curenemy = curenemy->next)
		{
			if (isinRect(cur->data.drect, curenemy->data.dr))
			{
				curenemy->data.ishit = true;
				curenemy->data.HP -= cur->data.damage;
				if (curenemy->data.HP < 0)
					
				PullProjectile(Projectiles, cur);
				ispooled = true;
				break;
			}
		}
		SDL_RenderFillRectF(ren, &cur->data.drect);
		cur = nextProjectile;
	}
	if (Hero && Hero->W)
	{
		Hero->W[Hero->currentWeapon].cd -= ct - lt;
	}
	lt = ct;
}

void HeroMove()
{
	int V = 1;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	if (kstate[SDL_SCANCODE_D] && !(kstate[SDL_SCANCODE_A]))
	{
		Hero->dirleft = 0;
		Hero->dir = Rightrun;
		Hero->dr.x += V;
	}
	if (kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]))
	{
		Hero->dirleft = 1;
		Hero->dir = LeftRun;
		Hero->dr.x -= V;
	}
	if (kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]))
	{
		Hero->dir = BackRun;
		Hero->dr.y -= V;
	}
	if (kstate[SDL_SCANCODE_S] && !(kstate[SDL_SCANCODE_W]))
	{
		Hero->dir = FrontRun;
		Hero->dr.y += V;
	}
	if (!kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && !kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]) && Hero->dirleft)
		Hero->dir = LeftNondir;
	if (!kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && !kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]) && !Hero->dirleft)
		Hero->dir = RightNondir;
}

void enemyprocess()
{
	for (enemy *curenemy = Equeue.head; curenemy != nullptr; curenemy = curenemy->next)
	{
		enemyprocessing(curenemy);
	}
}

void Gamemode(int& mode)
{
#pragma region timeofgamemod
	static int dt = 0, lt = 0;
	int ct = SDL_GetTicks(), FPS = 24;
	dt += ct - lt;
#pragma endregion

	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);


	if (dt > 1000 / FPS)
	{
		HeroMove();
		HeroShot();
		enemyprocess();
	}
	if (kstate[SDL_SCANCODE_ESCAPE])
	{
		mode = 0;
		Hero->dr = { 0,0,Hero->dr.w,Hero->dr.h };
	}
	HeroDv();
	lt = ct;
}