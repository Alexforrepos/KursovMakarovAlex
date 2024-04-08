#include <SDL.h>
#include <iostream>


bool isin(SDL_Point p, SDL_Rect R)
{
	if (p.x >= R.x && p.x <= R.x + R.h && p.y > R.y && p.y <= R.y + R.h) return 1;
	return 0;
}