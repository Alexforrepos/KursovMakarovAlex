#pragma once
#include <SDL.h>
#include "All_TextureInit.h"


struct Effect_Data_Time
{
	int dt = 0;
	int lt = 0;
	int fps;
};

struct EFFECT_ELEMENT_DATA
{
	LOCAL_MASS_TEXTURE_DESCRIPTOR* Effec_Descriptor = nullptr;
	int CurFaze;
	SDL_FRect DirectionRect;
	Effect_Data_Time TimeData;
	float angle = 0;
	bool ismirored;
	bool mustbepooled;
};

struct EFFECT_ELEMENT
{
	EFFECT_ELEMENT* Next = nullptr, * Prev = nullptr;
	EFFECT_ELEMENT_DATA Data;
};

struct EFFECT_QUEUE
{
	EFFECT_ELEMENT* Head = nullptr, * Tail = nullptr;
};


extern EFFECT_QUEUE* EffQuue;

bool isEmptyEffect(const EFFECT_QUEUE*& queue);

void CreateEffect(int model, SDL_FPoint dir);

EFFECT_QUEUE* CreateEffectQueue();

void PULLEFFECT(EFFECT_QUEUE*& queue);

void EffectRender(EFFECT_ELEMENT* reneffect);