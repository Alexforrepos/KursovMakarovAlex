#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Hero.h"
#include "SpleetProcessing.h"
#include "texturesimport.h"
#include "SDLProcessing.h"
#include "All_TextureInit.h"
#include "Geometry.h"
void SpleetAnimation(LOCAL_MASS_TEXTURE_DESCRIPTOR* Textures, int& currentstag, SDL_FRect& Dr, bool ismirrored, int model, TimeStruct& selftime)
{
	int ct = SDL_GetTicks();
	model--; // ”меньшаем модель на 1, чтобы она соответствовала индексам массивов

	if (selftime.dt > selftime.selftimefps)
	{
		if (Textures == nullptr || Textures->LocalLen < 5 || Textures->PrivateTexture[currentstag + 1] == nullptr)
		{
			return;
		}

		if (Textures->LocalLen != 9)
		{
			if (model)
			{
				if (currentstag >= 8)
					currentstag = 0;
				if (currentstag < 1)
					currentstag = 0;
			}
			else
			{
				if (currentstag >= 16)
					currentstag = 8;
				if (currentstag < 9)
					currentstag = 8;
			}
			currentstag++;
		}
		else
		{
			currentstag = (currentstag - 1) % 8 + 1; // ÷иклический переход к следующей текстуре в р€ду из 8
		}

		//  омпенсаци€ смещени€ вниз при различии в высоте текстур
		if (Textures->SR[currentstag].h < Textures->SR[currentstag - 1].h)
		{
			Dr.y += (Textures->SR[currentstag - 1].h - Textures->SR[currentstag].h);
		}

		Dr.w = (float)Textures->SR[currentstag].w;
		Dr.h = (float)Textures->SR[currentstag].h;

		SDL_RenderCopyExF(ren, Textures->PrivateTexture[currentstag], NULL, &Dr, NULL, NULL, ismirrored ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
		if (Textures->SR[currentstag].h < Textures->SR[currentstag - 1].h)
			Dr.y -= Textures->SR[currentstag-1].h - Textures->SR[currentstag].h;
		selftime.lt = ct;
		selftime.dt = 0;
	}
	else
	{
		if (Textures->SR[currentstag].h < Textures->SR[currentstag - 1].h)
		{
			Dr.y += (Textures->SR[currentstag - 1].h - Textures->SR[currentstag].h);
		}
		SDL_RenderCopyExF(ren, Textures->PrivateTexture[currentstag], NULL, &Dr, NULL, NULL, ismirrored ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
		if (Textures->SR[currentstag].h < Textures->SR[currentstag - 1].h)
			Dr.y -= Textures->SR[currentstag - 1].h - Textures->SR[currentstag].h;
	}

	selftime.dt += ct - selftime.lt;
}

//void DeathAnimation(LOCAL_MASS_TEXTURE_DESCRIPTOR* Textures, SDL_FRect Dr, bool ismirored)
//{
//	if (Textures->LocalLen < 5)
//		return;
//	if (Textures == nullptr && Textures->PrivateTexture[0] == nullptr)
//		return;
//	SDL_RenderCopyExF(ren, Textures->PrivateTexture[0], &Textures->SR[0], &Dr, NULL, NULL,
//		ismirored ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
//}