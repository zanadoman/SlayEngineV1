#include "SlayEngineV1.h"

uint8 slayKey(slayDisplay* Display, uint64 Key)
{
    SDL_PollEvent(&Display->Event);
    const uint8 *state = SDL_GetKeyboardState(NULL);

    return state[Key];
}

//NEED TO STORE THE EVENT QUEUE
uint16 slayMouse(slayDisplay* Display, sint32* X, sint32* Y, logic* LMB, logic* MMB, logic* RMB, sint8* Wheel)
{
    while (SDL_PollEvent(&Display->Event))
    {
        if (Display->Event.type == SDL_MOUSEMOTION)
        {
            if (X != NULL)
            {
                *X = Display->Event.motion.x;
                if (*X < 0)
                {
                    *X = 0;
                }
                else if (Display->Width < *X)
                {
                    *X = Display->Width;
                }
            }

            if (Y != NULL)
            {
                *Y = Display->Event.motion.y;
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

        if (Display->Event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (Display->Event.button.button == SDL_BUTTON_LEFT && LMB != NULL)
            {
                *LMB = true;
            }
            else if (LMB != NULL)
            {
                *LMB = false;
            }
            if (Display->Event.button.button == SDL_BUTTON_MIDDLE && MMB != NULL)
            {
                *MMB = true;
            }
            else if (MMB != NULL)
            {
                *MMB = false;
            }
            if (Display->Event.button.button == SDL_BUTTON_RIGHT && RMB != NULL)
            {
                *RMB = true;
            }
            else if (RMB != NULL)
            {
                *RMB = false;
            }
        }

        if (Display->Event.type == SDL_MOUSEWHEEL && Wheel != NULL)
        {
            if (0 < Display->Event.wheel.y)
            {
                *Wheel = 1;
            }
            else if (0 > Display->Event.wheel.y)
            {
                *Wheel = -1;
            }
        }
        else if (Wheel != NULL)
        {
            *Wheel = 0;
        }
    }

    return 0;
}