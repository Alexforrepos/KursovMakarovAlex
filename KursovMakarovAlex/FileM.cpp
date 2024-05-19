#include "FileM.h"
#include <iostream>
#include "enemy.h"
#include "Hero.h"

int lc = 0;

void FileEnemyQGet(int &mode)
{
	FILE* F;
	if (fopen_s(&F, "TextInformation/EnemyQueue.txt", "r")) { printf("couldn open Eq-file\n"); exit(-4); };
	fseek(F, lc, SEEK_SET);
	int kolvo,model = 0;
	SDL_FPoint ep;
	fscanf_s(F, "%i\n", &kolvo);
	if (kolvo == 0)
	{
		mode = 0;
		lc = 0;
	}
	for (int k = 0; k < 3; k++) 
	{
		fscanf_s(F, "%d %f %f\n", &model, &ep.x, &ep.y);
		CreateNewEnemy(Equeue, model, ep);
	}
	lc = ftell(F);
	fclose(F);
}

void FileHeroStatsSave(const char filename[50])
{
	FILE* F;
	if (fopen_s(&F, filename, "wt")) { printf("couldn open save-file\n"); exit(-5); };

	fprintf_s(F, "%i\n" ,Hero->HP);
	fprintf_s(F, "%i\n" ,Hero->Money);
	fprintf_s(F, "%i\n" ,Hero->currentWeapon);
	for (int i = 0;i<4;i++)
		fprintf_s(F, "%i\n", Hero->ItemsInventory[i]);
	fclose(F);
}

void FileHeroGet(const char filename[50])
{
	FILE* F;
	if (fopen_s(&F, filename, "rt")) { printf("couldn open save-file\n"); exit(-6); };

	fscanf_s(F, "%i ", &Hero->HP);
	fscanf_s(F, "%i ", &Hero->Money);
	fscanf_s(F, "%i", &Hero->currentWeapon);
	Hero->dr = { 500,500,Hero->dr.w,Hero->dr.h };
	for (int i = 0; i < 4; i++)
		fscanf_s(F, "%i", &Hero->ItemsInventory[i]);
	fclose(F);
}
