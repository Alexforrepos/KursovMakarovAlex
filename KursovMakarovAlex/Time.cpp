#include <iostream>
#include "Time.h"
#include <SDL.h>

int dt = 0, lt = 0;

void DT()
{
	int ct = SDL_GetTicks();
	dt += lt - ct;
}