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
};

struct SAVEDATAS
{
	BASIC_SAVE_STRUCT BSS; // flag of start
	boost_flags BF; //boost flags
};


extern char LastFileSaveUsed[100];

extern SAVEDATAS Save;

SAVEDATAS DATASAVEGET(char Domen[100]);

void DataSave(SAVEDATAS Save, char Destination[100]);

int WavesProcessing(SAVEDATAS& CURSAVE, char Domen[100]);
