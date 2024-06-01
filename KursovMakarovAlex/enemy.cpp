#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Geometry.h"
#include "Hero.h"
#include "projectile.h"
#include "enemy.h"
#include  "texturesimport.h"
#include "SDLProcessing.h"
#include "SpleetProcessing.h"
#include "Effects.h"
#include "FileM.h"

#define STOPPING_RADIUS 500

void CreateNewEnemy(EnemyQueue& Queue, int model, SDL_FPoint ep)
{
	enemydata TempData = { 0 };
	TempData.AnimationTime = { 0,0,0,1000 };
	TempData.ShotTime = { 0,0,0,0 };
	TempData.angle = NULL;
	TempData.Textures = nullptr;
	TempData.curstage = 1;
	TempData.ltshot = 0;
	switch (model)
	{
	case 0:
		TempData.Textures = &ALL_TEXTURES->ALL_LOCAL_TEXTURES[Distant_Spleet_Animation];
		TempData.speed = 0.4;
		TempData.CD = 1000;
		TempData.HP = 50;
		TempData.dr = { ep.x , ep.y, 50,50 };
		TempData.model = model;
		break;
	case 1:
		TempData.Textures = &ALL_TEXTURES->ALL_LOCAL_TEXTURES[Melee_Spleet_Animation];
		TempData.speed = 0.7;
		TempData.CD = 0;
		TempData.HP = 100;
		TempData.dr = { ep.x , ep.y,50,50 };
		TempData.model = model;
		break;
	case 2:
		TempData.Textures = &ALL_TEXTURES->ALL_LOCAL_TEXTURES[Summon_Spleet_Animation];
		TempData.speed = 0.1;
		TempData.CD = 0.1;
		TempData.HP = 300;
		TempData.dr = { ep.x , ep.y, 50,50 };
		TempData.model = model;
		break;
	case 3:
		TempData.Textures = &ALL_TEXTURES->ALL_LOCAL_TEXTURES[Saw_Spleet_Animation];
		TempData.speed = 3;
		TempData.CD = 0;
		TempData.HP = 100;
		TempData.dr = { ep.x , ep.y, 50,50 };
		TempData.model = model;
		TempData.angle = rand();
		break;
	case 4:
		TempData.Textures = &ALL_TEXTURES->ALL_LOCAL_TEXTURES[Boom_Spleet_Animatin];
		TempData.speed = 0.2;
		TempData.CD = 0;
		TempData.HP = 200;

		TempData.model = model;
		break;
	default:
		break;

	}
	TempData.dr = { ep.x , ep.y, (float)TempData.Textures->SR[TempData.curstage].w,(float)TempData.Textures->SR[TempData.curstage].h };
	addEnemy(Queue, TempData);
}

#pragma region list

EnemyQueue Equeue;

void addEnemy(EnemyQueue& queue, enemydata data)
{
	enemy* newEnemy = (enemy*)malloc(sizeof(enemy));
	newEnemy->data = data;
	newEnemy->next = nullptr;
	newEnemy->prev = nullptr;

	if (queue.head == nullptr)
	{
		queue.head = newEnemy;
	}
	else
	{
		queue.tail->next = newEnemy;
		newEnemy->prev = queue.tail;
	}

	queue.tail = newEnemy;
}

void RemoveEnemyQ(EnemyQueue& queue, enemy* removeEnemy)
{
	if (removeEnemy->prev != nullptr)
	{
		removeEnemy->prev->next = removeEnemy->next;
	}
	else
	{
		queue.head = removeEnemy->next;
	}

	if (removeEnemy->next != nullptr)
	{
		removeEnemy->next->prev = removeEnemy->prev;
	}
	else
	{
		queue.tail = removeEnemy->prev;
	}

	free(removeEnemy);
}

bool isQueueEmpty(const EnemyQueue& queue)
{
	return queue.head == nullptr && queue.tail == nullptr;
}

