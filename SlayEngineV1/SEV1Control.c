#include "SlayEngineV1.h"

sint64 slayEvent(slayDisplay* Display)
{
    while (SDL_PollEvent(&Display->Event) != 0)
    {
        switch (Display->Event.type)
        {
            case SDL_QUIT:
                SDL_Quit();
                TTF_Quit();
                SDL_CloseAudio();
                return 0;
        }
    }

    return 1;
}

uint64 slayDeltaTime(uint64* DisplayPrevTick)
{
    uint64 DeltaTime;
    
    DeltaTime = SDL_GetTicks() - *DisplayPrevTick;
    if (DeltaTime > 40)
    {
        DeltaTime = 40;
    }
    *DisplayPrevTick = SDL_GetTicks();

    return DeltaTime;
}

uint16 slayFPS(uint64 FPS, uint64 DisplayPrevTick)
{
    sint64 delay;

    delay = (sint64)round((DisplayPrevTick + 1000.0 / FPS) - SDL_GetTicks());
    if (delay > 0)
    {
        SDL_Delay(delay);
    }

    return 0;
}

uint64 slayRandom(uint64 Min, uint64 Max, double Seed)
{
    return (uint64)round(SDL_GetTicks64() / Seed) % (Max - Min) + Min;
}