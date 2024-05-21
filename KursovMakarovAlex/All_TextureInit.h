#pragma once
#include <SDL.h>


struct LOCAL_MASS_TEXTURE_DESCRIPTOR
{
	SDL_Texture** PrivateTexture;
	int LocalLen= 0;
};

struct PUBLIC_TEXTURE_DESCRIPTOR
{
	LOCAL_MASS_TEXTURE_DESCRIPTOR* ALL_LOCAL_TEXTURES;
	int len = 0;
};


extern PUBLIC_TEXTURE_DESCRIPTOR* ALL_TEXTURES;

enum ALL_PRIVATE_TEXTURES_INDEX
{

};

enum TextureType
{
	boom_attack_mob,
	distant,
	Hero,
	melee,
	Saw,
	summon,
	boom,
	guns,
	portal,
	summon_ring,
	battle,
	menu
};