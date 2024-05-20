#pragma once
#include <SDL.h>

enum typeofitem
{
	speedboost,damageboost,quantboost,firerate
};

struct ItemData
{
	SDL_Texture* T;
	typeofitem Type;
	SDL_FRect Dr;
};

struct Item
{
	Item* Next = nullptr;
	ItemData Data = {0};
	Item* Prev = nullptr;
};

struct ItemDeq
{
	Item* Head = nullptr;
	int len = 0;
	Item* Tail = nullptr;
};

extern ItemDeq* IDeq;

#pragma region Interfac

void RemoveItem(ItemDeq*& Deq, Item* item);

bool addItem(ItemDeq*& Deq, ItemData Data);

bool IdeqInit();

void DeinitIDeq();

void ClearItem(ItemDeq*& Deq);

void ItemsFall(SDL_FPoint p);

void ItemGet(Item* i);

void CreateItem(typeofitem model, SDL_FPoint p);

void ItemRender(ItemDeq* Deq);

int ItemSumm();
#pragma endregion
