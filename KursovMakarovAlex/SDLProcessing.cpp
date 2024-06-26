#include <iostream>
#include "SDLProcessing.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Window* win;
SDL_Renderer* ren;
int WIDTH = 1920;
int HEIGHT = 1080;;

int Deinit(int error)
{
	if (win)
	{
		SDL_DestroyWindow(win);
	}
	if (ren)
	{
		SDL_DestroyRenderer(ren);
	}
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	return error;
}

void Init()
{
	int r;
	win = SDL_CreateWindow("Wave Defence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE );
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("err init %s\n", SDL_GetError());
		Deinit(-2);
	}
	if (!win)
	{
		printf("err win %s\n", SDL_GetError());
		Deinit(-2);
	}
	if (!ren)
	{
		printf("err ren %s\n", SDL_GetError());
		Deinit(-2);;
	}
	if ((r = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) == 0)
	{
		printf("err init_img %s\n", IMG_GetError());
		Deinit(-3);
	}
	if (r & IMG_INIT_PNG)
		printf("png_sucs_init\n");
	else
		printf("png_err_init\n");
	
	if (r & IMG_INIT_JPG) 
		printf("jpg_sucs_init\n"); 
	else 
		printf("jpg_err_init\n");

	if (TTF_Init())
	{
		printf("err ttf %s\n", TTF_GetError());
		Deinit(-4);
	}
}