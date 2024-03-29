#pragma once
#include <SDL.h>

enum TypeOfTexture
{
	TTF = 0, IMG = 1
};

struct Texture—haracteristic
{
	SDL_Texture* texture;
	SDL_Rect drect;
	int type;
};

SDL_Texture* CreateTextTexture(const char massage[], const char filename[], SDL_Color color, int size_of_font, SDL_Renderer* ren);

void TextureInfo(SDL_Texture* t, int* w, int* h);

SDL_Rect RectOfTexture(SDL_Texture* t);

Texture—haracteristic NewTextureInit(const char filename[], SDL_Renderer* ren);

SDL_Texture* CreateUTexture(const char filename[], SDL_Renderer* ren);

void MemoryReallocForTexture();

void FreeAllTexture();