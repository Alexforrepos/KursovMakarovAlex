#pragma once
#include <iostream>
#include <SDL.h>

enum Position
{
	LEFT,
	RIGHT,
	ON_THE_LINE
};

bool isinPoint(SDL_Point p, SDL_Rect R);

bool isinRect(SDL_FRect rect1, SDL_FRect rect2);

double GetAlpha(SDL_FPoint P1, SDL_FPoint P2);

double GetDistance(SDL_FPoint P1, SDL_FPoint P2);

SDL_FPoint GetCenterPointOfRect(SDL_FRect rect);

SDL_FPoint GetRandomPointOnCircle(SDL_FPoint center, float radius);

Position GetPointSide(SDL_FPoint Point1, SDL_FPoint Point2);