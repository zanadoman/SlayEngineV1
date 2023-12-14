#include "SlayEngineV1.h"

slayFlipbook* slayNewFlipbook(slayEngine* Engine, uint32 Delay, uint64 Count, char* Paths, ...)
{
    slayFlipbook* result;
    
    va_list PathsArgs;
    char* PathsTemp;

    result = malloc(sizeof(slayFlipbook));
    if (result == NULL)
    {
        printf("ERROR Unable to allocate memory for FLIPBOOK\n");
        exit(1);
    }

    result->Textures = malloc(sizeof(void*) * Count);
    if (result->Textures == NULL)
    {
        printf("ERROR Unable to allocate memory for FLIPBOOK_TEXTURES\n");
        exit(1);
    }
    va_start(PathsArgs, Paths);
    result->Textures[0] = slayLoadTexture(Engine, Paths);
    for (uint64 i = 1; i < Count; i++)
    {
        PathsTemp = va_arg(PathsArgs, char*);
        if (PathsTemp == NULL)
        {
            result->Textures[i] = NULL;
        }
        else
        {
            result->Textures[i] = slayLoadTexture(Engine, PathsTemp);
        }
    }
    va_end(PathsArgs);

    result->Current = -1;
    result->PrevTick = 0;

    result->Delay = Delay;
    result->Count = Count;

    return result;
}

uint8 slayResetFlipbook(slayFlipbook* Flipbook)
{
    Flipbook->Current = -1;

    return 0;
}

slayTexture* slayPlayFlipbook(slayFlipbook* Flipbook)
{
    if (Flipbook->Current != Flipbook->Count - 1 && Flipbook->Delay <= SDL_GetTicks() - Flipbook->PrevTick)
    {
        Flipbook->Current++;
        Flipbook->PrevTick = SDL_GetTicks();
    }

    return Flipbook->Textures[Flipbook->Current];
}

slayTexture* slayLoopFlipbook(slayFlipbook* Flipbook)
{
    if (Flipbook->Delay <= SDL_GetTicks() - Flipbook->PrevTick)
    {
        Flipbook->Current++;
        if (Flipbook->Current == Flipbook->Count)
        {
            Flipbook->Current = 0;
        }
        Flipbook->PrevTick = SDL_GetTicks();
    }

    return Flipbook->Textures[Flipbook->Current];
}

uint8 slayDestroyFlipbook(slayFlipbook* Flipbook)
{
    for (uint64 i = 0; i < Flipbook->Count; i++)
    {
        SDL_DestroyTexture(Flipbook->Textures[i]);
    }
    free(Flipbook->Textures);
    free(Flipbook);

    return 0;
}