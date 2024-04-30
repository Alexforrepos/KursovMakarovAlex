#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Geometry.h"
#include "Hero.h"
#include "projectile.h"
#include "enemy.h"
#include  "texturesimport.h"
#include "SDLProcessing.h"


#define STOPPING_RADIUS 500

SDL_Texture* TextureEnemy[4];

EnemyQueue Equeue;

void addEnemy(EnemyQueue& queue, enemydata data)
{
	enemy* newEnemy = new enemy;
	newEnemy->data = data;
	newEnemy->next = nullptr;

	if (queue.tail == nullptr)
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

void removeEnemy(EnemyQueue& queue, enemy* removeEnemy)
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

	delete removeEnemy;
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

const char* EnemyTextures[4]
{
	"",
	"",
	"",
	""
};

void InitEnemyTexture()
{
	for (int i = 0; i < 4; i++)
		TextureEnemy[i] = CreateUTexture(EnemyTextures[i]);
}

void DeinitEnemyTexture()
{
	for (int i = 0; i < 4; i++)
	{
		SDL_DestroyTexture(TextureEnemy[i]);
	}
}


void CreateNewEnemy(EnemyQueue& Queue, int model)
{
	enemydata TempData = { 0 };
	switch (model)
	{
	case 0:
		TempData.speed = 4;
		TempData.CD = 1000;
		TempData.HP = 50;
		TempData.dr = { 200,800,100,100 };
		TempData.model = model;
		break;
	case 1:
		TempData.speed = 4;
		TempData.CD = 0;
		TempData.HP = 100;
		TempData.dr = { 300,800,100,100 };
		TempData.model = model;
		break;
	case 2:
		TempData.speed = 4;
		TempData.CD = 0;
		TempData.HP = 300;
		TempData.dr = { 400,800,100,100 };
		TempData.model = model;
		break;
	default:
		break;
	}
	addEnemy(Queue, TempData);
}

void enemyMoveTowardsPlayer(enemy* en)
{
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

void enemyprocessing(enemy* en)
{
	static int lt = 0;
	int ct = SDL_GetTicks();
	if (en == NULL) 
	{
		return;
	}
#pragma region createnemyprojectile


	if (en->data.CD < 0)
	{
		projectiledata tempdata;
		tempdata.angle = SDL_atan2(Hero->dr.y - en->data.dr.y, Hero->dr.x - en->data.dr.x);
		tempdata.drect = { en->data.dr.x, en->data.dr.y, 20, 20 };
		tempdata.livetime = 3000;
		tempdata.speed = 5;
		tempdata.damage = 10;
		PushProjectile(EnemyProjectiles, tempdata);
		en->data.CD = 1000;
	}
	else
	{
		en->data.CD -= ct - lt;
	}
#pragma endregion


#pragma region enemymove
	if (en->data.model == 0)
	{
		enemyMoveTowardsPlayer(en);
		SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
		SDL_RenderFillRectF(ren, &en->data.dr);
	}
	else if (en->data.model == 1)
	{
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderFillRectF(ren, &en->data.dr);
	}
	else if (en->data.model == 2)
	{
		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		SDL_RenderFillRectF(ren, &en->data.dr);
	}
#pragma endregion

#pragma region enemyprojectileprocessing
	for (projectile* cur = EnemyProjectiles.head; cur != nullptr; cur = cur->next)
	{
		SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
		SDL_RenderFillRectF(ren, &cur->data.drect);
		if (cur->data.livetime <= 0)
		{
			PullProjectile(EnemyProjectiles,cur);
			break;
		}
		if (isinRect(cur->data.drect, Hero->dr))
		{
			Hero->HP -= cur->data.damage;
			PullProjectile(EnemyProjectiles, cur);
			break;
		}
		cur->data.drect = { cur->data.drect.x + (float)cos(cur->data.angle),cur->data.drect.y + (float)sin(cur->data.angle),cur->data.drect.w,cur->data.drect.h };
		cur->data.livetime -= ct - lt;
	}
	lt = ct;
#pragma endregion
}