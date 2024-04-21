#include <SDL.h>
#include <iostream>
#include "Geometry.h"

bool isinPoint(SDL_Point p, SDL_Rect R)
{
	if (p.x >= R.x && p.x <= R.x + R.w && p.y > R.y && p.y <= R.y + R.h) return 1;
	return 0;
}

bool isinRect(SDL_Rect rect1, SDL_Rect rect2)
{
	if (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x && rect1.y < rect2.y + rect2.h && rect1.y + rect1.h > rect2.y)
		return true;

	return false;
}

