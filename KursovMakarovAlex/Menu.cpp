#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "TextProcessing.h"
#include "texturesimport.h"
#include "Menu.h"
#include "Geometry.h"
#include "SDLProcessing.h"

enum linkenum
{
	startitem, information, exitsitem
};

struct MenuItemElementData
{
	SDL_Rect Direction;
	SDL_Texture* SelectTexture;
	SDL_Texture* NonSelectTexture;
	int link;
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

SDL_Texture** MenuBackground = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 4);

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
	MenuBackground[0] = CreateUTexture("textures/SaveImage.jpg");


	MenuItemElementData PlayGame;
	PlayGame.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Play", { 120,120,120,255 }, 100, 100);
	PlayGame.SelectTexture = CreateTextTexture(ren, Fonts[0], "Play", { 255,0,0,255 }, 100, 100);
	GetTextureDimensions(PlayGame.SelectTexture, &PlayGame.Direction.w, &PlayGame.Direction.h);
	PlayGame.Direction = { (WIDTH - PlayGame.Direction.w) / 2,300 - PlayGame.Direction.h,PlayGame.Direction.w,PlayGame.Direction.h };
	PlayGame.link = 0;
	pushMenuElement(&MainMenuDrow, PlayGame);

	MenuItemElementData Information;
	Information.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Information", { 120,120,120,255 }, 600, 600);
	Information.SelectTexture = CreateTextTexture(ren, Fonts[0], "Information", { 255,0,0,255 }, 600, 600);
	GetTextureDimensions(Information.SelectTexture, &Information.Direction.w, &Information.Direction.h);
	Information.Direction = { (WIDTH - Information.Direction.w) / 2,500 - Information.Direction.h,Information.Direction.w,Information.Direction.h };
	PlayGame.link = 1;
	pushMenuElement(&MainMenuDrow, Information);

	MenuItemElementData Exit;
	Exit.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Exit", { 120,120,120,255 }, 100, 100);
	Exit.SelectTexture = CreateTextTexture(ren, Fonts[0], "Exit", { 255,0,0,255 }, 100, 100);
	GetTextureDimensions(Exit.SelectTexture, &Exit.Direction.w, &Exit.Direction.h);
	Exit.Direction = { (WIDTH - Exit.Direction.w) / 2,700 - Exit.Direction.h,Exit.Direction.w,Exit.Direction.h };
	PlayGame.link = 2;
	pushMenuElement(&MainMenuDrow, Exit);

#pragma endregion
}

void MenuInit()
{
	MainMenuInit();
}

void DrowMenu(bool &isrun,int &mod)
{
	static int menumod = 0;
	SDL_Point mp;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	switch (menumod)
	{
	case 0:
		SDL_RenderCopy(ren, MenuBackground[menumod], NULL, NULL);
		for (MenuElemnt* cur = MainMenuDrow.Head; cur != NULL; cur = cur->Next)
		{
			if (isinPoint(mp, cur->Data.Direction))
			{
				SDL_RenderCopy(ren, cur->Data.SelectTexture, NULL, &cur->Data.Direction);
				if (mstate & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					switch (cur->Data.link)
					{
					case startitem:
						mod = 1;
						break;
					case information:
						menumod = 1;
						break;
					case exitsitem:
						isrun = false;
						break;
					default:
						break;
					}
				}
			}
			else
			{
				SDL_RenderCopy(ren, cur->Data.NonSelectTexture, NULL, &cur->Data.Direction);
			}
		}
	case 1:
		//SDL_RenderCopy();
		break;
	default:
		break;
	}
}