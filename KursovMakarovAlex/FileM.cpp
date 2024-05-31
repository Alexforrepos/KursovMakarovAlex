#define _CRT_SECURE_NO_WARNINGS
#include "FileM.h"
#include <iostream>
#include "enemy.h"
#include "Hero.h"
#include <string.h>






char LastFileSaveUsed[100];
SAVEDATAS Save;

SAVEDATAS DATASAVEGET(char Domen[100])
{
	FILE* F = nullptr;
	if (fopen_s(&F, Domen, "rt"))
	{
		printf("err savefile open");

		exit(-1);
	}
	SAVEDATAS LOCAL_SAVEDATA;
	fscanf_s(F, "%i %i", &LOCAL_SAVEDATA.BSS.is_running, &LOCAL_SAVEDATA.BSS.Score);
	if (!(LOCAL_SAVEDATA.BSS.is_running || LOCAL_SAVEDATA.BSS.Score)) // так как иггра не была запущена он возвращает 0 - SAVE + проверка на score 
	{
		LOCAL_SAVEDATA.BSS = { 0,0,0 };
		LOCAL_SAVEDATA.BF = { 0,0,0,0,0 };
		return LOCAL_SAVEDATA;
	}

	fscanf(F, "%i",  &LOCAL_SAVEDATA.BSS.Last_Wave);
	fscanf(F, "%i %i %i %i %i", &LOCAL_SAVEDATA.BF.DAMAGEBOOST, &LOCAL_SAVEDATA.BF.FLOOR_IS_LAVA, &LOCAL_SAVEDATA.BF.INV
		, &LOCAL_SAVEDATA.BF.ORBIT_TRAECTORY, &LOCAL_SAVEDATA.BF.SPEED);
	fscanf_s(F, "%i %i\n", &Hero->Money, &Hero->HP);
	fscanf_s(F, "%i %i %i %i\n", &Hero->ItemsInventory[0], &Hero->ItemsInventory[1], &Hero->ItemsInventory[2], &Hero->ItemsInventory[3]);
	fscanf_s(F, "%i %i %i %i\n", &Hero->W[0].isanable, &Hero->W[1].isanable, &Hero->W[2].isanable, &Hero->W[3].isanable);
	strcpy(LastFileSaveUsed, Domen);
	fclose(F);
	return LOCAL_SAVEDATA;
}

void DataSave(SAVEDATAS Save, char Destination[100])
{

	FILE* F = nullptr;
	if (fopen_s(&F, Destination, "wt"))
	{
		printf("Error opening save file for writing\n");
		exit(-1);
	}

	fprintf(F, "%s %d", Save.BSS.is_running ? "1" : "0",Save.BSS.Score);
	if (!Save.BSS.is_running) // If the game was not running, write default values
	{
		fprintf(F, "\n0 0\n");
		fprintf(F, "0 0 0 0 0\n");
		fprintf(F, "0 1000\n");
		fprintf(F, "0 0 0 0\n");
	}
	else
	{
		fprintf(F, "\n%d\n", Save.BSS.Last_Wave);
		fprintf(F, "%d %d %d %d %d\n", Save.BF.DAMAGEBOOST, Save.BF.FLOOR_IS_LAVA, Save.BF.INV, Save.BF.ORBIT_TRAECTORY, Save.BF.SPEED);
		fprintf(F, "%i %i\n", Hero->Money, Hero->HP);
		fprintf(F, "%i %i %i %i\n", Hero->ItemsInventory[0], Hero->ItemsInventory[1], Hero->ItemsInventory[2], Hero->ItemsInventory[3]);
		fprintf(F, "%i %i %i %i\n", Hero->W[0].isanable, Hero->W[1].isanable, Hero->W[2].isanable, Hero->W[3].isanable);
	}
	fclose(F);
}

int WavesProcessing(SAVEDATAS& CURSAVE, char Domen[100])
{
	int Enem_Q;
	int tmpmpdel;

	FILE* F = nullptr;
	if (fopen_s(&F, Domen, "rt"))
	{
		printf("Error opening save file for writing\n");
		exit(-1);
	}
	if (!CURSAVE.BSS.is_running)
	{
		CURSAVE.BSS.Last_Wave = 0;
		CURSAVE.BSS.is_running = 1;
	}

	fseek(F, CURSAVE.BSS.Last_Wave, SEEK_SET);
	if (feof(F))
	{
		return 0;
	}
	fscanf_s(F, "%i", &Enem_Q);

	for (int i = 0; i < Enem_Q; i++)
	{
		fscanf_s(F, "%i", &tmpmpdel);
		CreateNewEnemy(Equeue, tmpmpdel, { (float)(rand() % 1000 + 100),(float)(rand() % 1000 + 100) });
	}
	CURSAVE.BSS.Last_Wave = ftell(F);
	fclose(F);
	return 1;
}


