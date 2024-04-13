#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "texturesimport.h"
#include "SpleetProcessing.h"
#include "SDLProcessing.h"
#include "Mouse.h"
#include "gamemode.h"
#include "Hero.h"

enum dirrectionsofhero
{
	LeftHero, RightHero, DownHero, UpHero, StayHero
};

void Gamemode(int& mode)
{
	const Uint8* kstate = SDL_GetKeyboardState(NULL);
	int currentDirrection;
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);
	if (kstate[SDL_SCANCODE_D] && !(kstate[SDL_SCANCODE_A]))
		currentDirrection = RightHero;
	if (kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]))
		currentDirrection = LeftHero;
	if (kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]))
		currentDirrection = UpHero;
	if (kstate[SDL_SCANCODE_S] && !(kstate[SDL_SCANCODE_D]))
		currentDirrection = DownHero;
	if (!kstate[SDL_SCANCODE_W] && !(kstate[SDL_SCANCODE_S]) && !kstate[SDL_SCANCODE_A] && !(kstate[SDL_SCANCODE_D]))
		currentDirrection = StayHero;
	switch (currentDirrection)
	{
	case RightHero:

		break;
	case LeftHero:


		break;
	case DownHero:


		break;
	case UpHero:


		break;
	case StayHero:


		break;
	}
}