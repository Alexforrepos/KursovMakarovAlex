#pragma once
#include <SDL.h>
#include "All_TextureInit.h"


struct enemydata
{

	int HP;

	int CD;
	TimeStruct ShotTime;


	TimeStruct AnimationTime;
	LOCAL_MASS_TEXTURE_DESCRIPTOR* Textures;
	int curstage = 0;

	SDL_FRect dr;


	float speed;
	

	bool ishit;
	float angle;
	
	int model;
};

struct enemy
{
	enemy* prev = nullptr;
	enemydata data;
	enemy* next = nullptr;
};

struct EnemyQueue
{
	enemy* head = nullptr;
	enemy* tail = nullptr;
};

extern EnemyQueue Equeue;

void addEnemy(EnemyQueue& queue, enemydata data);

void enemyprocessing(enemy* en);

void RemoveEnemyQ(EnemyQueue& queue, enemy* removeEnemy);

void CreateNewEnemy(EnemyQueue& Queue, int model, SDL_FPoint ep);

bool isQueueEmpty(const EnemyQueue& queue);