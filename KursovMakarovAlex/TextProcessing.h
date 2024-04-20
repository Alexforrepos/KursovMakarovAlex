#pragma once
#include <SDL_ttf.h>
#define qFont 12

extern TTF_Font* Fonts[qFont];

bool LoadFonts();

SDL_Texture* CreateTextTexture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, int maxWidth, int maxHeight);

void CloseFonts();