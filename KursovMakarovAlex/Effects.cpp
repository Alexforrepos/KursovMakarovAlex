#include <SDL.h>
#include "texturesimport.h"
#include <SDL_image.h>
#include "Effects.h"
#include "SDLProcessing.h"

EFFECT_QUEUE* EffQuue;

EFFECT_QUEUE* CreateEffectQueue()
{
    EffQuue = (EFFECT_QUEUE*)malloc(sizeof(EFFECT_QUEUE));
    if (!EffQuue)
        return nullptr;
    EffQuue->Head = nullptr;
    EffQuue->Tail = nullptr;
    return EffQuue;
}

void DeleteEffectQueue(EFFECT_QUEUE* queue)
{
    if (!queue) return;

    EFFECT_ELEMENT* current = queue->Head;
    while (current)
    {
        EFFECT_ELEMENT* next = current->Next;
        // Освобождаем память, выделенную для данных элемента
        if (current->Data.Effec_Descriptor)
        {
            free(current->Data.Effec_Descriptor);
        }
        // Освобождаем память, выделенную для самого элемента
        free(current);
        current = next;
    }

    // Освобождаем память, выделенную для очереди
    free(queue);
}

void PUSHEFFECT(EFFECT_QUEUE*& queue, EFFECT_ELEMENT_DATA data) 
{
    EFFECT_ELEMENT* element = (EFFECT_ELEMENT*)malloc(sizeof(EFFECT_ELEMENT));
    if (!element)
        return;

    element->Data = data;
    element->Next = nullptr;
    element->Prev = queue->Tail;


    if (!queue->Head)
    {
        queue->Head = element;
    }
    if (queue->Tail) 
      {
        queue->Tail->Next = element;
    }
    queue->Tail = element;

    
}

// Функция для удаления элемента из очереди
void PULLEFFECT(EFFECT_QUEUE*& queue)
{
    if (!queue->Head) 
    {
        return; // Очередь пуста
    }

    EFFECT_ELEMENT* oldHead = queue->Head;
    queue->Head = queue->Head->Next;

    if (queue->Head) 
    {
        queue->Head->Prev = nullptr;
    }
    else 
    {
        queue->Tail = nullptr; // Очередь стала пустой
    }

    free(oldHead);
}

void ClearEffect(EFFECT_QUEUE*& EQ)
{
    while (EQ->Tail!=nullptr)
    {
        PULLEFFECT(EQ);
    }
}

// Функция для проверки, пуста ли очередь
bool isEmptyEffect(EFFECT_QUEUE*& queue) 
{
    return queue->Head == nullptr;
}


// 0 - boom effect
void CreateEffect(int model,SDL_FPoint dir)
{
    EFFECT_ELEMENT_DATA  TmpEffectData = { 0 };
    switch (model)
    {
    case 0:
        TmpEffectData.Effec_Descriptor = &ALL_TEXTURES->ALL_LOCAL_TEXTURES[Exp_Animation];
        TmpEffectData.DirectionRect = { dir.x,dir.y,(float)TmpEffectData.Effec_Descriptor->SR[0].w,(float)TmpEffectData.Effec_Descriptor->SR[0].h };
        TmpEffectData.TimeData = { 0,0,20 };
        TmpEffectData.CurFaze = 0;
        TmpEffectData.mustbepooled = false;
        PUSHEFFECT(EffQuue,TmpEffectData);
    default:
        break;
    }
}


void EffectRender(EFFECT_ELEMENT* reneffect)
{
    if (!reneffect)
        return;
    if (!reneffect->Data.Effec_Descriptor)
        return;
  
    int ct = SDL_GetTicks();
    if (ct - reneffect->Data.TimeData.lt > reneffect->Data.TimeData.fps)
    {
        reneffect->Data.CurFaze = (reneffect->Data.CurFaze + 1);
        if (reneffect->Data.CurFaze > reneffect->Data.Effec_Descriptor->LocalLen - 1)
        {
            reneffect->Data.CurFaze = reneffect->Data.Effec_Descriptor->LocalLen - 1;
            reneffect->Data.mustbepooled = true;
        }

        reneffect->Data.TimeData.lt = ct;
        
    }
    reneffect->Data.DirectionRect = { reneffect->Data.DirectionRect.x,reneffect->Data.DirectionRect.y, (float)reneffect->Data.Effec_Descriptor->SR[reneffect->Data.CurFaze].w,(float)reneffect->Data.Effec_Descriptor->SR[reneffect->Data.CurFaze].h };
    
    SDL_RenderCopyExF(ren, reneffect->Data.Effec_Descriptor->PrivateTexture[reneffect->Data.CurFaze],
        &reneffect->Data.Effec_Descriptor->SR[reneffect->Data.CurFaze], &reneffect->Data.DirectionRect,
            reneffect->Data.angle, NULL, reneffect->Data.ismirored ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
