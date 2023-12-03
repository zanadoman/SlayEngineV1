#include "SlayEngineV1.h"

uint8 slayKey(slayEngine* Engine, uint64 Key)
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
    else
    {
        return SDL_GetKeyboardState(NULL)[Key];
    }
}