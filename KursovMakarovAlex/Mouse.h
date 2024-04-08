#pragma once
#include <iostream>


struct Mouse
{
	bool isPKM = false;
	bool isLKM = false;
};

bool isin(SDL_Point p, SDL_Rect R);