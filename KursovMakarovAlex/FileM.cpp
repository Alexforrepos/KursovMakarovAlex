#define _CRT_SECURE_NO_WARNINGS
#include "FileM.h"
#include <iostream>
#include "enemy.h"
#include "Hero.h"
#include <string.h>

#include "SDLProcessing.h"




char LastFileSaveUsed[100];
SAVEDATAS Save;

void DATASAVEGET(const char* Domen)
{
	FILE* F = nullptr;
	if (fopen_s(&F, Domen, "rt"))
	{
		printf("err savefile open");

		exit(-1);
	}
	fscanf_s(F, "%i %i", &Save.BSS.is_running, &Save.BSS.Score);
	if (!(Save.BSS.is_running)) 
	{
		Save.BF = { 0 };
		Save.BSS.in_shop = false;
		Save.BSS.is_running = false;
		Save.BSS.Last_Wave = 0;
		Save.BSS.Money = 0;

		Save.HSS.HeroEnemyKill = 0;
		FOR(0, 4) Save.HSS.WeaponEnabled[i] = 0;
		FOR(0, 4) Save.HSS.HeroItem[i] = 0;
		Save.HSS.WeaponEnabled[0] = 1;

		Save.HSS.HeroMoney = 0;
		Save.HSS.HeroLastHp = 1000;

		strcpy(LastFileSaveUsed, Domen);
		fclose(F);
		return;
	}

	fscanf_s(F, "%i", &Save.BSS.Last_Wave);

	int damageBoost, floorIsLava, inv, orbitTraectory, speed;
	fscanf_s(F, "%i %i %i %i %i", &damageBoost, &floorIsLava, &inv, &orbitTraectory, &speed);

	Save.BF.DAMAGEBOOST = (damageBoost != 0);
	Save.BF.FLOOR_IS_LAVA = (floorIsLava != 0);
	Save.BF.INV = (inv != 0);
	Save.BF.ORBIT_TRAECTORY = (orbitTraectory != 0);
	Save.BF.SPEED = (speed != 0);

	fscanf_s(F, "%d %d %d\n", &Save.HSS.HeroMoney, &Save.HSS.HeroLastHp, &Save.HSS.HeroEnemyKill);
	fscanf_s(F, "%i %i %i %i\n", &Save.HSS.HeroItem[0], &Save.HSS.HeroItem[1], &Save.HSS.HeroItem[2], &Save.HSS.HeroItem[3]);

	int num1, num2, num3, num4;
	fscanf_s(F, "%i %i %i %i", &num1, &num2, &num3, &num4);
	Save.HSS.WeaponEnabled[0] = (num1 >= 1) ? true : false;
	Save.HSS.WeaponEnabled[1] = (num2 >= 1) ? true : false;
	Save.HSS.WeaponEnabled[2] = (num3 >= 1) ? true : false;
	Save.HSS.WeaponEnabled[3] = (num4 >= 1) ? true : false;

	strcpy(LastFileSaveUsed, Domen);
	fclose(F);
}

void DataSave(SAVEDATAS Save, const char* Destination)
{

	FILE* F = nullptr;
	if (fopen_s(&F, Destination, "wt"))
	{
		printf("Error opening save file for writing: %s\n", Destination);
		exit(-1);
	}

	fprintf(F, "%s %d", Save.BSS.is_running ? "1" : "0", Save.BSS.Score);
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
		fprintf(F, "%d %d %d %d %d\n",
			Save.BF.DAMAGEBOOST ? 1 : 0,
			Save.BF.FLOOR_IS_LAVA ? 1 : 0,
			Save.BF.INV ? 1 : 0,
			Save.BF.ORBIT_TRAECTORY ? 1 : 0,
			Save.BF.SPEED ? 1 : 0);
		fprintf(F, "%i %i %i\n", Save.HSS.HeroMoney, Save.HSS.HeroLastHp, Save.HSS.HeroEnemyKill);
		fprintf(F, "%i %i %i %i\n", Save.HSS.HeroItem[0], Save.HSS.HeroItem[1], Save.HSS.HeroItem[2], Save.HSS.HeroItem[3]);
		fprintf(F, "%d %d %d %d\n", Save.HSS.WeaponEnabled[0] ? 1 : 0, Save.HSS.WeaponEnabled[1] ? 1 : 0, Save.HSS.WeaponEnabled[2] ? 1 : 0, Save.HSS.WeaponEnabled[3] ? 1 : 0);
	}
	fclose(F);
}

int WavesProcessing(SAVEDATAS& CURSAVE, const char* Domen)
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
		fclose(F);
		return 0;
	}

	fscanf_s(F, "%i", &Enem_Q);
	if (feof(F)) {
		fclose(F);
		return 0;
	}
	for (int i = 0; i < Enem_Q; i++)
	{
		if (feof(F)) {
			fclose(F);
				return 0;
		}
		fscanf_s(F, "%i", &tmpmpdel);
		float x = (float)(rand() % WIDTH);
		float y = (float)(rand() % HEIGHT);
		CreateNewEnemy(Equeue, tmpmpdel, { x,y });
	}
	CURSAVE.BSS.Last_Wave = ftell(F);
	fclose(F);
	return 1;
}