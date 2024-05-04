#include <SDL.h>
#include <iostream>

#include "Geometry.h"


bool isinPoint(SDL_Point p, SDL_Rect R) // проверка на вхождение точкки 
{
	if (p.x >= R.x && p.x <= R.x + R.w && p.y > R.y && p.y <= R.y + R.h) return 1;
	return 0;
}

bool isinRect(SDL_FRect rect1, SDL_FRect rect2) // проверка на вхождение квадратов 
{
	if (rect1.x + rect1.w < rect2.x + rect2.w && rect1.x > rect2.x && rect1.y + rect1.h < rect2.y + rect2.h && rect1.y > rect2.y) 
		return true;

	return false;
}


double GetDistance(SDL_FPoint P1, SDL_FPoint P2)
{
	double distance = sqrt((P1.x - P2.x)* (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y));
	return distance;
}

double GetAlpha(SDL_FPoint P1, SDL_FPoint P2)
{
	return SDL_atan2(P2.y - P1.y, P2.x - P1.x);
}

SDL_FPoint GetCenterPointOfRect(SDL_FRect rect)
{
	float centerX = rect.x + rect.w / 2;
	float centerY = rect.y + rect.h / 2;

	SDL_FPoint center = { centerX, centerY };
	return center;
}

Position GetPointSide(SDL_FPoint Point1, SDL_FPoint Point2) 
{
	float crossProduct = (Point2.x - Point1.x) * (Point1.y);
	if (crossProduct > 0) {
		return RIGHT;
	}
	else if (crossProduct < 0) {
		return LEFT;
	}
	else
		return ON_THE_LINE;
}

SDL_FPoint GetRandomPointOnCircle(SDL_FPoint center, float radius)
{
	float angle = (rand() / float(RAND_MAX)) * 2 * M_PI;
	float x = center.x + radius * cos(angle);
	float y = center.y + radius * sin(angle);

	return { x, y };
}