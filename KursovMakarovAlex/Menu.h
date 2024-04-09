#pragma once
#include <SDL.h>
#include "Mouse.h"

enum mods
{
	StandartMode = 0,
	InfoMode = 1,
	LoadMode = 2,
	NewGameMode = 3
};


void MenuDrow(Mouse mos, bool& isrun,int mod);