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

extern Texture—haracteristic* BackgrTextures;

void GetTextureDimensions(SDL_Texture* texture, int* width, int* height);

SDL_Texture* CreateUTexture(const char filename[]);

SDL_Texture* CaptureScreenTexture(SDL_Renderer* renderer);

SDL_Rect GetTextureAllRect(SDL_Texture* texture, float scale);