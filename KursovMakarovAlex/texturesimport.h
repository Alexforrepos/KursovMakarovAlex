#pragma once
#include <SDL.h>

#pragma region enums

enum TypeOfTexture
{
	TTF = 0, IMG = 1
};

enum Range_of_Textures
{
	TextMenuStart = 0, TextMenuEnd = 5,

	BackGroundMenu = 0, InfoMenu = 1, SaveMenu = 2
};

#pragma endregion

struct Texture—haracteristic
{
	SDL_Texture* texture;
	SDL_Rect drect;
	bool isaktive = false;
};

#pragma region externs

extern Texture—haracteristic* BackgrTextures;

extern Texture—haracteristic* TextTextures;

#pragma endregion

SDL_Texture* CreateTextTexture(const char massage[], const char filename[], SDL_Color color, int size_of_font, SDL_Renderer* ren);

void TextureInfo(SDL_Texture* t, int* w, int* h);

SDL_Rect RectOfTexture(SDL_Texture* t, int x, int y);

Texture—haracteristic NewTextureInit(const char filename[], SDL_Renderer* ren);

SDL_Texture* CreateUTexture(const char filename[]);

void MenuTextureInit();

void FreeTextures();

SDL_Texture* GetTextureFromWindow();