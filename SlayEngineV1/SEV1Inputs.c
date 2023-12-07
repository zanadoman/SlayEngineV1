#include "SlayEngineV1.h"

logic slayKey(slayEngine* Engine, uint16 Key)
{
    if (Key == SDL_SCANCODE_RMB)
    {
        return Engine->Mouse->RMB;
    }
    else if (Key == SDL_SCANCODE_MMB)
    {
        return Engine->Mouse->MMB;
    }
    else if (Key == SDL_SCANCODE_LMB)
    {
        return Engine->Mouse->LMB;
    }
    else if (Key == SDL_SCANCODE_WHEELUP)
    {
        return abs(Engine->Mouse->Wheel);
    }
    else if (Key == SDL_SCANCODE_WHEELDOWN)
    {
        return abs(Engine->Mouse->Wheel);
    }
    else
    {
        return SDL_GetKeyboardState(NULL)[Key];
    }
}