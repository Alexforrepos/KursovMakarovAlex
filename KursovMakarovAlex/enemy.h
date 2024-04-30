#pragma once
#include <SDL.h>

struct enemydata
{

	int HP, CD,speed;
	SDL_FRect dr;
	SDL_Texture* T;
	int model;
	bool ishit;
};

struct enemy
{
	enemy* prev = NULL;
	enemydata data;
	enemy* next = NULL;
};

struct EnemyQueue
{
	enemy* head;
	enemy* tail;
};

extern EnemyQueue Equeue;

void enemyprocessing(enemy* en);

void removeEnemy(EnemyQueue& queue, enemy* removeEnemy);

void CreateNewEnemy(EnemyQueue& Queue, int model);