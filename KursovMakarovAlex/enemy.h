#pragma once
#include <SDL.h>

struct enemydata
{
	int HP, CD;
	SDL_Texture* T;
	int model;
};


struct enemy
{
	enemy* prev = NULL;
	enemydata data;
	enemy* next = NULL;
};

struct enemyQueue
{
	enemy* head;
	enemy* tail;
};