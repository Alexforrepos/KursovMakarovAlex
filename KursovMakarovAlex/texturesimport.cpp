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
		printf("errn get window surf texture\n");
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
		exit(-1);
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	if (texture == nullptr) 
	{ 
		printf("err texture");
		exit(-1); 
	}
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

SDL_Rect GetTextureAllRect(SDL_Texture* texture,float scale)
{
	int width=-1,height=-1;
	GetTextureDimensions(texture, &width, &height);
	return { 0,0,(int)(width * scale) ,(int)(height*scale) };
}

void renderTextureWithAlpha(SDL_Texture* texture, int x, int y)
{
	// Устанавливаем прозрачность текстуры
	SDL_SetTextureAlphaMod(texture, 128); // Здесь 128 определяет прозрачность текстуры (от 0 до 255)

	// Получаем ширину и высоту текстуры
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

	// Создаем прямоугольник для позиционирования текстуры
	SDL_Rect dstRect = { x, y, texW, texH };

	// Отрисовываем текстуру
	SDL_RenderCopy(ren, texture, NULL, &dstRect);

	// Сбрасываем уровень прозрачности до значения по умолчанию (255 - непрозрачный)
	SDL_SetTextureAlphaMod(texture, 255);
}