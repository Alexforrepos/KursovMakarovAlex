#pragma once
#include <SDL.h>
#include "All_TextureInit.h"

void SpleetAnimation(LOCAL_MASS_TEXTURE_DESCRIPTOR* Textures, int& currentstag, SDL_FRect Dr, bool ismirored, bool model, TimeStruct& selftime);

void DeathAnimation(LOCAL_MASS_TEXTURE_DESCRIPTOR* Textures, SDL_FRect Dr, bool ismirored);