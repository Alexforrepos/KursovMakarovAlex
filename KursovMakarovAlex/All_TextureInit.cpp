#include "All_TextureInit.h"
#include <iostream>
#include "texturesimport.h"


PUBLIC_TEXTURE_DESCRIPTOR* ALL_TEXTURES;
#define SCALE 2


#pragma region DynamicMemory


// Функция для выделения памяти под PUBLIC_TEXTURE_DESCRIPTOR
void CreatePublicTextureDescriptor(PUBLIC_TEXTURE_DESCRIPTOR*& publicTextureDescriptor, int publicLen)
{
    publicTextureDescriptor = (PUBLIC_TEXTURE_DESCRIPTOR*)malloc(sizeof(PUBLIC_TEXTURE_DESCRIPTOR));
    if (publicTextureDescriptor == nullptr)
    {
        printf("Memory allocation failed.\n");
        exit(-1);
    }

    for (int i = 0; i < publicLen; i++)
    {
        publicTextureDescriptor->ALL_LOCAL_TEXTURES[i].li = 0;
        publicTextureDescriptor->ALL_LOCAL_TEXTURES[i].LocalLen = 0;
    }

    publicTextureDescriptor->PublicLen = publicLen;
}


void FreePublicTextureDescriptor(PUBLIC_TEXTURE_DESCRIPTOR* descriptor)
{
    if (descriptor != NULL)
    {
        free(descriptor);
    }
}



#pragma endregion

#pragma region Interface

void AddNewLocalTexture(int textureIndex, char filename[100])
{


    if (ALL_TEXTURES != NULL && textureIndex >= 0 && textureIndex <= ALL_TEXTURES->PublicLen)
    {
      
        if (ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].li + 1 <= ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].LocalLen)
        {


            if (ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].li < ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].LocalLen)
            {

              

                ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].PrivateTexture[ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].li] = CreateUTexture(filename);

                if (textureIndex == Guns_Textures)
                    ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].SR[ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].li] =
                    GetTextureAllRect(ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].PrivateTexture[ALL_TEXTURES->
                        ALL_LOCAL_TEXTURES[textureIndex].li], 1.5);
                else
                {
                   
                        ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].SR[ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].li] =
                        GetTextureAllRect(ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].PrivateTexture[ALL_TEXTURES->
                            ALL_LOCAL_TEXTURES[textureIndex].li], SCALE);
                }
          

            }
            ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].li++;
        }
    }
}

SDL_Texture** GetLocalTexture(int textureIndex)
{
    return ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].PrivateTexture;
}

int GetLocalTextureLen(int textureIndex)
{
    return ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].LocalLen;
}

int GetTotalLocalTextures()
{
    return ALL_TEXTURES->PublicLen;
}


LOCAL_MASS_TEXTURE_DESCRIPTOR* GetLocalDescriptorByIndex(int index)
{
    if (index < ALL_TEXTURES->PublicLen && index > -1)
    {
        return (&ALL_TEXTURES->ALL_LOCAL_TEXTURES[index]);
    }
    else
    {
        printf("Invalid index.\n");
        exit(-1);
    }
}


#pragma endregion

#pragma region InitRegion

