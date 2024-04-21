#pragma once
#include <SDL.h>

enum mods
{
	StandartMode = 0,
	InfoMode = 1,
	LoadMode = 2,
	NewGameMode = 3
};

void MenuInit();

void DrowMenu(bool& isrun, int& mod);