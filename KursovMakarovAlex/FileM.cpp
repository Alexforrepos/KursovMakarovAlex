#include "FileM.h"
#include <iostream>
#include "enemy.h"
#include "Hero.h"

int lc = 0;

void FileEnemyQGet(int &mode)
{
	FILE* F;
	if (fopen_s(&F, "EnemyQueue.txt", "r")) { printf("couldn open Eq-file\n"); exit(-5); };
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

void FileHeroStatsSave()
{
	FILE* F;
	if (fopen_s(&F, "EnemyQueue.txt", "wt")) { printf("couldn open Eq-file\n"); exit(-5); };

	fprintf_s(F, "%i " ,Hero->HP);
	fprintf_s(F, "%i " ,Hero->Money);
	fprintf_s(F, "%i\n" ,Hero->currentWeapon);
	for (int i = 0;i<4;i++)
		fprintf_s(F, "%i\n", Hero->ItemsInventory[i]);
}

void FileHeroGet()
{
	FILE* F;
	if (fopen_s(&F, "EnemyQueue.txt", "rt")) { printf("couldn open Eq-file\n"); exit(-5); };

	fscanf_s(F, "%i ", &Hero->HP);
	fscanf_s(F, "%i ", &Hero->Money);
	fscanf_s(F, "%i\n", &Hero->currentWeapon);
	for (int i = 0; i < 4; i++)
		fscanf_s(F, "%i\n", &Hero->ItemsInventory[i]);

}

