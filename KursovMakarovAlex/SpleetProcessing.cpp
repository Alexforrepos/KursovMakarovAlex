#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Hero.h"
#include "SpleetProcessing.h"
#include "texturesimport.h"
#include "SDLProcessing.h"


void SpleetAnimaticHero(SDL_Texture* Texture, SDL_Rect R[], SDL_FRect Dr, int mkolvo, int FPS, int CRs)
{
	static int dt = 0;
	static int lt = 0;
	int crt = SDL_GetTicks();
	dt += crt - lt;
	static int CurrentSpleetCR = 0;
	static int lastCr = NULL;
	if (lastCr != CRs)
	{
		CurrentSpleetCR = 0;
		lastCr = CRs;
		dt = 0;
		lt = 0;
	}
	if (CurrentSpleetCR == mkolvo)
		CurrentSpleetCR = 0;
	if (dt > 1000 / FPS)
	{
		dt %= 1000 / FPS;
		CurrentSpleetCR++;
	}
	SDL_RenderCopyF(ren, Texture, &R[CRs * 4 + CurrentSpleetCR], &Dr);
	lt = crt;
}