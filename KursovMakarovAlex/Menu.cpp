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
#include "All_TextureInit.h"
#include "Hero.h"

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
	bool isactive;
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
MenuQuery MainPlayDrow;
MenuQuery MainSaveBoost;

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

}

void MainMenuInit()
{

#pragma region PlayMenuMode

	MenuItemElementData Save1;
	Save1.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Save-1", { 0,255,0,255 }, 200, 200);
	Save1.SelectTexture = CreateTextTexture(ren, Fonts[0], "Save-1", { 255,0,0,255 }, 200, 200);
	GetTextureDimensions(Save1.SelectTexture, &Save1.Direction.w, &Save1.Direction.h);
	Save1.Direction = { (WIDTH - Save1.Direction.w) / 2,300 - Save1.Direction.h,Save1.Direction.w,Save1.Direction.h };
	Save1.link = 0;
	pushMenuElement(&MainPlayDrow, Save1);


	MenuItemElementData Save2;
	Save2.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Save-2", { 0,255,0,255 }, 200, 200);
	Save2.SelectTexture = CreateTextTexture(ren, Fonts[0], "Save-2", { 255,0,0,255 }, 200, 200);
	GetTextureDimensions(Save2.SelectTexture, &Save2.Direction.w, &Save2.Direction.h);
	Save2.Direction = { (WIDTH - Save2.Direction.w) / 2,500 - Save2.Direction.h,Save2.Direction.w,Save2.Direction.h };
	Save2.link = 1;
	pushMenuElement(&MainPlayDrow, Save2);


	MenuItemElementData Save3;
	Save3.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Save-3", { 0,255,0,255 }, 200, 200);
	Save3.SelectTexture = CreateTextTexture(ren, Fonts[0], "Save-3", { 255,0,0,255 }, 200, 200);
	GetTextureDimensions(Save3.SelectTexture, &Save3.Direction.w, &Save3.Direction.h);
	Save3.Direction = { (WIDTH - Save3.Direction.w) / 2,700 - Save3.Direction.h,Save3.Direction.w,Save3.Direction.h };
	Save3.link = 2;
	pushMenuElement(&MainPlayDrow, Save3);

#pragma endregion


#pragma region BoosterRoom

	MenuItemElementData StartGame;
	StartGame.SelectTexture = CreateTextTexture(ren, Fonts[0], "Start", { 255,255,255,255 }, 400, 200);
	StartGame.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Start", { 255,255,255,255 }, 400, 200);
	GetTextureDimensions(StartGame.SelectTexture, &StartGame.Direction.w, &StartGame.Direction.h);
	StartGame.Direction.x = WIDTH / 2 - StartGame.Direction.w / 2;
	StartGame.Direction.y = HEIGHT / 2;
	StartGame.link = startitem;
	StartGame.isactive = false;

	MenuItemElementData ContinueGame;
	ContinueGame.SelectTexture = CreateTextTexture(ren, Fonts[0], "Continue", { 255,255,255,255 }, 400, 200);
	ContinueGame.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Continue", { 255,255,255,255 }, 400, 200);
	GetTextureDimensions(ContinueGame.SelectTexture, &ContinueGame.Direction.w, &ContinueGame.Direction.h);
	ContinueGame.Direction.x = WIDTH / 2 - ContinueGame.Direction.w / 2;
	ContinueGame.Direction.y = HEIGHT / 2 + 100;
	ContinueGame.isactive = false;
	ContinueGame.link = -1;

	pushMenuElement(&MainSaveBoost, StartGame);
	pushMenuElement(&MainSaveBoost, ContinueGame);


#pragma region Boosts

	MenuItemElementData MEGADAMAGE;
	MEGADAMAGE.SelectTexture = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Boosts_Buttons].PrivateTexture[0];
	MEGADAMAGE.Direction.x = WIDTH / 5 - 100;
	MEGADAMAGE.Direction.y = 200;
	GetTextureDimensions(MEGADAMAGE.SelectTexture, &MEGADAMAGE.Direction.w, &MEGADAMAGE.Direction.h);
	MEGADAMAGE.link = 1;
	MEGADAMAGE.isactive = false;

	MenuItemElementData SPEED;
	SPEED.SelectTexture = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Boosts_Buttons].PrivateTexture[1];
	SPEED.Direction.x = 2 * WIDTH / 5 - 100;
	SPEED.Direction.y = 200;
	GetTextureDimensions(SPEED.SelectTexture, &SPEED.Direction.w, &SPEED.Direction.h);
	SPEED.link = 2;
	SPEED.isactive = false;

	MenuItemElementData FLOOR_IS_LAVA;
	FLOOR_IS_LAVA.SelectTexture = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Boosts_Buttons].PrivateTexture[2];
	FLOOR_IS_LAVA.Direction.x = 3 * WIDTH / 5 - 100;
	FLOOR_IS_LAVA.Direction.y = 200;
	GetTextureDimensions(FLOOR_IS_LAVA.SelectTexture, &FLOOR_IS_LAVA.Direction.w, &FLOOR_IS_LAVA.Direction.h);
	FLOOR_IS_LAVA.link = 3;
	FLOOR_IS_LAVA.isactive = false;

	MenuItemElementData IMMUN;
	IMMUN.SelectTexture = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Boosts_Buttons].PrivateTexture[3];
	IMMUN.Direction.x = 4 * WIDTH / 5 - 100;
	IMMUN.Direction.y = 200;
	GetTextureDimensions(IMMUN.SelectTexture, &IMMUN.Direction.w, &IMMUN.Direction.h);
	IMMUN.link = 4;
	IMMUN.isactive = false;

	MenuItemElementData SPIN;
	SPIN.SelectTexture = ALL_TEXTURES->ALL_LOCAL_TEXTURES[Boosts_Buttons].PrivateTexture[4];
	SPIN.Direction.x = WIDTH / 2;
	SPIN.Direction.y = 400;
	GetTextureDimensions(SPIN.SelectTexture, &SPIN.Direction.w, &SPIN.Direction.h);
	SPIN.link = 5;
	SPIN.isactive = false;

	pushMenuElement(&MainSaveBoost, MEGADAMAGE);
	pushMenuElement(&MainSaveBoost, SPEED);
	pushMenuElement(&MainSaveBoost, FLOOR_IS_LAVA);
	pushMenuElement(&MainSaveBoost, IMMUN);
	pushMenuElement(&MainSaveBoost, SPIN);

