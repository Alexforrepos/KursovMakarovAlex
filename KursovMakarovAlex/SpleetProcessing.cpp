#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Hero.h"
#include "SpleetProcessing.h"
#include "texturesimport.h"
#include "SDLProcessing.h"
#include "All_TextureInit.h"
#include "Geometry.h"
void SpleetAnimation(LOCAL_MASS_TEXTURE_DESCRIPTOR* Textures, int& currentstag, SDL_FRect Dr, bool ismirored, bool model, TimeStruct& selftime)
{
	int ct = SDL_GetTicks();


	if (selftime.dt > selftime.selftimefps)
	{

			if (Textures->LocalLen < 5 || (Textures == nullptr && Textures->PrivateTexture[currentstag + 1] == nullptr))
			{
				return;
			}

		if (Textures->LocalLen != 9)
		{

			if (model)
			{
				currentstag = (currentstag % 8) + 1;
			}
			else
			{
				currentstag = (currentstag - 9 + 1) % 8 + 9;
			}
		}
		else
		{
			currentstag = currentstag % 8 + 1;
		}

		Dr = { Dr.x, Dr.y, (float)Textures->SR[currentstag].w, (float)Textures->SR[currentstag].h };
		selftime.lt = ct;
		selftime.dt %= (int)selftime.selftimefps;
	}

	selftime.dt += ct - selftime.lt;

	SDL_FPoint tmppoint = { Dr.x + Dr.w / 2, Dr.y + Dr.h / 2 }; // Центральная точка
	if (currentstag >= 16)
		currentstag = 1;
	SDL_RenderCopyExF(ren, Textures->PrivateTexture[currentstag], NULL, &Dr, NULL, &tmppoint, ismirored ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void DeathAnimation(LOCAL_MASS_TEXTURE_DESCRIPTOR* Textures, SDL_FRect Dr, bool ismirored)
{
	if (Textures->LocalLen < 5)
		return;
	if (Textures == nullptr && Textures->PrivateTexture[0] == nullptr)
		return;
	SDL_RenderCopyExF(ren, Textures->PrivateTexture[0], &Textures->SR[0], &Dr, NULL, NULL,
		ismirored ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}