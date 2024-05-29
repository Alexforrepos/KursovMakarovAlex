#include <iostream>
#include <SDL.h>
#include "Items.h"
#include "Hero.h"
#include "SDLProcessing.h"
#include "All_TextureInit.h"

#define BULL {}
#define FALLCHANCE 100


ItemDeq* IDeq = nullptr;

typedef bool errt;

#pragma region ItemDeq

bool IdeqInit()
{
	IDeq = (ItemDeq*)malloc(sizeof(ItemDeq));
	if (IDeq == nullptr)
		return false;
	IDeq->Head = nullptr;
	IDeq->Tail = nullptr;
	IDeq->len = 0;
	return true;
}

void DeinitIDeq()
{
	if (IDeq != nullptr)
	{
		ClearItem(IDeq);
		free(IDeq);
	}
}

bool addItem(ItemDeq*& Deq, ItemData Data)
{
	Item* newItem = (Item*)malloc(sizeof(Item));
	if (!newItem)
	{
		printf("Couldn't create new item\n");
		return false;
	}
	if (Deq == nullptr)
		return 0;

	newItem->Data = Data;
	newItem->Next = nullptr;
	newItem->Prev = nullptr;

	if (Deq->Head == nullptr)
	{
		Deq->Head = newItem;
	}
	else
	{
		Deq->Tail->Next = newItem;
		newItem->Prev = Deq->Tail;
	}

	Deq->Tail = newItem;

	Deq->len++;

	return true;
}

void RemoveItem(ItemDeq*& Deq, Item* item)
{
	printf("%i \n", item->Data.Type);

	if (item != nullptr)
	{

		if (item->Prev != nullptr)
		{
			item->Prev->Next = item->Next;
		}
		else
		{
			Deq->Head = item->Next;
		}

		if (item->Next != nullptr)
		{
			item->Next->Prev = item->Prev;
		}
		else
		{
			Deq->Tail = item->Prev; // Обновление Deq->Tail
		}

		Deq->len--;
		free(item);
	}
}

void ClearItem(ItemDeq*& Deq)
{
	Item* cur = Deq->Head,*tmpitem = nullptr;
	while (Deq->Head != nullptr)
	{
		tmpitem = cur->Next;
		RemoveItem(IDeq, cur);
		cur = tmpitem;
	}
	// Освобождение памяти для самой структуры ItemDeq // Установка указателя на NULL
}

bool IsFill(ItemDeq* Deq)
{
	return Deq->len > 0;
}

#pragma endregion

#pragma region ItemInterface

void ItemRender(ItemDeq* Deq)
{
	if (Deq != nullptr)
	{
		Item* cur = Deq->Head;
		while (cur != nullptr)
		{
			
			SDL_RenderCopyF(ren, cur->Data.T,NULL,&cur->Data.Dr);
			cur = cur->Next;
		}
	}
}

void CreateItem(typeofitem model, SDL_FPoint p)
{
	int m = 0;
	if (model == 0)
		m = 2;
	else
		if (model == 1)
			m = 3;
		else
			if (model == 2)
				m = 0;
			else
				m = 3;

	addItem(IDeq, { ALL_TEXTURES->ALL_LOCAL_TEXTURES[Items_Textures].PrivateTexture[m] ,model ,{p.x,p.y,40,40}}); 
}

void ItemsFall(SDL_FPoint p)
{
	if (rand() % 100 >= 100 - FALLCHANCE && IDeq->len < 20)
	{
		CreateItem((typeofitem)(rand() % 4), p);
	}
}

void ItemGet(Item* i)
{
	Hero->ItemsInventory[i->Data.Type]++;
	RemoveItem(IDeq, i);
}

#pragma endregion


int ItemSumm()
{
	int summ = 0;
	for (int i = 0; i < 4; i++)
		summ += Hero->ItemsInventory[i];
	return summ;
}