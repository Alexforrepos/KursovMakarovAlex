#include <iostream>
#include <SDL.h>
#include "Items.h"
#include "Hero.h"
#include "SDLProcessing.h"

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

errt addItem(ItemDeq*& Deq, ItemData Data)
{
	Item* newItem = (Item*)malloc(sizeof(Item));
	if (newItem == nullptr) {
		printf("CdntCreateNewItem\n");
		return false;
	}
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
		Deq->Tail = item->Prev;
	}

	Deq->len--;
	free(item);
}

void ClearItem(ItemDeq*& Deq)
{
	Item* cur = Deq->Head;
	while (Deq->Head != nullptr)
	{
		RemoveItem(Deq, cur);
	}
}

bool IsFill(ItemDeq* Deq)
{
	return Deq->len>0;
}

#pragma endregion

#pragma region ItemInterface

void ItemRender(ItemDeq* Deq)
{
	Item* cur = Deq->Head;
	while (cur!=nullptr)
	{
		switch (cur->Data.Type)
		{
		case 0:
			SDL_SetRenderDrawColor(ren, 99, 0, 120, 255);
			break;
		case 1:
			SDL_SetRenderDrawColor(ren, 99, 255, 120, 255);
			break;
		case 3:
			SDL_SetRenderDrawColor(ren, 255, 123, 120, 255);
			break;
		case 4:
			SDL_SetRenderDrawColor(ren, 99, 255, 255, 255);
			break;
		default:
			SDL_SetRenderDrawColor(ren, 85, 78, 99, 255);
			break;
		}
		SDL_RenderDrawRectF(ren,&cur->Data.Dr);
		cur = cur->Next;
	}
}

void CreateItem(typeofitem model,SDL_FPoint p)
{
	addItem(IDeq, { nullptr ,model ,{ p.x,p.y,20,20 } }); // добавить текстуру
}

void ItemsFall(SDL_FPoint p)
{
	if (rand() % 100 >= 100-FALLCHANCE && IDeq->len<20) 
	{	
		CreateItem(typeofitem(rand() % 4), p);
	}
}

void ItemGet(Item* i)
{
	Hero->ItemsInventory[i->Data.Type]++;
	RemoveItem(IDeq, i);
}

#pragma endregion