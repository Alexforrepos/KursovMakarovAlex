#pragma once
#include "projectile.h"
#include "SDL.h"

struct projectiledata
{
	double angle;
	int speed, livetime = 2500,damage;
	SDL_FRect drect;
};


struct projectile
{
	projectile* prev = NULL;
	projectiledata data = {0};
	projectile* next =NULL;
};


struct ProjectileQueue
{
	projectile* head = NULL;
	projectile* tail = NULL;
};

extern ProjectileQueue Projectiles;

void PushProjectile(ProjectileQueue& queue, projectiledata data);

void PullProjectile(ProjectileQueue& queue, projectile* projectileToRemove);