#pragma once
#include "projectile.h"
#include "SDL.h"

struct projectiledata
{
	double angle;
	int speed, livetime = 2500,damage;
	SDL_Rect drect;
};

struct projectile
{
	projectiledata data;
	projectile* next =NULL;
};


struct ProjectileQueue
{
	projectile* head = NULL;
	projectile* tail = NULL;
};

extern ProjectileQueue Projectiles;

void PushProjectile(ProjectileQueue& Queue, projectiledata elementdata);

projectiledata PullProjectileData(ProjectileQueue& queue);