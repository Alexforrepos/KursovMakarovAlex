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
#include "TextProcessing.h"
#include "Shop.h"




void InventoryScore(SDL_Texture* T[7], char buf1[], char buf2[], char buf3[], char buf4[])
{
	T[3] = CreateTextTexture(ren, Fonts[0], buf1, { 255,255,255,255 }, 600, 600);
	T[4] = CreateTextTexture(ren, Fonts[0], buf2, { 255,255,255,255 }, 600, 600);
	T[5] = CreateTextTexture(ren, Fonts[0], buf3, { 255,255,255,255 }, 600, 600);
	T[6] = CreateTextTexture(ren, Fonts[0], buf4, { 255,255,255,255 }, 600, 600);
}

void InitTexturesForRenderForScore(SDL_Texture* T[7], char buf1[], char buf2[], char buf3[])
{
	T[0] = CreateTextTexture(ren, Fonts[0], buf1, { 255,255,255,255 }, 400, 400);
	T[1] = CreateTextTexture(ren, Fonts[0], buf2, { 255,255,255,255 }, 400, 400);
	T[2] = CreateTextTexture(ren, Fonts[0], buf3, { 255,255,255,255 }, 400, 400); 
}

void Score_Render(int &mode)
{
	static int lt = SDL_GetTicks();
	int ct = SDL_GetTicks();
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	char tmp[100];
	static SDL_Texture* Ts[7];
	static bool isred = true;
	SDL_SetRenderDrawColor(ren, 120, 120, 120,255);
	SDL_RenderClear(ren);
	SDL_Rect R = { 100,100,1700,800 };
	SDL_RenderCopy(ren, ALL_TEXTURES->ALL_LOCAL_TEXTURES[Menu_Background].PrivateTexture[1], NULL, &R);
	char buffforQE[50], buffforMoney[50], bufforscore[50];

	sprintf_s(buffforQE, "Enemies Killed: %d",Hero->enemK);
	sprintf_s(bufforscore, "Score Get: %d",Save.BSS.Score);
	sprintf_s(buffforMoney, "Money Gain: %d",Hero->Money);

	char buffforInvDamage[50], buffforInvSpeed[50], bufforInvScore[50], buffforRate[50];

	sprintf_s(buffforInvDamage, "Damage MULT: %.2f", 1 + Hero->ItemsInventory[0] / 10.0);
	sprintf_s(buffforInvSpeed, "Speed MULT: %.2f", 1 + Hero->ItemsInventory[1] / 10.0);
	sprintf_s(bufforInvScore, "Score MULT: %.2f", 1 + Hero->ItemsInventory[2] / 10.0);
	sprintf_s(buffforRate, "FireRate MULT: %.2f", 1+Hero->ItemsInventory[3]/10.0);

	static SDL_Rect QERCT;
	static SDL_Rect InvDmgR;
	static SDL_Rect SRCT;
	static SDL_Rect InvSpeedR;
	static SDL_Rect MRECT;
	static SDL_Rect InvScoreR;
	static SDL_Rect InvFRR;

	if (isred)
	{
		InitTexturesForRenderForScore(Ts, buffforQE, bufforscore, buffforMoney);
		InventoryScore(Ts, buffforInvDamage, buffforInvSpeed, bufforInvScore, buffforRate);
		isred = false;
		lt = SDL_GetTicks();
		 QERCT = GetTextureAllRect(Ts[0], 1); QERCT = { R.x + 100,R.y + 100, QERCT.w ,QERCT.h  };
		 SRCT = GetTextureAllRect(Ts[1], 1);	SRCT = { QERCT.x,QERCT.y + QERCT.h + 50,SRCT.w ,SRCT.h  };
		 MRECT = GetTextureAllRect(Ts[2], 1);	MRECT = { SRCT.x,SRCT.y + SRCT.h + 50,MRECT.w ,MRECT.h  };

		 InvFRR = GetTextureAllRect(Ts[3], 1);	InvFRR = { QERCT.x + QERCT.w + 50,R.y + 100,InvFRR.w ,InvFRR.h  };
		 InvScoreR = GetTextureAllRect(Ts[4], 1);	InvScoreR = { QERCT.x + SRCT.w + 50,QERCT.y + QERCT.h + 50,InvScoreR.w ,InvScoreR.h  };
		 InvSpeedR = GetTextureAllRect(Ts[5], 1);	InvSpeedR = { QERCT.x + MRECT.w + 50,SRCT.y + SRCT.h + 50,InvSpeedR.w ,InvSpeedR.h  };
		 InvDmgR = GetTextureAllRect(Ts[6], 1);	InvDmgR = { QERCT.x + QERCT.w,InvSpeedR.y + InvSpeedR.h + 50,InvDmgR.w ,InvDmgR.h  };

	}

	SDL_RenderCopy(ren, Ts[0], NULL, &QERCT);
	SDL_RenderCopy(ren, Ts[1], NULL, &SRCT);
	SDL_RenderCopy(ren, Ts[2], NULL, &MRECT);
	SDL_RenderCopy(ren, Ts[3], NULL, &InvFRR);
	SDL_RenderCopy(ren, Ts[4], NULL, &InvScoreR);
	SDL_RenderCopy(ren, Ts[5], NULL, &InvSpeedR);
	SDL_RenderCopy(ren, Ts[6], NULL, &InvDmgR);
	
	if (ct - lt > 10000)
	{
		SDL_DestroyTexture(Ts[0]);
		SDL_DestroyTexture(Ts[1]);
		SDL_DestroyTexture(Ts[2]);
		SDL_DestroyTexture(Ts[3]);
		SDL_DestroyTexture(Ts[4]);
		SDL_DestroyTexture(Ts[5]);
		SDL_DestroyTexture(Ts[6]);
		isred = 1;
		strcpy_s(tmp, "TextInformation/EnemyQueue.txt");
		WavesProcessing(Save, tmp);
		mode = 2;
	}
}

