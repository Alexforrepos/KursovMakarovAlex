#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "TextProcessing.h"
#include "texturesimport.h"
#include "Menu.h"
#include "Geometry.h"
#include "SDLProcessing.h"

struct MenuItemElementData
{
	SDL_Rect Direction;
	SDL_Texture* SelectTexture;
	SDL_Texture* NonSelectTexture;
};

struct MenuElemnt
{
	MenuElemnt* Prev;
	MenuElemnt* Next;
	MenuItemElementData Data;
};

struct MenuQuery
{
	MenuElemnt* Head;
	MenuElemnt* Tail;
};

MenuQuery MainMenuDrow;

void pushMenuElement(MenuQuery* query, MenuItemElementData data)
{
	MenuElemnt* element = (MenuElemnt*)malloc(sizeof(MenuElemnt));
	element->Data = data;
	element->Prev = query->Tail;
	element->Next = NULL;

	if (query->Tail != NULL)
	{
		query->Tail->Next = element;
	}
	else
	{
		query->Head = element;
	}

	query->Tail = element;
}

void RemoveMenuElement(MenuQuery* query, MenuElemnt* elementToRemove)
{
	if (elementToRemove == nullptr)
	{
		return;
	}

	if (elementToRemove->Prev != nullptr)
	{
		elementToRemove->Prev->Next = elementToRemove->Next;
	}
	else
	{
		query->Head = elementToRemove->Next;
	}

	if (elementToRemove->Next != nullptr)
	{
		elementToRemove->Next->Prev = elementToRemove->Prev;
	}
	else
	{
		query->Tail = elementToRemove->Prev;
	}

	free(elementToRemove);
}

void DeleteMenuQuery(MenuQuery* query)
{
	MenuElemnt* current = query->Head;
	while (current != nullptr)
	{
		MenuElemnt* next = current->Next;
		delete current;
		current = next;
	}

	free(query);
}

void MainMenuInit()
{
#pragma region MainMenu

	MenuItemElementData PlayGame;
	PlayGame.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Play", { 120,120,120,255 }, 100, 100);
	PlayGame.SelectTexture = CreateTextTexture(ren, Fonts[0], "Play", { 255,0,0,255 }, 100, 100);
	GetTextureDimensions(PlayGame.SelectTexture, &PlayGame.Direction.w, &PlayGame.Direction.h);
	PlayGame.Direction = { (WIDTH - PlayGame.Direction.w) / 2,300 - PlayGame.Direction.h,PlayGame.Direction.w,PlayGame.Direction.h };
	pushMenuElement(&MainMenuDrow, PlayGame);

	MenuItemElementData Information;
	Information.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Information", { 120,120,120,255 }, 600, 600);
	Information.SelectTexture = CreateTextTexture(ren, Fonts[0], "Information", { 255,0,0,255 }, 300, 300);
	GetTextureDimensions(Information.SelectTexture, &Information.Direction.w, &Information.Direction.h);
	Information.Direction = { (WIDTH - Information.Direction.w) / 2,500 - Information.Direction.h,Information.Direction.w,Information.Direction.h };
	pushMenuElement(&MainMenuDrow, Information);

	MenuItemElementData Exit;
	Exit.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Exit", { 120,120,120,255 }, 100, 100);
	Exit.SelectTexture = CreateTextTexture(ren, Fonts[0], "Exit", { 255,0,0,255 }, 100, 100);
	GetTextureDimensions(Exit.SelectTexture, &Exit.Direction.w, &Exit.Direction.h);
	Exit.Direction = { (WIDTH - Exit.Direction.w) / 2,700 - Exit.Direction.h,Exit.Direction.w,Exit.Direction.h };
	pushMenuElement(&MainMenuDrow, Exit);


#pragma endregion
}

void MenuInit()
{
	MainMenuInit();
}

void DrowMenu()
{
	SDL_Point mp;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);

	for (MenuElemnt* cur = MainMenuDrow.Head; cur != NULL; cur = cur->Next)
	{
		if (isinPoint(mp, cur->Data.Direction))
		{
			SDL_RenderCopy(ren, cur->Data.SelectTexture, NULL, &cur->Data.Direction);
		}
		else
		{
			SDL_RenderCopy(ren, cur->Data.NonSelectTexture, NULL, &cur->Data.Direction);
		}
	}
}