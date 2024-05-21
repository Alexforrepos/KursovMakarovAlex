#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Items.h"
#include "texturesimport.h"
#include "SpleetProcessing.h"
#include "SDLProcessing.h"
#include "gamemode.h"
#include "Hero.h"
#include "projectile.h"
#include "enemy.h"
#include "Geometry.h"
#include "FileM.h"

enum dirrectionsofhero
{
	LeftHero, RightHero, DownHero, UpHero, StayHero
};

void CreateProjectile(float alpha)
{
	SDL_Point mp;
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	projectiledata tmpprojectile;
	tmpprojectile.damage = Hero->W[Hero->currentWeapon].damage + Hero->ItemsInventory[damageboost]*10;
	tmpprojectile.livetime = 3000;
	tmpprojectile.speed = Hero->W[Hero->currentWeapon].bulletspeed;
	tmpprojectile.drect = { Hero->dr.x + Hero->dr.w / 2,Hero->dr.y + Hero->dr.h / 2,20,20 };
	tmpprojectile.angle = alpha;
	PushProjectile(Projectiles, tmpprojectile);
}

void BulletsProc()
{
	bool ispooled = false;
	static int dt = 0, lt = 0;
	int ct = SDL_GetTicks();
	projectile* cur = Projectiles.head;
	while (cur != nullptr)
	{
		projectile* nextProjectile = cur->next;
		if (cur->data.livetime < 0)
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
				PullProjectile(Projectiles, cur);
				ispooled = true;
				break;
			}
		}
		SDL_RenderFillRectF(ren, &cur->data.drect);
		cur = nextProjectile;
	}
	lt = ct;
}

void ShotgunShoot()
{
	SDL_Point mp;
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	SDL_FPoint p = { mp.x,mp.y };
	CreateProjectile(GetAlpha(GetCenterPointOfRect(Hero->dr), p));
	CreateProjectile(GetAlpha(GetCenterPointOfRect(Hero->dr), p) + M_PI / 6);
	CreateProjectile(GetAlpha(GetCenterPointOfRect(Hero->dr), p) - M_PI / 6);
}

void HeroShot()
{

	SDL_Point mp;
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	SDL_FPoint p = { mp.x,mp.y };
#pragma region timeofHeroshot
	static int dt = 0, lt = 0;
	int ct = SDL_GetTicks();
	dt += ct - lt;
#pragma endregion

#pragma region createProjectile
	if (mstate & SDL_BUTTON(SDL_BUTTON_LEFT) && Hero->W[Hero->currentWeapon].cd - Hero->ItemsInventory[firerate] < 0)
	{
		switch (Hero->currentWeapon)
		{
		case 0:
			CreateProjectile(GetAlpha(GetCenterPointOfRect(Hero->dr), p));
			break;
		case 1:
			ShotgunShoot();
			break;
		default:
			break;
		}
		Hero->W[Hero->currentWeapon].cd = Hero->W[Hero->currentWeapon].reloadtime;
	}
#pragma endregion
	BulletsProc();

	if (Hero && Hero->W)
	{
		Hero->W[Hero->currentWeapon].cd -= ct - lt;
	}
	lt = ct;
}

void ItemProcess()
{
	ItemRender(IDeq);
	for (Item* cur = IDeq->Head; cur != nullptr; cur = cur->Next)
	{
		if (GetDistance(GetCenterPointOfRect(Hero->dr), GetCenterPointOfRect(cur->Data.Dr)) < 40)
		{
			ItemGet(cur);
			break;
		}
	}
}

