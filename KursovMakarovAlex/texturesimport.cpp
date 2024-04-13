#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>	
#include "SDLProcessing.h"
#include "texturesimport.h"

int TextureQuant = 100, TextTexturesQuant = 100;

#pragma region DdynamicMassesInit
Texture—haracteristic* BackgrTextures = (Texture—haracteristic*)calloc(sizeof(Texture—haracteristic) * TextureQuant, NULL);
Texture—haracteristic* TextTextures = (Texture—haracteristic*)calloc(sizeof(Texture—haracteristic) * TextTexturesQuant, NULL);
#pragma endregion


SDL_Texture* CreateTextTexture(const char massage[], const char filename[], SDL_Color color, int size_of_font, SDL_Renderer* ren)
{
	TTF_Font* font = TTF_OpenFont(filename, size_of_font);
	if (font == NULL)
	{
		printf("errn ttf file %s font open\n", filename);
		return NULL;
	}
	SDL_Surface* surf = TTF_RenderText_Blended(font, massage, color);
	if (surf == NULL)
	{
		printf("errn ttf file font open\n");
		TTF_CloseFont(font);
		return NULL;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);
	if (texture == NULL)
	{
		printf("errn ttf file font open\n");
		return NULL;
	}
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

SDL_Texture* GetTextureFromWindow()
{
	SDL_Surface* s = SDL_GetWindowSurface(win);
	if (s == NULL)
	{
		printf("errn couldnt surface get \n");
		system("pause");
		return NULL;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, s);
	if (texture == NULL)
	{
		printf("errn get window surf texture \n");
		return NULL;
	}
	SDL_FreeSurface(s);
	return texture;
}

void TextureInfo(SDL_Texture* t, int* w, int* h)
{
	SDL_QueryTexture(t, NULL, NULL, w, h);
}

SDL_Rect RectOfTexture(SDL_Texture* t, int x, int y)
{
	SDL_Rect r = { x,y,0,0 };
	SDL_QueryTexture(t, NULL, NULL, &r.w, &r.h);
	return r;
}

SDL_Texture* CreateUTexture(const char filename[], SDL_Renderer* ren)
{
	SDL_Surface* surface = IMG_Load(filename);
	if (surface == NULL)
	{
		printf("err_png_open %s\n,err %s\n", filename, IMG_GetError);
		system("pause");
		Deinit(-3);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	return  texture;
}

Texture—haracteristic NewTextureInit(SDL_Renderer* ren, const char filename[], int x, int y)
{
	Texture—haracteristic texture;
	texture.texture = CreateUTexture(filename, ren);
	texture.drect = RectOfTexture(texture.texture, x, y);
	texture.isaktive = true;
	return texture;
} //ÒÓÁ‰‡ÌËÂ Ë ‰Ó·‡‚ÓÂÌËÂ ÌÓ‚ÓÈ ÚÂÍÒÚÛ˚ ‚ Ï‡ÒÒË‚

void FreeTextures()
{

	for (int i = 0; i < TextureQuant; i++)
	{
		if (BackgrTextures[i].isaktive)
			SDL_DestroyTexture(BackgrTextures[i].texture);
	}
	for (int i = 0; i < TextTexturesQuant; i++)
	{
		if (TextTextures[i].isaktive)
			SDL_DestroyTexture(TextTextures[i].texture);
	}
	if (BackgrTextures)
		free(BackgrTextures);
	if (TextTextures)
		free(TextTextures);
}

#pragma region Menu
void MenuTextureInit()
{
#pragma region text
	TextTextures[0].texture = CreateTextTexture("Start Game", "OpenSans-Bold.ttf", { 255,255,255,255 }, 32, ren);
	TextTextures[1].texture = CreateTextTexture("Start Game", "OpenSans-Bold.ttf", { 255,0  ,0  ,255 }, 32, ren);
	TextTextures[0].drect = RectOfTexture(TextTextures[0].texture, 100, 200);
	TextTextures[1].drect = RectOfTexture(TextTextures[1].texture, 100, 200);

	TextTextures[2].texture = CreateTextTexture("Info ", "OpenSans-Bold.ttf", { 255,255,255,255 }, 32, ren);
	TextTextures[3].texture = CreateTextTexture("Info ", "OpenSans-Bold.ttf", { 255,0  ,0  ,255 }, 32, ren);
	TextTextures[2].drect = RectOfTexture(TextTextures[2].texture, 100, 300);
	TextTextures[3].drect = RectOfTexture(TextTextures[3].texture, 100, 300);

	TextTextures[4].texture = CreateTextTexture("Exit ", "OpenSans-Bold.ttf", { 255,255,255,255 }, 32, ren);
	TextTextures[5].texture = CreateTextTexture("Exit ", "OpenSans-Bold.ttf", { 255,0  ,0  ,255 }, 32, ren);
	TextTextures[4].drect = RectOfTexture(TextTextures[4].texture, 100, 400);
	TextTextures[5].drect = RectOfTexture(TextTextures[5].texture, 100, 400);
#pragma endregion
#pragma region MenuBackground
	BackgrTextures[0] = NewTextureInit(ren, "proba.png", NULL, NULL);
	BackgrTextures[1] = NewTextureInit(ren, "Infobackgr.jpg", NULL, NULL);
	BackgrTextures[2] = NewTextureInit(ren, "SaveImage.jpg", NULL, NULL);
#pragma endregion
}
#pragma endregion