#include "projectile.h"
#include "SDL.h"

ProjectileQueue Projectiles;

void PushProjectile(ProjectileQueue& queue, projectiledata data)
{
    projectile* newProjectile = new projectile;
    newProjectile->data = data;
    newProjectile->next = nullptr;
    newProjectile->prev = nullptr;

    if (queue.tail == nullptr)
    {
        queue.head = newProjectile;
        queue.tail = newProjectile;
    }
    else
    {
        queue.tail->next = newProjectile;
        newProjectile->prev = queue.tail;
        queue.tail = newProjectile;
    }
}

void PullProjectile(ProjectileQueue& queue, projectile* projectileToRemove)
{
    if (projectileToRemove == nullptr)
    {
        return;
    }

    if (projectileToRemove->prev != nullptr)
    {
        projectileToRemove->prev->next = projectileToRemove->next;
    }
    else
    {
        queue.head = projectileToRemove->next;
    }

    if (projectileToRemove->next != nullptr)
    {
        projectileToRemove->next->prev = projectileToRemove->prev;
    }
    else
    {
        queue.tail = projectileToRemove->prev;
    }

    delete projectileToRemove;
}