void Death(int &mode)
{
	static bool newran = false;
	if (newran)
		newran = false;
	int ct = SDL_GetTicks();
	static int lt = SDL_GetTicks();
	Score_Render(mode);
	char tmp[100] = "You Are Dead";
	static SDL_Texture * T = CreateTextTexture(ren, Fonts[0], tmp, { 255,255,255,255 }, 400, 200);
	int w, h;
	GetTextureDimensions(T, &w, &h);
	static SDL_Rect Dr = { WIDTH / 2,50,w,h };
	SDL_RenderCopy(ren, T, NULL, &Dr);
	if (ct - lt > 10000 && !newran)
	{
		mode = 0;
		Save.BSS.is_running = 0;
		newran = true;
	}
}

enum dirrectionsofhero
{
	LeftHero, RightHero, DownHero, UpHero, StayHero
};

void WALLS(int screenWidth, int screenHeight)
{

	SDL_SetRenderDrawColor(ren, 255, 223, 130, 255);
	SDL_Rect screen = { 10, 10, screenWidth - 20, screenHeight - 20 };
	SDL_RenderFillRect(ren, &screen);
	

	SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
	SDL_Rect topWall = { 0, 0, screenWidth, 10 };
	SDL_RenderFillRect(ren, &topWall);

	SDL_Rect bottomWall = { 0, screenHeight - 10, screenWidth, 10 };
	SDL_RenderFillRect(ren, &bottomWall);


	SDL_Rect leftWall = { 0, 0, 10, screenHeight };
	SDL_RenderFillRect(ren, &leftWall);


	SDL_Rect rightWall = { screenWidth - 10, 0, 10, screenHeight };
	SDL_RenderFillRect(ren, &rightWall);



}

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
	SDL_Point mp;
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	SDL_FPoint p = { mp.x,mp.y };
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
		if (Save.BF.ORBIT_TRAECTORY)
		{
			cur->data.drect.x = Hero->dr.x + GetDistance(GetCenterPointOfRect(Hero->dr),p) * cos(cur->data.angle);
			cur->data.drect.y = Hero->dr.y + GetDistance(GetCenterPointOfRect(Hero->dr), p) * sin(cur->data.angle);
			cur->data.angle += ((float)cur->data.speed) / GetDistance(GetCenterPointOfRect(Hero->dr), p);
		}
		else
		{
			cur->data.drect.x += cos(cur->data.angle) * (double)cur->data.speed;
			cur->data.drect.y += sin(cur->data.angle) * (double)cur->data.speed;
		}
		for (enemy* curenemy = Equeue.head; curenemy != nullptr; curenemy = curenemy->next)
		{
			if (SDL_HasIntersectionF(&cur->data.drect, &curenemy->data.dr))
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



void DrawAndShootLaser(int startX, int startY, int length, int height, float angle, int lineWidth) {
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255); // Устанавливаем цвет лазерного луча
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND); // Устанавливаем режим наложения для управления толщиной линии


	// Рассчитываем координаты конечной точки лазерного луча
	int endX = startX + length * cos(angle);
	int endY = startY + length * sin(angle);

	// Устанавливаем толщину линии
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
	SDL_RenderDrawLine(ren, startX, startY, endX, endY);

	// "Выстрел" лазером (можно добавить дополнительные эффекты или действия)
}