#pragma endregion




#pragma endregion
#pragma region MainMenu
#pragma region mainmenuregion

	MenuItemElementData PlayGame;
	PlayGame.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Play", { 120,120,120,255 }, 200, 100);
	PlayGame.SelectTexture = CreateTextTexture(ren, Fonts[0], "Play", { 255,0,0,255 }, 200, 100);
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
	Exit.NonSelectTexture = CreateTextTexture(ren, Fonts[0], "Exit", { 120,120,120,255 }, 200, 100);
	Exit.SelectTexture = CreateTextTexture(ren, Fonts[0], "Exit", { 255,0,0,255 }, 200, 100);
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

void BoosterRoom(int& mod,int menumode)
{
	char tmp[100];
	SDL_Point mp;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	for (MenuElemnt* cur = MainSaveBoost.Head; cur != nullptr; cur = cur->Next)
		if (!isinPoint(mp, cur->Data.Direction))
		{

			if (cur->Data.isactive)
			{
				if (cur->Data.link == -1 && !Save.BSS.is_running)
					continue;
				SDL_RenderCopy(ren, cur->Data.SelectTexture, NULL, &cur->Data.Direction);
				if (cur->Data.link == -1)
					cur->Data.isactive = 0;
				if (cur->Data.link == 0)
					cur->Data.isactive = 0;
			}
			else
			{
				if (cur->Data.link == -1 && !Save.BSS.is_running)
					continue;
				renderTextureWithAlpha(cur->Data.SelectTexture, cur->Data.Direction.x, cur->Data.Direction.y);
			}
		}
		else
		{
			if (cur->Data.link == -1 && !Save.BSS.is_running)
				continue;
			SDL_RenderCopy(ren, cur->Data.SelectTexture, NULL, &cur->Data.Direction);
			if (mstate & SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				switch (cur->Data.link)
				{
				case -1:
					WavesProcessing(Save, "EnemyQueue.txt");
					mod = 1;
					menumode = 0;
					break;
				case 0:

					Hero->HP = 1000;
					Save.BSS.Last_Wave = 0;
					Save.BSS.is_running = 1;
					mod = 1;
					strcpy_s(tmp, "EnemyQueue.txt");
					WavesProcessing(Save, tmp);
					menumode = 0;
					break;
				case 1:
					Save.BF.DAMAGEBOOST = !Save.BF.DAMAGEBOOST;
					break;
				case 2:
					Save.BF.FLOOR_IS_LAVA = !Save.BF.FLOOR_IS_LAVA;
					break;
				case 3:
					Save.BF.SPEED = !Save.BF.SPEED;
					break;
				case 4:
					Save.BF.INV = !Save.BF.INV;
					break;
				case 5:
					Save.BF.ORBIT_TRAECTORY = !Save.BF.ORBIT_TRAECTORY;
					break;
				default:
					break;
				}
				cur->Data.isactive = !cur->Data.isactive;
			}
		}
}

void DrowMenu(bool& isrun, int& mod)
{
	int ct = SDL_GetTicks();
	static int lt = ct;
	char tmp[100];
	SDL_Rect D = { 100, 100, WIDTH - 200, HEIGHT - 200 };
	SDL_Color WHITE = { 255,255,255,255 };
	static int menumod = 0;
	SDL_Point mp;
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	Uint32 mstate = SDL_GetMouseState(&mp.x, &mp.y);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, ALL_TEXTURES->ALL_LOCAL_TEXTURES[Menu_Background].PrivateTexture[0], NULL, NULL);
	if (ALL_TEXTURES->ALL_LOCAL_TEXTURES[Menu_Background].PrivateTexture[0] == nullptr)
		exit(-1);
	switch (menumod)
	{
	case 0:
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
		if (kstate[SDL_SCANCODE_ESCAPE]) menumod = 0;
		break;
	case 2:
		SDL_SetRenderDrawColor(ren, WHITE.r / 2, WHITE.g / 2, WHITE.b / 2, 255);
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
						Save = DATASAVEGET("Save1.txt");
						break;
					case 1:
						Save = DATASAVEGET("Save2.txt");
						break;
					case 2:
						Save = DATASAVEGET("Save3.txt");
						break;
					default:
						break;
					}
					menumod = 3;
				}
			}
			else
				SDL_RenderCopy(ren, cur->Data.NonSelectTexture, NULL, &cur->Data.Direction);
		if (kstate[SDL_SCANCODE_ESCAPE] && ct - lt > 200) {menumod = 0;lt = ct;};
		break;
	case 3:
		if (kstate[SDL_SCANCODE_ESCAPE] && ct - lt > 200) 
		{
			menumod = 2;
			lt = ct;
		}
		BoosterRoom(mod,menumod);
	default:
		break;
	}

}

void DeinitMenu(){DeleteMenuQuery(&MainMenuDrow);DeleteMenuQuery(&MainPlayDrow);DeleteMenuQuery(&MainSaveBoost);}