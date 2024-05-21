#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "TextProcessing.h"
#include "texturesimport.h"
#include "Menu.h"
#include "Geometry.h"
#include "SDLProcessing.h"
#include "FileM.h"
#include <string.h>

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

SDL_Texture** MenuBackground = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 12);


MenuQuery MainMenuDrow;
MenuQuery MainPlayDrow;

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

#pragma region PlayMenuMode

	MenuItemElementData Save1;
	Save1.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Save-1", { 0,255,0,255 }, 100, 100);
	Save1.SelectTexture = CreateTextTexture(ren, Fonts[0], "Save-1", { 255,0,0,255 }, 100, 100);
	GetTextureDimensions(Save1.SelectTexture, &Save1.Direction.w, &Save1.Direction.h);
	Save1.Direction = { (WIDTH - Save1.Direction.w) / 2,300 - Save1.Direction.h,Save1.Direction.w,Save1.Direction.h };
	Save1.link = 0;
	pushMenuElement(&MainPlayDrow, Save1);


	MenuItemElementData Save2;
	Save2.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Save-2", { 0,255,0,255 }, 100, 100);
	Save2.SelectTexture = CreateTextTexture(ren, Fonts[0], "Save-2", { 255,0,0,255 }, 100, 100);
	GetTextureDimensions(Save2.SelectTexture, &Save2.Direction.w, &Save2.Direction.h);
	Save2.Direction = { (WIDTH - Save2.Direction.w) / 2,500 - Save2.Direction.h,Save2.Direction.w,Save2.Direction.h };
	Save2.link = 1;
	pushMenuElement(&MainPlayDrow, Save2);


	MenuItemElementData Save3;
	Save3.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Save-3", { 0,255,0,255 }, 100, 100);
	Save3.SelectTexture = CreateTextTexture(ren, Fonts[0], "Save-3", { 255,0,0,255 }, 100, 100);
	GetTextureDimensions(Save3.SelectTexture, &Save3.Direction.w, &Save3.Direction.h);
	Save3.Direction = { (WIDTH - Save3.Direction.w) / 2,700 - Save3.Direction.h,Save3.Direction.w,Save3.Direction.h };
	Save3.link = 2;
	pushMenuElement(&MainPlayDrow, Save3);

#pragma endregion


#pragma region InformationRegion
	MenuBackground[1] = CreateUTexture("textures/Infobackgr.jpg");

#pragma endregion
#pragma region MainMenu
#pragma region mainmenuregion
	MenuBackground[0] = CreateUTexture("textures/SaveImage.jpg");
	MenuItemElementData PlayGame;
	PlayGame.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Play", { 120,120,120,255 }, 100, 100);
	PlayGame.SelectTexture = CreateTextTexture(ren, Fonts[0], "Play", { 255,0,0,255 }, 100, 100);
	GetTextureDimensions(PlayGame.SelectTexture, &PlayGame.Direction.w, &PlayGame.Direction.h);
	PlayGame.Direction = { 100,300 - PlayGame.Direction.h,PlayGame.Direction.w,PlayGame.Direction.h };
	PlayGame.link = startitem;
	pushMenuElement(&MainMenuDrow, PlayGame);

	MenuItemElementData Information;
	Information.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Information", { 120,120,120,255 }, 600, 600);
	Information.SelectTexture = CreateTextTexture(ren, Fonts[0], "Information", { 255,0,0,255 }, 600, 600);
	GetTextureDimensions(Information.SelectTexture, &Information.Direction.w, &Information.Direction.h);
	Information.Direction = { 100,500 - Information.Direction.h,Information.Direction.w,Information.Direction.h };
	Information.link = information;
	pushMenuElement(&MainMenuDrow, Information);

	MenuItemElementData Exit;
	Exit.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Exit", { 120,120,120,255 }, 100, 100);
	Exit.SelectTexture = CreateTextTexture(ren, Fonts[0], "Exit", { 255,0,0,255 }, 100, 100);
	GetTextureDimensions(Exit.SelectTexture, &Exit.Direction.w, &Exit.Direction.h);
	Exit.Direction = { 100,700 - Exit.Direction.h,Exit.Direction.w,Exit.Direction.h };
	Exit.link = exitsitem;
	pushMenuElement(&MainMenuDrow, Exit);
#pragma endregion

#pragma endregion
}

void MenuInit()
{
	MainMenuInit();
}

void BoosterRoom()
{

}

void DrowMenu(bool &isrun,int &mod)
{
	SDL_Rect D = { 100, 100, WIDTH - 200, HEIGHT - 200 };
	SDL_Color WHITE = { 255,255,255,255 };
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
						menumod = 2;
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
		break;
	case 1:
		SDL_RenderCopy(ren,MenuBackground[1],NULL,NULL);
		if (kstate[SDL_SCANCODE_ESCAPE]) menumod = 0;
		break;
	case 2:
		SDL_RenderCopy(ren, MenuBackground[0], NULL, NULL);
		SDL_SetRenderDrawColor(ren, WHITE.r/2, WHITE.g / 2, WHITE.b / 2, 255);
		SDL_RenderFillRect(ren, &D);
		for (MenuElemnt* cur = MainPlayDrow.Head; cur != nullptr; cur = cur->Next)
			if (isinPoint(mp, cur->Data.Direction))
			{
				SDL_RenderCopy(ren, cur->Data.SelectTexture, NULL, &cur->Data.Direction);
				if (mstate & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					switch (cur->Data.link)
					{
					case 0:
						FileHeroGet("TextInformation/Save1.txt");
						break;
					case 1:
						FileHeroGet("TextInformation/Save2.txt");
						break;
					case 2:
						FileHeroGet("TextInformation/Save3.txt");
						break;
					default:
						break;
					}
					mod = 1;
				}
			}
			else
				SDL_RenderCopy(ren, cur->Data.NonSelectTexture, NULL, &cur->Data.Direction);
			if (kstate[SDL_SCANCODE_ESCAPE]) menumod = 0;
		break;
	default:
		break;
	}
}