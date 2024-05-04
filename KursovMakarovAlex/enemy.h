#pragma once
#include <SDL.h>

struct enemydata
{

	int HP, CD;
	float speed;
	SDL_FRect dr;
	SDL_Texture* T;
	int model;
	int lt;
	bool ishit;
	float angle;
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

void addEnemy(EnemyQueue& queue, enemydata data);

void enemyprocessing(enemy* en);

void removeEnemy(EnemyQueue& queue, enemy* removeEnemy);

void CreateNewEnemy(EnemyQueue& Queue, int model, SDL_FPoint ep);