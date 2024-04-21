#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "enemy.h"


SDL_Texture* TextureEnemy[4];

void addEnemy(enemyQueue& queue, enemydata data)
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

void removeEnemy(enemyQueue& queue, enemy* removeEnemy)
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

void clearEnemies(enemyQueue& queue)
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
    for (int i = 0; i < 4;i++);
}

void DeinitEnemyTexture()
{
    for (int i = 0; i < 4; i++)
    {
        SDL_DestroyTexture(TextureEnemy[i]);
    }
}


void CreateNewEnemy(int model)
{

    switch (model)
    {
    case 0:
        
    default:
        break;
    }
}

void enemyprocessing(enemy en)
{
	switch (en.data.model)
	{
	case 10:
		

	default:
		break;
	}
}