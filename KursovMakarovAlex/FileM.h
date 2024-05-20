#pragma once
#include <SDL.h>

extern char currentsave[26];

void FileEnemyQGet(int &mode);


void FileHeroGet(const char filename[50]);


void FileHeroStatsSave(const char filename[50]);