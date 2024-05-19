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

SDL_Texture* TextureEnemy[5];

void CreateNewEnemy(EnemyQueue& Queue, int model, SDL_FPoint ep)
{
	enemydata TempData = { 0 };
	TempData.lt = 0;
	TempData.angle = NULL;
	TempData.T = nullptr;
	switch (model)
	{
	case 0:
		TempData.speed = 0.4;
		TempData.CD = 1000;
		TempData.HP = 50;
		TempData.dr = { ep.x , ep.y, 50,50 };
		TempData.model = model;
		break;
	case 1:
		TempData.speed = 0.7;
		TempData.CD = 0;
		TempData.HP = 100;
		TempData.dr = { ep.x , ep.y,50,50 };
		TempData.model = model;
		break;
	case 2:
		TempData.speed = 0.1;
		TempData.CD = 0.1;
		TempData.HP = 300;
		TempData.dr = { ep.x , ep.y, 50,50 };
		TempData.model = model;
		break;
	case 3:
		TempData.speed = 3;
		TempData.CD = 0;
		TempData.HP = 100;
		TempData.dr = { ep.x , ep.y, 50,50 };
		TempData.model = model;
		TempData.angle = rand();
		break;
	case 4:
		TempData.speed = 0.2;
		TempData.CD = 0;
		TempData.HP = 200;
		TempData.dr = { ep.x , ep.y, 50,50 };
		TempData.model = model;
		break;
	default:
		break;
	}
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
	printf("%i \n", removeEnemy->data.model);
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
#pragma region Texture
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
#pragma endregion
#pragma region beh
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
void Mele_Beh(enemy* en)
{
	int ct = SDL_GetTicks();
	float ang = GetAlpha(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr));
	if (en->data.CD <= 0)
	{
		en->data.dr = { en->data.dr.x + en->data.speed * cos(ang) , en->data.dr.y + en->data.speed * sin(ang),en->data.dr.w,en->data.dr.h };
		if (GetDistance(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr)) < 50)
			en->data.CD = 3000;
	}
	else
	{
		if(isinRect({ en->data.dr.x - en->data.speed * cos(ang) , en->data.dr.y - en->data.speed * sin(ang),en->data.dr.w,en->data.dr.h }, {0,0,(float)WIDTH,(float)HEIGHT}))
			en->data.dr = { en->data.dr.x - en->data.speed * cos(ang) , en->data.dr.y - en->data.speed * sin(ang),en->data.dr.w,en->data.dr.h };
	}
	en->data.CD -= ct - en->data.lt;
	en->data.lt = ct;
}
void Sum_Beh(enemy* en)
{
	int ct = SDL_GetTicks();
	float ang = -GetAlpha(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr));
	if (GetDistance(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr)) < 50)
	{
		en->data.CD = 3000;
		if(isinRect({ en->data.dr.x - en->data.speed * cos(ang) , en->data.dr.y - en->data.speed * sin(ang),en->data.dr.w,en->data.dr.h }, {0,0,(float)WIDTH,(float)HEIGHT}))
			en->data.dr = { en->data.dr.x + en->data.speed * cos(ang) , en->data.dr.y + en->data.speed * sin(ang),en->data.dr.w,en->data.dr.h };
	}
	if (en->data.CD <= 0)
	{
		CreateNewEnemy(Equeue, rand() % 2 + 3, { en->data.dr.x + rand() % 50 - 25,en->data.dr.y + rand() % 50 - 25 });
		en->data.CD = 5000;
	}
	en->data.CD -= ct - en->data.lt;
	en->data.lt = ct;
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
				en->data.dr.x = WIDTH - 10-en->data.dr.w;
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
	if(GetDistance(GetCenterPointOfRect(en->data.dr), GetCenterPointOfRect(Hero->dr)) < 40)
	{
		en->data.HP = 0;
	}
}
#pragma endregion

void enemyprocessing(enemy* en)
{
	static int lt = 0;
	int ct = SDL_GetTicks();
	if (en == NULL)
	{
		return;
	}
#pragma region createnemyprojectile


	if (en->data.CD < 0 && en->data.model == 0)
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
		Mele_Beh(en);
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderFillRectF(ren, &en->data.dr);
	}
	else if (en->data.model == 2)
	{
		Sum_Beh(en);
		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		SDL_RenderFillRectF(ren, &en->data.dr);
	}
	else if(en->data.model == 3)
	{
		Saw_Beh(en);
		SDL_SetRenderDrawColor(ren, 0, 255, 255, 255);
		SDL_RenderFillRectF(ren, &en->data.dr);
	}
	else
	{
		Boom_Beh(en);
		SDL_SetRenderDrawColor(ren, 255, 0, 255, 255);
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
			PullProjectile(EnemyProjectiles, cur);
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