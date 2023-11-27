#include "SlayEngineV1.h"

//Calculates the delta time for the current frame
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
//Caps the fps to the specified value also takes DeltaTime into account
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
//Generates random numbers from ticks / seed
uint64 slayRandom(uint64 Min, uint64 Max, double Seed)
{
    return (uint64)round(SDL_GetTicks64() / Seed) % (Max - Min) + Min;
}