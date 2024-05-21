#pragma once
#include <SDL.h>

extern char currentsave[100];
extern char lastfileusedname[100];

void FileEnemyQGet(int &mode);


void FileHeroGet(const char filename[50]);


void FileHeroStatsSave(const char filename[50]);
