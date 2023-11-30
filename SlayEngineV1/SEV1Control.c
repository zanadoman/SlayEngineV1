#include "SlayEngineV1.h"

sint64 slayEvent(slayDisplay* Display, slayMouse* Mouse)
{
    uint32 MouseState;

    if (Mouse != NULL)
    {
        slayMouseButtons(Mouse);
        Mouse->Wheel = 0;
    }

    while (SDL_PollEvent(&Display->Event))
    {
        if (Display->Event.type == SDL_QUIT)
        {
            return 0;
        }

        if (Mouse != NULL)
        {
            if (Display->Event.type == SDL_MOUSEMOTION)
            {
                Mouse->X = Display->Event.motion.x;
                if (Mouse->X < 0)
                {
                    Mouse->X = 0;
                }
                else if (Display->Width < Mouse->X)
                {
                    Mouse->X = Display->Width;
                }

                Mouse->Y = Display->Event.motion.y;
                if (Mouse->Y < 0)
                {
                    Mouse->Y = 0;
                }
                else if (Display->Height < Mouse->Y)
                {
                    Mouse->Y = Display->Height;
                }
            }

            if (Display->Event.type == SDL_MOUSEWHEEL)
            {
                Mouse->Wheel = Display->Event.wheel.y;
            }
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