bool CheckLaserRectangleIntersection(int startX, int startY, float angle, int length, const SDL_FRect& rect) {
	float radianAngle = angle;

	// Вычисляем координаты конечной точки луча
	int endX = startX + static_cast<int>(length * cos(radianAngle));
	int endY = startY + static_cast<int>(length * sin(radianAngle));

	// Проверяем пересечение луча и прямоугольника
	// Проверяем пересечение с левой, правой, верхней и нижней сторонами прямоугольника
	if ((startX <= static_cast<int>(rect.x + rect.w) && endX >= static_cast<int>(rect.x) &&
		startY <= static_cast<int>(rect.y + rect.h) && endY >= static_cast<int>(rect.y)) ||
		(startX >= static_cast<int>(rect.x) && endX <= static_cast<int>(rect.x + rect.w) &&
			startY <= static_cast<int>(rect.y) && endY >= static_cast<int>(rect.y))) {
		// Произошло пересечение
		return true;
	}

	return false;
}


void HeroShot()
{

	SDL_Point mp;
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	SDL_FPoint p = { mp.x,mp.y };
	enemy* cur = Equeue.head;
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
		case 2:
			CreateProjectile(GetAlpha(GetCenterPointOfRect(Hero->dr), p));
			break;
		case 3:
			DrawAndShootLaser(Hero->dr.x + Hero->dr.w / 2, Hero->dr.y + Hero->dr.h / 2, 4000, 10, GetAlpha({ Hero->dr.x + Hero->dr.w / 2, Hero->dr.y + Hero->dr.h / 2 }, p), 10);

			while (cur != nullptr)
			{
				if (CheckLaserRectangleIntersection(Hero->dr.x + Hero->dr.w / 2, Hero->dr.y + Hero->dr.h / 2, GetAlpha({ Hero->dr.x + Hero->dr.w / 2, Hero->dr.y + Hero->dr.h / 2 }, p) , 1, cur->data.dr))
				{
					cur->data.HP -= Hero->W[3].damage + (1 + Hero->ItemsInventory[1] / 10);
				}
				cur = cur->next;
			}
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
	SDL_RenderCopyExF(ren, Hero->W[Hero->currentWeapon].T, &Hero->W[Hero->currentWeapon].cr, &Hero->W[Hero->currentWeapon].dr, 
		!Hero->isfliped ? GetAlpha(p, GetCenterPointOfRect(Hero->dr)) * 180 / M_PI : GetAlpha(p, GetCenterPointOfRect(Hero->dr)) * 180 / M_PI - 180, NULL, !Hero->isfliped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
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
			Save.BSS.Score += 10 * Hero->ItemsInventory[2];
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
				Hero->Money += 100;
				Save.BSS.Score += 100 * (1 + Hero->ItemsInventory[mult] / 10);
				Hero->enemK += 1;
				break;
			}
			Hero->Money += 100;
			Save.BSS.Score += 100 * (1 + Hero->ItemsInventory[mult] / 10);
			Hero->enemK += 1;
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

void HeroMove()
{
	SDL_Point mp;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	bool ismirrored = false;
	static int ismove = 0;
	static int lastx = 0, lasty = 0;
	static int speed = Save.BF.SPEED?100: 10;

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
	ismove = 0;
	if (ct - lt > 1000 / 24)
	{
		if (kstate[SDL_SCANCODE_W] && !kstate[SDL_SCANCODE_S])
		{
			Hero->dr.y -= speed * (1 + Hero->ItemsInventory[speedboost] / 10.0);
			ismove = 1;
		}
		if (kstate[SDL_SCANCODE_S] && !kstate[SDL_SCANCODE_W])
		{
			Hero->dr.y += speed * (1 + Hero->ItemsInventory[speedboost] / 10.0);
			ismove = 1;
		}
		if (kstate[SDL_SCANCODE_A] && !kstate[SDL_SCANCODE_D])
		{
			Hero->dr.x -= speed * (1 + Hero->ItemsInventory[speedboost] / 10.0);
			ismove = 1;
		}
		if (kstate[SDL_SCANCODE_D] && !kstate[SDL_SCANCODE_A])
		{
			Hero->dr.x += speed * (1 + Hero->ItemsInventory[speedboost] / 10.0);
			ismove = 1;
		}
		if (!kstate[SDL_SCANCODE_D] && !kstate[SDL_SCANCODE_A] && !kstate[SDL_SCANCODE_S] && !kstate[SDL_SCANCODE_W])
		{
			ismove = 0;
			if (Save.BF.FLOOR_IS_LAVA)
				Hero->HP -= 10;
		}
		lt = ct;
	}
	SpleetAnimation(Hero->TEXTURES[Hero->isfliped ? Hero_Spleet_Animation_R - 2 : Hero_Spleet_Animation - 2], Hero->phaseofanimation, Hero->dr, true, ismove, Hero->Time);
}

void HP_RENDER()
{
		int numHearts =  Hero->HP / 100 ; 
		for (int i = 0; i < numHearts; ++i)
		{
			SDL_Rect destRect = { 20 + i * (ALL_TEXTURES->ALL_LOCAL_TEXTURES[Icons].SR[0].w  + 10), 20,
				ALL_TEXTURES->ALL_LOCAL_TEXTURES[Icons].SR[0].w, ALL_TEXTURES->ALL_LOCAL_TEXTURES[Icons].SR[0].h }; // учитываем расстояние между сердечками
			SDL_RenderCopy(ren, ALL_TEXTURES->ALL_LOCAL_TEXTURES[Icons].PrivateTexture[0], NULL, &destRect);
		}
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
		WALLS(WIDTH,HEIGHT);
		HP_RENDER();

		HeroMove();
		HeroShot();
		enemyprocess();
		ItemProcess();
		EffectsProc();
		if (kstate[SDL_SCANCODE_ESCAPE])
		{
			Hero->dr = { 0, 0, Hero->dr.w, Hero->dr.h };
			DataSave(Save, LastFileSaveUsed);
			mode = 0;
		}

		if (Equeue.head == nullptr)
		{
			ClearItem(IDeq);
			tmp_backgr = CaptureScreenTexture(ren);
			gamemode = 1;
			Hero->dr.x = WIDTH / 2;
			Hero->dr.h = HEIGHT - 100;
		}
		if (Hero->HP <= 0)
			gamemode = 3;
		if (Save.BF.INV)
			Hero->HP = 1000;
		break;

	case 1:
		Score_Render(gamemode);
		break;
	case 2:
		Shopmode(gamemode);
		break;
	case 3:
		Death(mode);
	}
}