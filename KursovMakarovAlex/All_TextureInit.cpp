#include "All_TextureInit.h"
#include <iostream>


PUBLIC_TEXTURE_DESCRIPTOR* ALL_TEXTURES;

#pragma region DynamicMemory

LOCAL_MASS_TEXTURE_DESCRIPTOR* CreateLocalMassTextureDescriptor(int len)
{
    LOCAL_MASS_TEXTURE_DESCRIPTOR* newDescriptor = (LOCAL_MASS_TEXTURE_DESCRIPTOR*)malloc(len * sizeof(LOCAL_MASS_TEXTURE_DESCRIPTOR));
    if (newDescriptor == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(-1);
    }
    return newDescriptor;
}

// Функция для освобождения памяти, выделенной под LOCAL_MASS_TEXTURE_DESCRIPTOR
static void FreeLocalMassTextureDescriptor(LOCAL_MASS_TEXTURE_DESCRIPTOR* descriptor)
{
    free(descriptor);
}

// Функция для выделения памяти под PUBLIC_TEXTURE_DESCRIPTOR
PUBLIC_TEXTURE_DESCRIPTOR* CreatePublicTextureDescriptor(int len)
{
    PUBLIC_TEXTURE_DESCRIPTOR* newDescriptor = (PUBLIC_TEXTURE_DESCRIPTOR*)malloc(sizeof(PUBLIC_TEXTURE_DESCRIPTOR));
    if (newDescriptor == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(-1);
    }
    newDescriptor->ALL_LOCAL_TEXTURES = CreateLocalMassTextureDescriptor(len);
    newDescriptor->len = len;
    return newDescriptor;
}

// Функция для освобождения памяти, выделенной под PUBLIC_TEXTURE_DESCRIPTOR и связанные с ней структуры
void FreePublicTextureDescriptor(PUBLIC_TEXTURE_DESCRIPTOR* descriptor)
{
    if (descriptor != NULL)
    {
        FreeLocalMassTextureDescriptor(descriptor->ALL_LOCAL_TEXTURES);
        free(descriptor);
    }
}


#pragma region teq
void AddNewLocalTextureRow(SDL_Texture** newTexture, int newLen)
{
    // Увеличиваем размер структуры на 1
    ALL_TEXTURES->ALL_LOCAL_TEXTURES = (LOCAL_MASS_TEXTURE_DESCRIPTOR*)realloc(ALL_TEXTURES->ALL_LOCAL_TEXTURES, (ALL_TEXTURES->len + 1) * sizeof(LOCAL_MASS_TEXTURE_DESCRIPTOR));

    // Проверяем успешность выделения памяти
    if (ALL_TEXTURES->ALL_LOCAL_TEXTURES == NULL)
    {
        printf("Memory re-allocation failed.\n");
        exit(-1);
    }


    // Увеличиваем счетчик длины
    ALL_TEXTURES->len++;
}

void AddNewLocalTextureWithRealloc(SDL_Texture* newTexture, int localIndex)
{
    // Увеличиваем размер массива PrivateTexture на 1
    ALL_TEXTURES->ALL_LOCAL_TEXTURES[localIndex].PrivateTexture = (SDL_Texture**)realloc(ALL_TEXTURES->ALL_LOCAL_TEXTURES[localIndex].PrivateTexture, (ALL_TEXTURES->ALL_LOCAL_TEXTURES[localIndex].LocalLen + 1) * sizeof(SDL_Texture*));

    // Проверяем успешность выделения памяти
    if (ALL_TEXTURES->ALL_LOCAL_TEXTURES[localIndex].PrivateTexture == NULL)
    {
        printf("Memory re-allocation failed.\n");
        exit(-1);
    }

    // Добавляем новую текстуру
    ALL_TEXTURES->ALL_LOCAL_TEXTURES[localIndex].PrivateTexture[ALL_TEXTURES->ALL_LOCAL_TEXTURES[localIndex].LocalLen] = newTexture;

    // Увеличиваем счетчик длины
    ALL_TEXTURES->ALL_LOCAL_TEXTURES[localIndex].LocalLen++;
}
#pragma endregion

#pragma endregion

#pragma region Interface

void AddNewLocalTexture(SDL_Texture** newTexture, int textureIndex, int localLen)
{
    ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].PrivateTexture = newTexture;
    ALL_TEXTURES->ALL_LOCAL_TEXTURES[textureIndex].LocalLen = localLen;
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
    return ALL_TEXTURES->len;
}

void AddNewLocalMassTexture(LOCAL_MASS_TEXTURE_DESCRIPTOR* newLocalTextureDescriptor, int localIndex)
{
    ALL_TEXTURES->ALL_LOCAL_TEXTURES[localIndex] = *newLocalTextureDescriptor;
}

LOCAL_MASS_TEXTURE_DESCRIPTOR* GetLocalDescriptorByIndex(int index)
{
    if (index < ALL_TEXTURES->len && index > -1)
    {
        return &(ALL_TEXTURES->ALL_LOCAL_TEXTURES[index]);
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


}


#pragma endregion
