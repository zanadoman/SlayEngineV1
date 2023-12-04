#include "SlayEngineV1.h"

logic slayEvent(slayEngine* Engine)
{
    slayMouseMovement(Engine);
    slayMouseButtons(Engine);
    Engine->Mouse->Wheel = 0;

    while (SDL_PollEvent(&Engine->Display->Event))
    {
        if (Engine->Display->Event.type == SDL_QUIT)
        {
            return false;
        }

        if (Engine->Display->Event.type == SDL_MOUSEMOTION)
        {
            Engine->Mouse->X = Engine->Display->Event.motion.x;
            if (Engine->Mouse->X < 0)
            {
                Engine->Mouse->X = 0;
            }
            else if (Engine->Display->Width < Engine->Mouse->X)
            {
                Engine->Mouse->X = Engine->Display->Width;
            }

            Engine->Mouse->Y = Engine->Display->Event.motion.y;
            if (Engine->Mouse->Y < 0)
            {
                Engine->Mouse->Y = 0;
            }
            else if (Engine->Display->Height < Engine->Mouse->Y)
            {
                Engine->Mouse->Y = Engine->Display->Height;
            }
        }

        if (Engine->Display->Event.type == SDL_MOUSEWHEEL)
        {
            Engine->Mouse->Wheel = Engine->Display->Event.wheel.y;
        }
    }

    return true;
}

uint16 slayUpdateDeltaTime(slayEngine* Engine)
{
    Engine->DeltaTime = SDL_GetTicks() - Engine->PrevTick;
    if (Engine->DeltaTime > 40)
    {
        Engine->DeltaTime = 40;
    }
    Engine->PrevTick = SDL_GetTicks();

    return 0;
}

uint16 slayCapFPS(slayEngine* Engine)
{
    sint64 delay;

    delay = (sint64)round((Engine->PrevTick + 1000.0 / Engine->MaxFPS) - SDL_GetTicks());
    if (delay > 0)
    {
        SDL_Delay(delay);
    }

    return 0;
}

sint64 slayRandom(uint64 Min, uint64 Max, double Seed)
{
    return (sint64)round(SDL_GetTicks() / Seed) % (Max - Min) + Min;
}