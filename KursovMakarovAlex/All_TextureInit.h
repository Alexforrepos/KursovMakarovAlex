#pragma once
#include <SDL.h>
#define SIZEOFALLTEXTURE 20
#define MAX_SIZE_OFLOCAL_DESCRIPTOR 40

struct TimeStruct
{
	int dt, ct, lt;
	float selftimefps;
};

// —труктура данных дл€ отдельног сплита
struct LOCAL_MASS_TEXTURE_DESCRIPTOR
{
	SDL_Texture* PrivateTexture[MAX_SIZE_OFLOCAL_DESCRIPTOR];
	SDL_Rect SR[MAX_SIZE_OFLOCAL_DESCRIPTOR];
	int LocalLen = 0, li = 0;
	SDL_Rect MaxRect;
};

// —труктура данных дл€ всех сплитов
struct PUBLIC_TEXTURE_DESCRIPTOR
{
	LOCAL_MASS_TEXTURE_DESCRIPTOR ALL_LOCAL_TEXTURES[SIZEOFALLTEXTURE];
	int PublicLen = 0;
};

extern PUBLIC_TEXTURE_DESCRIPTOR* ALL_TEXTURES;


//дл€ всех возможных значений индексов LOCAL_MASS_TEXTURE_DESCRIPTOR
enum TextureType
{
	Boom_Spleet_Animatin,
	Distant_Spleet_Animation,
	Hero_Spleet_Animation,
	Hero_Spleet_Animation_R,
	Melee_Spleet_Animation,
	Saw_Spleet_Animation,
	Summon_Spleet_Animation,
	Exp_Animation,
	Guns_Textures,
	Portal_Texture,
	Summon_Ring_Texture,
	Battle_Background,
	Menu_Background,
	Shot_Effect,
	Bullet,
	Icons,
	Items_Textures,
	Button_Textures,
	Boosts_Buttons,
	Lazer
};

enum SpleetAnimTexturesBoarders
{
	BeginOfStay = 1,
	EndOfStay = 9,
	BeginOfRun = 9,
	EndOfRun = 18
};

void InitALLTEXTURES();

void FreeTextures();