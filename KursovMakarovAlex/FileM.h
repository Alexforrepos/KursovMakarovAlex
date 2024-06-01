#pragma once
#include <SDL.h>


struct boost_flags
{
	bool INV;
	bool SPEED;
	bool DAMAGEBOOST;
	bool FLOOR_IS_LAVA;
	bool ORBIT_TRAECTORY;
};

struct BASIC_SAVE_STRUCT
{
	bool is_running;
	bool in_shop;
	int Last_Wave;
	int Score;
	int Money;
};

struct SAVEDATAS
{
	BASIC_SAVE_STRUCT BSS; // flag of start
	boost_flags BF; //boost flags
};

extern char LastFileSaveUsed[100];

extern SAVEDATAS Save;

SAVEDATAS DATASAVEGET(const char* Domen);

void DataSave(SAVEDATAS Save,const char* Destination);

int WavesProcessing(SAVEDATAS& CURSAVE, const char* Domen);
