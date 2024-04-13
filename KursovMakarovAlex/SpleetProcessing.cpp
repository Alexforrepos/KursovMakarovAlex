#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "SpleetProcessing.h"
#include "texturesimport.h"


void SpleetAnimatic(SDL_Renderer* ren, Spleet—haracteristic& spleet, int FPS)
{
	static int  dt, lasttime;
	int currentime = SDL_GetTicks();
	dt += currentime - lasttime;
	lasttime = currentime;
	if (dt > 1000 / FPS)
	{
		spleet.currenfaze++;
		dt = 0;
		spleet.currenfaze %= spleet.maxfaze;
		SDL_RenderCopy(ren, spleet.texture, &spleet.crect[spleet.currenfaze], &spleet.drect);
	}
}

void SpleetInterruption(Spleet—haracteristic*& Herot, int currentspleet)
{
	static int lastspleet,currentspleet;
	if (lastspleet != currentspleet)
	{
		Herot[lastspleet].currenfaze = 0;
		lastspleet = currentspleet;
	}
}