void clearEnemies(EnemyQueue& queue)
{
	enemy* curr = queue.head;
	while (curr != nullptr)
	{
		enemy* next = curr->next;
		delete curr;
		curr = next;
	}

	queue.head = nullptr;
	queue.tail = nullptr;
}

#pragma endregion

#pragma region beh
void enemyMoveTowardsPlayer(enemy* en)
{
	static int lt = 0;
	int ct = SDL_GetTicks();
	if (ct - en->data.ltshot > en->data.CD) // Пример для модели 0
	{
		// Создание снаряда
		projectiledata tempdata;
		tempdata.angle = SDL_atan2(Hero->dr.y - en->data.dr.y, Hero->dr.x - en->data.dr.x);
		tempdata.drect = { en->data.dr.x, en->data.dr.y, 20, 20 };
		tempdata.livetime = 3000;
		tempdata.speed = 0.1;
		tempdata.damage = 100;
		PushProjectile(EnemyProjectiles, tempdata);
		en->data.CD = 1000;
		en->data.ltshot = ct;
	}

	if (en == NULL)
	{
		return;
	}

	int distance = sqrt(((Hero->dr.x - en->data.dr.x) * (Hero->dr.x - en->data.dr.x)) + (Hero->dr.y - en->data.dr.y) * (Hero->dr.y - en->data.dr.y));

	if (distance > STOPPING_RADIUS)
	{

		float angle = SDL_atan2(Hero->dr.y - en->data.dr.y, Hero->dr.x - en->data.dr.x);

		float newX = en->data.dr.x + en->data.speed * cos(angle);
		float newY = en->data.dr.y + en->data.speed * sin(angle);

		en->data.dr.x = newX;
		en->data.dr.y = newY;
	}
}

void Mele_Beh(enemy* en)
{
	int ct = SDL_GetTicks();
	float ang = GetAlpha(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr));
	if (en->data.CD <= 0)
	{
		en->data.dr = { en->data.dr.x + en->data.speed * cos(ang) , en->data.dr.y + en->data.speed * sin(ang),en->data.dr.w,en->data.dr.h };
		if (GetDistance(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr)) < 50)
		{
			Hero->HP -= 50;
			en->data.CD = 3000;
		}
	}
	else
	{
		/*if(isinRect({ en->data.dr.x - en->data.speed * cos(ang) , en->data.dr.y - en->data.speed * sin(ang),en->data.dr.w,en->data.dr.h }, {0,0,(float)WIDTH,(float)HEIGHT}))
			en->data.dr = { en->data.dr.x - en->data.speed * cos(ang) , en->data.dr.y - en->data.speed * sin(ang),en->data.dr.w,en->data.dr.h };
	*/
	}
	en->data.CD -= ct - en->data.ShotTime.lt;
	en->data.ShotTime.lt = ct;
}
void Sum_Beh(enemy* en)
{
	int ct = SDL_GetTicks();
	float ang = -GetAlpha(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr));
	if (GetDistance(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr)) < 50)
	{
		en->data.CD = 3000;
		if (isinRect({ en->data.dr.x - en->data.speed * cos(ang) , en->data.dr.y - en->data.speed * sin(ang),en->data.dr.w,en->data.dr.h }, { 0,0,(float)WIDTH,(float)HEIGHT }))
			en->data.dr = { en->data.dr.x + en->data.speed * cos(ang) , en->data.dr.y + en->data.speed * sin(ang),en->data.dr.w,en->data.dr.h };
	}
	if (en->data.CD <= 0)
	{
		CreateNewEnemy(Equeue, rand() % 2 + 3, { en->data.dr.x + rand() % 50 - 25,en->data.dr.y + rand() % 50 - 25 });
		en->data.CD = 5000;
	}
	en->data.CD -= ct - en->data.ShotTime.lt;
	en->data.ShotTime.lt = ct;
}

