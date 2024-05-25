#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "TextProcessing.h"


const char* fontNames[12] = 
{
    "fonts/zpix #779.ttf",
};

TTF_Font* Fonts[qFont];

bool LoadFonts()
{
    for (int i = 0; i < qFont; i++)
    {
        Fonts[i] = TTF_OpenFont(fontNames[i], 40);
        if (!Fonts[i])
        {
            SDL_Log("Failed to load font %s! SDL_ttf Error: %s\n", fontNames[i], TTF_GetError());
            return false;
        }
    }
    return true;
}

void CloseFonts()
{
    for (int i = 0; i < qFont; ++i)
    {
        if (Fonts[i])
        {
            TTF_CloseFont(Fonts[i]);
            Fonts[i] = nullptr;
        }
    }
}


SDL_Texture* CreateTextTexture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color textColor, int maxWidth, int maxHeight) // создание текста с настраевыми границвми
{
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text, textColor, maxWidth);
    if (!textSurface)
    {
        printf("Unable to rendertext surface SDL_ttf Error: %s\n", TTF_GetError());
        return NULL;
    }

    if (textSurface->w > maxWidth || textSurface->h > maxHeight)
    {
        SDL_Surface* scaledSurface = SDL_CreateRGBSurfaceWithFormat(0, maxWidth, maxHeight, textSurface->format->BitsPerPixel, textSurface->format->format);
        if (!scaledSurface)
        {
            printf("Unable to create scaled surface SDL Error: %s\n", SDL_GetError());
            SDL_FreeSurface(textSurface);
            return nullptr;
        }

        SDL_Rect srcRect = { 0, 0, textSurface->w, textSurface->h };
        SDL_Rect destRect = { 0, 0, maxWidth, maxHeight };
        SDL_BlitScaled(textSurface, &srcRect, scaledSurface, &destRect);

        SDL_FreeSurface(textSurface);
        textSurface = scaledSurface;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(textSurface);

    return textTexture;
}


