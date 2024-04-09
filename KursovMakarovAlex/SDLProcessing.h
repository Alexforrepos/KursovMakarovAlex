#pragma once
#include <SDL.h>

extern SDL_Renderer* ren;
extern SDL_Window* win;
extern int WIDTH;
extern int HEIGHT;


int Deinit(int error);

void Init();