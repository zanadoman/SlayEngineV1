#include "SlayEngineV1.h"

uint8 slayKey(slayDisplay* Display, uint64 Key)
{
    SDL_PollEvent(&Display->Event);
    const uint8 *state = SDL_GetKeyboardState(NULL);

    return state[Key];
}

uint16 slayMousePosition(slayDisplay* Display, sint32* X, sint32* Y)
{
    if (SDL_PollEvent(&Display->Event))
    {
        if (Display->Event.type == SDL_MOUSEMOTION)
        {
            *X =  Display->Event.motion.x;
            *Y =  Display->Event.motion.y;

            if (*X < 0)
            {
                *X = 0;
            }
            else if (Display->Width < *X)
            {
                *X = Display->Width;
            }
            if (*Y < 0)
            {
                *Y = 0;
            }
            else if (Display->Height < *Y)
            {
                *Y = Display->Height;
            }
        }
    }

    return 0;
}