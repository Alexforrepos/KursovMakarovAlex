#include "projectile.h"
#include "SDL.h"

ProjectileQueue Projectiles;
ProjectileQueue EnemyProjectiles;


void PushProjectile(ProjectileQueue& queue, projectiledata data)
{
    projectile* newProjectile = (projectile*)malloc(sizeof(projectile));
    if (newProjectile == nullptr)
        return;
    data.Textures = &ALL_TEXTURES->ALL_LOCAL_TEXTURES[Bullet];
    data.drect = { data.drect.x,data.drect.y,(float)ALL_TEXTURES->ALL_LOCAL_TEXTURES[Bullet].SR[&queue==&EnemyProjectiles?1:0].w,(float)ALL_TEXTURES->ALL_LOCAL_TEXTURES[Bullet].SR[&queue==&EnemyProjectiles?1:0].h};
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
        if (projectileToRemove->next != nullptr)
        {
            projectileToRemove->prev->next = projectileToRemove->next;
        }
        else
        {
            projectileToRemove->prev->next = nullptr;
        }
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

    free(projectileToRemove);
}
