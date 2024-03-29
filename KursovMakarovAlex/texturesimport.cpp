#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>	
#include "SDLProcessing.h"
#include "texturesimport.h"

int TextureQuant = 0;

Texture—haracteristic* Textures = (Texture—haracteristic*)malloc(sizeof(Texture—haracteristic) * TextureQuant);

SDL_Texture* CreateTextTexture(const char massage[], const char filename[], SDL_Color color, int size_of_font, SDL_Renderer* ren)
{
	TTF_Font* font = TTF_OpenFont(filename, size_of_font);
	if (font == NULL)
	{
		return NULL;
	}
	SDL_Surface* surf = TTF_RenderText_Blended(font, massage, color);
	if (surf == NULL)
	{
		TTF_CloseFont(font);
		return NULL;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);
	if (texture == NULL)
	{
		return NULL;
	}
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

void TextureInfo(SDL_Texture* t, int* w, int* h)
{
	SDL_QueryTexture(t, NULL, NULL, w, h);
}

SDL_Rect RectOfTexture(SDL_Texture* t)
{
	int w, h;
	TextureInfo(t, &w, &h);
	SDL_Rect r = { 0,0,w,h };
	return r;
}

void MemoryReallocForTexture()
{
	TextureQuant++;
	Textures = (Texture—haracteristic*)realloc(Textures, TextureQuant);
}

SDL_Texture* CreateUTexture(const char filename[], SDL_Renderer* ren)
{
	SDL_Surface* surface = IMG_Load(filename);
	if (surface == NULL)
	{
		printf("err_png_open %s\n,err#", filename, IMG_GetError);
		system("pause");
		Deinit(-3);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	return  texture;
}

Texture—haracteristic NewTextureInit(const char filename[], SDL_Renderer* ren)
{
	Texture—haracteristic texture;
	MemoryReallocForTexture();
	texture.texture = CreateUTexture(filename, ren);
	texture.drect = RectOfTexture(texture.texture);
	return texture;
} //ÒÓÁ‰‡ÌËÂ Ë ‰Ó·‡‚ÓÂÌËÂ ÌÓ‚ÓÈ ÚÂÍÒÚÛ˚ ‚ Ï‡ÒÒË‚

void FreeAllTexture()
{
	for (int i = 0; i < TextureQuant; i++)
	{
		SDL_DestroyTexture(Textures[i].texture);
	}
	free(Textures);
}