void InitALLTEXTURES()
{
    CreatePublicTextureDescriptor(ALL_TEXTURES, SIZEOFALLTEXTURE);

    char filenames[SIZEOFALLTEXTURE][40][100] = 
    { 
        { "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_0.png","textures/mobs_spleet/boom_attack_mob/M_Slime_Red_0.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_1.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_2.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_3.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_4.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_5.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_6.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_7.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_8.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_9.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_10.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_11.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_12.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_13.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_14.png", "textures/mobs_spleet/boom_attack_mob/M_Slime_Red_15.png" },
        {"textures/mobs_spleet/distant/death_distant.png","textures/mobs_spleet/distant/knight_12_0.png", "textures/mobs_spleet/distant/knight_12_1.png", "textures/mobs_spleet/distant/knight_12_2.png", "textures/mobs_spleet/distant/knight_12_3.png", "textures/mobs_spleet/distant/knight_12_4.png", "textures/mobs_spleet/distant/knight_12_5.png", "textures/mobs_spleet/distant/knight_12_6.png", "textures/mobs_spleet/distant/knight_12_7.png", "textures/mobs_spleet/distant/knight_12_8.png", "textures/mobs_spleet/distant/knight_12_9.png", "textures/mobs_spleet/distant/knight_12_10.png", "textures/mobs_spleet/distant/knight_12_11.png", "textures/mobs_spleet/distant/knight_12_12.png", "textures/mobs_spleet/distant/knight_12_13.png", "textures/mobs_spleet/distant/knight_12_14.png", "textures/mobs_spleet/distant/knight_12_15.png"},
        {"textures/mobs_spleet/Hero/DeathofHero.png","textures/mobs_spleet/Hero/M_Miner_Ninja_0.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_1.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_2.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_3.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_4.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_5.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_6.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_7.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_8.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_9.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_10.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_11.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_12.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_13.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_14.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_15.png"},
        {"textures/mobs_spleet/Hero/DeathofHero_R.png","textures/mobs_spleet/Hero/M_Miner_Ninja_0_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_1_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_2_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_3_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_4_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_5_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_6_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_7_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_8_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_9_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_10_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_11_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_12_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_13_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_14_R.png", "textures/mobs_spleet/Hero/M_Miner_Ninja_15_R.png"},
        {"textures/mobs_spleet/melee/death_melee.png","textures/mobs_spleet/melee/knight_9_0.png", "textures/mobs_spleet/melee/knight_9_1.png", "textures/mobs_spleet/melee/knight_9_2.png", "textures/mobs_spleet/melee/knight_9_3.png", "textures/mobs_spleet/melee/knight_9_4.png", "textures/mobs_spleet/melee/knight_9_5.png", "textures/mobs_spleet/melee/knight_9_6.png", "textures/mobs_spleet/melee/knight_9_7.png", "textures/mobs_spleet/melee/knight_9_8.png", "textures/mobs_spleet/melee/knight_9_9.png", "textures/mobs_spleet/melee/knight_9_10.png", "textures/mobs_spleet/melee/knight_9_11.png", "textures/mobs_spleet/melee/knight_9_12.png", "textures/mobs_spleet/melee/knight_9_13.png", "textures/mobs_spleet/melee/knight_9_14.png", "textures/mobs_spleet/melee/knight_9_15.png"},
        {"textures/mobs_spleet/Saw/Death_of_Saw.png","textures/mobs_spleet/Saw/002 8+1_0.png", "textures/mobs_spleet/Saw/002 8+1_1.png", "textures/mobs_spleet/Saw/002 8+1_2.png", "textures/mobs_spleet/Saw/002 8+1_3.png", "textures/mobs_spleet/Saw/002 8+1_4.png", "textures/mobs_spleet/Saw/002 8+1_5.png", "textures/mobs_spleet/Saw/002 8+1_6.png", "textures/mobs_spleet/Saw/002 8+1_7.png"},
        {"textures/mobs_spleet/summon/DeathOfSummon.png","textures/mobs_spleet/summon/M_Goblin_Executor_0.png", "textures/mobs_spleet/summon/M_Goblin_Executor_1.png", "textures/mobs_spleet/summon/M_Goblin_Executor_2.png", "textures/mobs_spleet/summon/M_Goblin_Executor_3.png", "textures/mobs_spleet/summon/M_Goblin_Executor_4.png", "textures/mobs_spleet/summon/M_Goblin_Executor_5.png", "textures/mobs_spleet/summon/M_Goblin_Executor_6.png", "textures/mobs_spleet/summon/M_Goblin_Executor_7.png", "textures/mobs_spleet/summon/M_Goblin_Executor_8.png", "textures/mobs_spleet/summon/M_Goblin_Executor_9.png", "textures/mobs_spleet/summon/M_Goblin_Executor_10.png", "textures/mobs_spleet/summon/M_Goblin_Executor_11.png", "textures/mobs_spleet/summon/M_Goblin_Executor_12.png", "textures/mobs_spleet/summon/M_Goblin_Executor_13.png", "textures/mobs_spleet/summon/M_Goblin_Executor_14.png", "textures/mobs_spleet/summon/M_Goblin_Executor_15.png"},
        {"textures/effects/boom/assassin_3_skill_2_effect_1_2.png", "textures/effects/boom/assassin_3_skill_2_effect_1_3.png", "textures/effects/boom/assassin_3_skill_2_effect_1_4.png", "textures/effects/boom/assassin_3_skill_2_effect_1_5.png", "textures/effects/boom/assassin_3_skill_2_effect_1_6.png", "textures/effects/boom/assassin_3_skill_2_effect_1_7.png", "textures/effects/boom/assassin_3_skill_2_effect_1_8.png", "textures/effects/boom/assassin_3_skill_2_effect_1_9.png", "textures/effects/boom/assassin_3_skill_2_effect_1_10.png"},
        {"textures/effects/guns/6 #317292.png","textures/effects/guns/Gun.png","textures/effects/guns/machine.png","textures/effects/guns/shot_gun.png"},
        {"textures/effects/portal/transfer_gate_8.png","textures/effects/portal/transfer_gate_0.png","textures/effects/portal/transfer_gate_1.png","textures/effects/portal/transfer_gate_2.png","textures/effects/portal/transfer_gate_3.png","textures/effects/portal/transfer_gate_4.png","textures/effects/portal/transfer_gate_5.png","textures/effects/portal/transfer_gate_6.png","textures/effects/portal/transfer_gate_7.png"},
        {"textures/effects/summon/robot_king_7_ summonRing.png"},{"textures/backgrounds/battle/background #404995.png" ,"textures/backgrounds/battle/background #405557.png","textures/backgrounds/battle/background #406019.png","textures/backgrounds/battle/background_2 #406266.png"},
        {"textures/backgrounds/menu/biaoti 01 #343428.png","textures/backgrounds/menu/OUTMENU.png"},
        {"textures/effects/Shot_effects/ShotEffecct.png"},
        {"textures/effects/bullet_effect/Bullet.png","textures/effects/bullet_effect/EnemyBulet.png"},
        {"textures/icons/health.png"},
        {"textures/icons/Items/part_atkspd2multicount.png","textures/icons/Items/part_crit_rate.png","textures/icons/Items/part_fragment_move_speed #325249.png","textures/icons/Items/part_melee_range.png" },
        {"textures/effects/button/healingbox.png","textures/effects/button/mall_button_1 #476568.png"},
        {"textures/icons/boosts/ATKS.png","textures/icons/boosts/level_buff_fire_breath.png","textures/icons/boosts/SPEED.png","textures/icons/boosts/level_buff_TempImmuneFire #365502.png","textures/icons/boosts/ui_buff_2174 #373039.png"},
        {"textures/effects/guns/RedSq_S.png"}
    };

    int lengths[SIZEOFALLTEXTURE] = { 17,17,17,17,17,9,17,9,4,9,1,4,2,1,2,1,4,2,5,1};

    for(int i = 0; i < SIZEOFALLTEXTURE; i++)
    {
        ALL_TEXTURES->ALL_LOCAL_TEXTURES[i].LocalLen = lengths[i];
        ALL_TEXTURES->ALL_LOCAL_TEXTURES[i].MaxRect = { 0,0,0,0 };
        for (int j = 0; j < lengths[i]; j++)
        {
            AddNewLocalTexture(i, filenames[i][j]);
        }
    }
}

void FreeTextures()
{
    for (int i = 0; i < ALL_TEXTURES->PublicLen; i++)
    {
        for (int j = 0; j < ALL_TEXTURES->ALL_LOCAL_TEXTURES[i].LocalLen; j++)
        {
            SDL_DestroyTexture(ALL_TEXTURES->ALL_LOCAL_TEXTURES[i].PrivateTexture[j]);
        }
    }
    FreePublicTextureDescriptor(ALL_TEXTURES);
    ALL_TEXTURES = NULL;
}

#pragma endregion
