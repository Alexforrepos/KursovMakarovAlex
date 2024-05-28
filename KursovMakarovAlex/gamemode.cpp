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
#include "Effects.h"

enum dirrectionsofhero
{
	LeftHero, RightHero, DownHero, UpHero, StayHero
};

void CreateProjectile(float alpha)
{
	SDL_Point mp;
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	projectiledata tmpprojectile;
	tmpprojectile.damage = Hero->W[Hero->currentWeapon].damage + Hero->ItemsInventory[damageboost] * 10;
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
		bool ispooled = false;
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
		if (!ispooled)
		{
			SDL_RenderCopyExF(ren, cur->data.Textures->PrivateTexture[0], NULL, &cur->data.drect, cur->data.angle * 180 / M_PI, NULL, SDL_FLIP_NONE);
		}
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
	static int lastwapon = 0;
#pragma endregion

#pragma region createProjectile
	Hero->W[Hero->currentWeapon].dr = { Hero->dr.x + Hero->dr.w / 2 - Hero->W[lastwapon].dr.w / 2,Hero->dr.y + Hero->dr.h / 2 - Hero->W[lastwapon].dr.h / 2,Hero->W[lastwapon].dr.w,Hero->W[lastwapon].dr.h };
	lastwapon = Hero->currentWeapon;
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
	SDL_RenderCopyExF(ren, Hero->W[Hero->currentWeapon].T, &Hero->W[Hero->currentWeapon].cr, &Hero->W[Hero->currentWeapon].dr, !Hero->isfliped ? GetAlpha(p, GetCenterPointOfRect(Hero->dr)) * 180 / M_PI : GetAlpha(p, GetCenterPointOfRect(Hero->dr)) * 180 / M_PI - 180, NULL, !Hero->isfliped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void EffectsProc()
{
	EFFECT_ELEMENT* cur = EffQuue->Head, * tmpcur = nullptr;
	while (cur != nullptr) {
		if (cur->Data.mustbepooled)
		{
			tmpcur = cur->Next;
			PULLEFFECT(EffQuue);
			cur = tmpcur;
		}
		else {
			EffectRender(cur);
			cur = cur->Next;
		}
	}
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

void enemyprocess()
{
	enemy* cur = Equeue.head;
	while (cur != nullptr)
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

void ShopMode(SDL_Texture* bacgr, int& gamemode, int& mode)
{
	SDL_Point mp;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	SDL_FPoint p = { mp.x,mp.y };


	SDL_SetRenderDrawColor(ren, 120, 0, 255, 255);
	SDL_RenderClear(ren);

	SDL_Rect LeftRect = { 0,0,WIDTH / 2,HEIGHT };
	SDL_Rect RightRect = { WIDTH / 2,0,WIDTH / 2,HEIGHT };

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

void HeroMove()
{

	SDL_Point mp;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	bool ismirored = false;
	bool ismove = false;
	static int lastx = 0, lasty = 0;
	int speed = 10;

	int ct = SDL_GetTicks();
	static int lt = ct;

	if (mp.x > Hero->dr.x)
		Hero->isfliped = true;
	else
		Hero->isfliped = false;


	if (!isinRect(Hero->dr, { 0,0,(float)WIDTH,(float)HEIGHT })) {
		Hero->dr = { (float)lastx,(float)lasty,Hero->dr.w,Hero->dr.h };
		if (Hero->dr.x < 0)
			Hero->dr.x = 0;
		if (Hero->dr.y < 0)
			Hero->dr.y = 0;
		if (Hero->dr.x + Hero->dr.w > WIDTH)
			Hero->dr.x = WIDTH - Hero->dr.w;
		if (Hero->dr.y + Hero->dr.h > HEIGHT)
			Hero->dr.y = HEIGHT - Hero->dr.h;
	}

	if (ct - lt > 1000 / 24)
	{

		if (kstate[SDL_SCANCODE_W] && !kstate[SDL_SCANCODE_S])
		{
			Hero->dr.y -= speed * (1 + Hero->ItemsInventory[speedboost] / 10.0);
			ismove = true;
		}

		if (kstate[SDL_SCANCODE_S] && !kstate[SDL_SCANCODE_W])
		{
			Hero->dr.y += speed * (1 + Hero->ItemsInventory[speedboost] / 10.0);
			ismove = true;
		}

		if (kstate[SDL_SCANCODE_A] && !kstate[SDL_SCANCODE_D])
		{
			Hero->dr.x -= speed * (1 + Hero->ItemsInventory[speedboost] / 10.0);
			ismove = true;
		}

		if (kstate[SDL_SCANCODE_D] && !kstate[SDL_SCANCODE_A])
		{
			Hero->dr.x += speed * (1 + Hero->ItemsInventory[speedboost] / 10.0);
			ismove = true;
		}
		lt = ct;
	}
	SpleetAnimation(Hero->TEXTURES[Hero->isfliped ? Hero_Spleet_Animation_R - 2 : Hero_Spleet_Animation -2], Hero->phaseofanimation, Hero->dr, true, !ismove, Hero->Time);
}

void HP_RENDER()
{
		int numHearts = Hero->HP > 10 ? Hero->HP / 10 : 0 ; 
		for (int i = 0; i < numHearts; ++i)
		{
			SDL_Rect destRect = { 20 + i * (ALL_TEXTURES->ALL_LOCAL_TEXTURES[Icons].SR[0].w  + 10), 20, ALL_TEXTURES->ALL_LOCAL_TEXTURES[Icons].SR[0].w, ALL_TEXTURES->ALL_LOCAL_TEXTURES[Icons].SR[0].h }; // учитываем расстояние между сердечками
			SDL_RenderCopy(ren, ALL_TEXTURES->ALL_LOCAL_TEXTURES[Icons].PrivateTexture[0], NULL, &destRect);
		}
}

void MONEY_RENDER()
{

}


void Gamemode(int& mode)
{
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	static int dt = 0, lt = SDL_GetTicks();
	int ct = SDL_GetTicks(), FPS = 24;
	static SDL_Texture* tmp_backgr = nullptr;
	static int gamemode = 0;

	dt += ct - lt;
	lt = ct;
	Hero->dr = { Hero->dr.x,Hero->dr.y,(float)Hero->TEXTURES[Hero->isfliped ? Hero_Spleet_Animation_R - 2 : Hero_Spleet_Animation - 2]->SR[Hero->phaseofanimation].w,(float)Hero->TEXTURES[Hero->isfliped ? Hero_Spleet_Animation_R - 2 : Hero_Spleet_Animation - 2]->SR[Hero->phaseofanimation].h };
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
		HP_RENDER();

		HeroMove();
		HeroShot();
		enemyprocess();
		ItemProcess();
		EffectsProc();
		if (kstate[SDL_SCANCODE_ESCAPE])
		{
			Hero->dr = { 0, 0, Hero->dr.w, Hero->dr.h };
			FileHeroStatsSave(currentsave);
			mode = 0;
		}

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
	}
}