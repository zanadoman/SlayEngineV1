#include "SlayEngineV1.h"

slayFlipbook* slayNewFlipbook(slayEngine* Engine, uint64 Delay, uint64 Count, char* Paths, ...)
{
    slayFlipbook* result;
    
    va_list PathsArgs;

    result = malloc(sizeof(slayFlipbook));

    result->Textures = malloc(sizeof(void*) * Count);
    va_start(PathsArgs, Paths);
    result->Textures[0] = slayLoadTexture(Engine, Paths);
    for (uint64 i = 1; i < Count; i++)
    {
        result->Textures[i] = slayLoadTexture(Engine, va_arg(PathsArgs, char*));
    }
    va_end(PathsArgs);

    result->Current = -1;
    result->PrevTick = 0;

    result->Delay = Delay;
    result->Count = Count;

    return result;
}

slayTexture* slayTurnFlipbook(slayEngine* Engine, slayFlipbook* Flipbook)
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

uint16 slayPurgeFlipbook(slayFlipbook* Flipbook)
{
    for (uint64 i = 0; i < Flipbook->Count; i++)
    {
        SDL_DestroyTexture(Flipbook->Textures[i]);
    }
    free(Flipbook->Textures);
    free(Flipbook);

    return 0;
}