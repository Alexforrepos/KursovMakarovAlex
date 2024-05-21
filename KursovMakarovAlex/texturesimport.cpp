#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>	
#include "SDLProcessing.h"
#include "texturesimport.h"


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

void GetTextureDimensions(SDL_Texture* texture, int* width, int* height)
{
	if (texture == nullptr)
	{
		*width = 0;
		*height = 0;
		return;
	}

	int textureWidth = 0;
	int textureHeight = 0;
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

	*width = textureWidth;
	*height = textureHeight;
}

SDL_Texture* CreateUTexture(const char filename[])
{
	SDL_Surface* surface = IMG_Load(filename);
	if (surface == NULL)
	{
		printf("err_img_open %s\n,err %s\n", filename, IMG_GetError);
		system("pause");
		Deinit(-3);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	return  texture;
}

SDL_Texture* CaptureScreenTexture(SDL_Renderer* renderer)
{
	// Получение содержимого окна в виде SDL_Surface
	SDL_Surface* screenSurface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenSurface->pixels, screenSurface->pitch);

	// Создание текстуры из SDL_Surface
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, screenSurface);

	// Освобождение ресурсов, необходимых для SDL_Surface
	SDL_FreeSurface(screenSurface);

	return texture;
}