void HeroMove()
{
	int V = 1;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	static float lastx=0, lasty=0;
	if (!isinRect(Hero->dr, { 0,0,(float)WIDTH,(float)HEIGHT }))
	{
		Hero->dr = { lastx,lasty,Hero->dr.w,Hero->dr.h };
		return;
	}
	if (kstate[SDL_SCANCODE_D] && !(kstate[SDL_SCANCODE_A]) && isinRect(Hero->dr, { 0,0,(float)WIDTH,(float)HEIGHT }))
	{
		lastx = Hero->dr.x;
		lasty = Hero->dr.y;
		Hero->dirleft = 0;
		Hero->dir = Rightrun;
		Hero->dr.x += V*(1+Hero->ItemsInventory[speedboost]/10);
	}
	if (kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]) && isinRect(Hero->dr, { 0,0,(float)WIDTH,(float)HEIGHT }))
	{
		lastx = Hero->dr.x;
		lasty = Hero->dr.y;
		Hero->dirleft = 1;
		Hero->dir = LeftRun;
		Hero->dr.x -= V * (1 + Hero->ItemsInventory[speedboost] / 10);
	}
	if (kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && isinRect(Hero->dr, { 0,0,(float)WIDTH,(float)HEIGHT }))
	{
		Hero->dir = BackRun;
		Hero->dr.y -= V * (1 + Hero->ItemsInventory[speedboost] / 10);
	}
	if (kstate[SDL_SCANCODE_S] && !(kstate[SDL_SCANCODE_W]) && isinRect(Hero->dr,{ 0,0,(float)WIDTH,(float)HEIGHT }))
	{
		lastx = Hero->dr.x;
		lasty = Hero->dr.y;
		Hero->dir = FrontRun;
		Hero->dr.y += V*(1+Hero->ItemsInventory[speedboost]/10);
	}
	if (!kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && !kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]) && Hero->dirleft && isinRect(Hero->dr,{0,0,(float)WIDTH,(float)HEIGHT}))
		Hero->dir = LeftNondir;
	if (!kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && !kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]) && !Hero->dirleft && isinRect(Hero->dr, { 0,0,(float)WIDTH,(float)HEIGHT }))
		Hero->dir = RightNondir;
}

void enemyprocess()
{
	enemy* cur = Equeue.head;
	while(cur!=nullptr)
	{
		enemyprocessing(cur);
		if (cur->data.HP <= 0)
		{
			enemy* N = cur->next;
			if (N == nullptr)
			{
				RemoveEnemyQ(Equeue, cur);
				Hero->Money += 999;
				break;
			}
			ItemsFall(GetCenterPointOfRect(cur->data.dr));
			RemoveEnemyQ(Equeue, cur);
			cur = N;
		}
		else
		{ 
		cur = cur->next;
		}
	}
}

void ShopMode(SDL_Texture* bacgr,int &gamemode, int& mode)
{
	SDL_Point mp;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	SDL_FPoint p = { mp.x,mp.y };


	SDL_SetRenderDrawColor(ren, 120, 0, 255, 255);
	SDL_RenderClear(ren);

	SDL_Rect LeftRect = {0,0,WIDTH/2,HEIGHT};
	SDL_Rect RightRect = { WIDTH / 2,0,WIDTH/2,HEIGHT};

	SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
	SDL_RenderFillRect(ren, &LeftRect);
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderFillRect(ren, &RightRect);
	

	if (isinPoint(mp, LeftRect))
	{
		if (mstate && SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			Hero->Money -= 200 * (1 + ItemSumm() / 10);
			Hero->HP += 200;
			gamemode = 0;
			FileEnemyQGet(mode);
		}
	}
	else
	{
		if (mstate && SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			Hero->Money -= 200 * (1 + ItemSumm() / 10);
			for (int i = 0; i < 4; i++)
			{
				if (!Hero->W[i].enabled)
				{
					Hero->W[i].enabled = !Hero->W[i].enabled;
					return;
				}
			}
			gamemode = 0;
			FileEnemyQGet(mode);
		}
	}
}

void Gamemode(int& mode)
{
#pragma region timeofgamemod
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	static int dt = 0, lt = 0;
	int ct = SDL_GetTicks(), FPS = 24;
	static SDL_Texture* tmp_backgr = nullptr;
	dt += ct - lt;
	static int gamemode = 0;
#pragma endregion

	if (kstate[SDL_SCANCODE_1] && Hero->W[0].enabled)
	{
		Hero->currentWeapon = 0;
	}
	if (kstate[SDL_SCANCODE_2] && Hero->W[1].enabled)
	{
		Hero->currentWeapon = 1;
	}
	if (kstate[SDL_SCANCODE_3] && Hero->W[2].enabled)
	{
		Hero->currentWeapon = 2;
	}
	if (kstate[SDL_SCANCODE_4] && Hero->W[3].enabled)
	{
		Hero->currentWeapon = 3;
	}

	switch (gamemode)
	{
	case 0:
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);
		if (dt > 1000 / FPS)
		{
			HeroMove();
			HeroShot();
			enemyprocess();
			ItemProcess();
		}
		if (kstate[SDL_SCANCODE_ESCAPE])
		{
			Hero->dr = { 0,0,Hero->dr.w,Hero->dr.h };
			FileHeroStatsSave(currentsave);
			mode = 0;
		}
		HeroDv();
		lt = ct;
		if (Equeue.head == nullptr)
		{
			ClearItem(IDeq);
			tmp_backgr = CaptureScreenTexture(ren);
			gamemode = 1;
		}
		break;
	case 1:
		ShopMode(tmp_backgr, gamemode, mode);
		break;
	default:
		break;
	}

}