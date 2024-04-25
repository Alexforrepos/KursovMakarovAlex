#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "enemy.h"
#include  "texturesimport.h"
#include "SDLProcessing.h"

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
		TempData.CD = 0;
		TempData.HP = 100;
		TempData.dr = { 200,800,100,100 };
		TempData.model = model;
		break;
	case 1:
		TempData.CD = 0;
		TempData.HP = 200;
		TempData.dr = { 300,800,100,100 };
		TempData.model = model;
		break;
	case 2:
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

void enemyprocessing(enemy* en)
{
	switch (en->data.model)
	{
	case 0:
		SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
		SDL_RenderFillRectF(ren, &en->data.dr);
		break;
	case 1:
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderFillRectF(ren, &en->data.dr);
		break;
	case 2:
		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		SDL_RenderFillRectF(ren, &en->data.dr);
		break;
	default:
		break;
	}
}