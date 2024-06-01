#include <SDL.h>

#include "SpleetProcessing.h"
#include "All_TextureInit.h"
#include "Hero.h"
#include "gamemode.h"
#include "Items.h"
#include "SDLProcessing.h"
#include "texturesimport.h"
#include "Geometry.h"
#include "FileM.h"
#include <string.h>


void Button_Ren(int &mode)
{
	char tmps[100];

	char tmp[100] = "EnemyQueue.txt";
	bool flagofAllW = false;
	static SDL_FRect ItemRect = { 300,300,50,50 };
	static SDL_FRect HealtRect = { WIDTH - 300,300,50,50 };
	static SDL_Rect PortalRectT = GetTextureAllRect(ALL_TEXTURES->ALL_LOCAL_TEXTURES[Portal_Texture].PrivateTexture[0], 2);
	static SDL_FRect PortalRect = { WIDTH / 2,300,(float)PortalRectT.w,(float)PortalRectT.h };
	static TimeStruct Portal_Time = { 0,0,0,500 };
	static bool isboughtItem = false;
	static bool isboughtHealth = false;
	static int phazeofportal = 0;
	SpleetAnimation(&ALL_TEXTURES->ALL_LOCAL_TEXTURES[Portal_Texture], phazeofportal, PortalRect, false, false, Portal_Time);


	if (!isboughtHealth)
		SDL_RenderCopyF(ren, ALL_TEXTURES->ALL_LOCAL_TEXTURES[Button_Textures].PrivateTexture[0], NULL, &HealtRect);
	if (!isboughtItem)
		SDL_RenderCopyF(ren, ALL_TEXTURES->ALL_LOCAL_TEXTURES[Button_Textures].PrivateTexture[1], NULL, &ItemRect);

	if (GetDistance(GetCenterPointOfRect(Hero->dr), GetCenterPointOfRect(ItemRect)) < 50 && !isboughtItem && Hero->Money > 200 - Hero->ItemsInventory[2] * 10 )
	{
		isboughtItem = !isboughtItem;
		for (int i = 0; i < 4; i++)
		{
			if (flagofAllW && i == 4 && Hero->W[4].isanable)
			{
				Save.BSS.Score += 1000;
				break;
			}
			if (!Hero->W[i].isanable)
			{
				Hero->W[i].isanable = !Hero->W[i].isanable;
				break;
			}
		}
	}
	if (GetDistance(GetCenterPointOfRect(Hero->dr), GetCenterPointOfRect(HealtRect)) < 50 && !isboughtHealth && Hero->Money > 200)
	{
		isboughtHealth = !isboughtHealth;
		Hero->HP += 200;
	}

	if (GetDistance(GetCenterPointOfRect(Hero->dr), GetCenterPointOfRect(PortalRect)) < 50)
	{
		isboughtItem = false;
		isboughtHealth = false;
		phazeofportal = 0;
		mode = 0;
	}
}

void Shopmode(int& mode)
{
	static int ismode = 0;
	SDL_SetRenderDrawColor(ren, 120, 120, 120, 255);
	SDL_RenderClear(ren);
	HP_RENDER();
	HeroMove();
	Button_Ren(mode);
	if (!ismode && mode!=0)
	{
		Hero->dr = { 0, 0, Hero->dr.w, Hero->dr.h };
		ismode = 1;
	}
}