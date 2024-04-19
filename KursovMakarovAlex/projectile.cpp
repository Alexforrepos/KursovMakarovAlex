#include "projectile.h"
#include "SDL.h"

ProjectileQueue Projectiles;

void PushProjectile(ProjectileQueue& Queue, projectiledata elementdata)
{
	projectile* element = (projectile*)malloc(sizeof(projectile));
	element->data = elementdata;
	element->next = NULL;

	if (Queue.head == NULL)
	{
		Queue.tail = element;
		Queue.head = element;
	}
	else
	{
		Queue.tail->next = element;
		Queue.tail = element;
	}
}


projectiledata PullProjectileData(ProjectileQueue& queue)
{
	projectiledata data = queue.head->data;

	if (queue.head == queue.tail)
	{
		queue.tail = NULL;
	}

	if (queue.head == queue.tail == NULL)
	{
		return { 0 };
	}

	projectile* TmpElement = queue.head;
	free(TmpElement);

	return data;
}