void Saw_Beh(enemy*& en)
{
	int ct = SDL_GetTicks();
	float nextX = en->data.dr.x + en->data.speed * cos(en->data.angle);
	float nextY = en->data.dr.y + en->data.speed * sin(en->data.angle);


	if (nextX <= 10 || nextX + en->data.dr.w - 10 >= WIDTH)
	{
		nextX <= 10 ?
			en->data.dr.x = 10 :
			en->data.dr.x = WIDTH - 10 - en->data.dr.w;
		en->data.angle = GetAlpha(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr));
	}
	if (nextY <= 10 || nextY + en->data.dr.h + 10 >= HEIGHT)
	{
		en->data.angle = GetAlpha(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr));
		nextY <= 10 ?
			en->data.dr.y = 10 :
			en->data.dr.y = HEIGHT - 10 - en->data.dr.h;
	}

	en->data.dr.x = nextX;
	en->data.dr.y = nextY;
	if (GetDistance(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr)) < 50)
	{
		en->data.HP = 0;
	}
}


void Boom_Beh(enemy* en)
{
	int ct = SDL_GetTicks();
	float ang = GetAlpha(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr));
	en->data.dr = { en->data.dr.x + en->data.speed * cos(ang) , en->data.dr.y + en->data.speed * sin(ang),en->data.dr.w,en->data.dr.h };
	if (GetDistance(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr)) < 40)
	{
		en->data.HP = 0;
		CreateEffect(0, { en->data.dr.x,en->data.dr.y });
		if (GetDistance(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr)))
			Hero->HP -= 40;
		for (enemy* cur = Equeue.head; cur != nullptr; cur = cur->next)
		{
			if (GetDistance(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(cur->data.dr)) < 300)
			{
				cur->data.HP = -1;
				Save.BSS.Score += 100 * (1 + Hero->ItemsInventory[2] / 10.0);
			}
		}
	}
}
#pragma endregion

void processEnemyProjectiles()
{
	static int lt = 0;
	int ct = SDL_GetTicks();
	projectile* cur = EnemyProjectiles.head;
	projectile* tmps;

	if (cur != nullptr)
	{
		do {
			SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
			SDL_RenderCopyExF(ren, cur->data.Textures->PrivateTexture[1], NULL, &cur->data.drect, cur->data.angle, NULL, SDL_FLIP_NONE);

			if (cur->data.livetime <= 0) {
				tmps = cur->next;
				PullProjectile(EnemyProjectiles, cur);
				cur = tmps;
				continue;
			}

			if (SDL_HasIntersectionF(&cur->data.drect,&Hero->dr))
			{
				Hero->HP -= cur->data.damage;
				tmps = cur->next;
				PullProjectile(EnemyProjectiles, cur);
				cur = tmps;
				continue;
			}

			cur->data.drect = { cur->data.drect.x + (float)cos(cur->data.angle), cur->data.drect.y + (float)sin(cur->data.angle), cur->data.drect.w, cur->data.drect.h };
			cur->data.livetime -= ct - lt;

			cur = cur->next;
		} while (cur != nullptr);

		lt = ct;
	}
}

void enemyprocessing(enemy* en)
{
	static int lt = 0;
	int ct = SDL_GetTicks();
	if (en == NULL)
	{
		return;
	}
#pragma region createnemyprojectile


	
#pragma endregion
#pragma region enemymove
	if (en->data.model == 0)
	{
		enemyMoveTowardsPlayer(en);

	}
	else if (en->data.model == 1)
	{
		Mele_Beh(en);
	}
	else if (en->data.model == 2)
	{
		Sum_Beh(en);
	}
	else if (en->data.model == 3)
	{
		Saw_Beh(en);

	}
	else
	{
		Boom_Beh(en);
	}
#pragma endregion
	lt = ct;

	SpleetAnimation(en->data.Textures, en->data.curstage, en->data.dr, Hero->dr.x < en->data.dr.x ? true : false, false, en->data.AnimationTime);
}