#include "SlayEngineV1.h"

uint8 slayKey(slayDisplay* Display, uint64 Key)
{
    return SDL_GetKeyboardState(NULL)[Key];
}

uint16 slayMouseButtons(slayMouse* Mouse)
{
    uint32 MouseState;

    MouseState = SDL_GetMouseState(NULL, NULL);
    if (MouseState & 1)
    {
        Mouse->LMB = true;
    }
    else
    {
        Mouse->LMB = false;
    }
    if (MouseState & 2)
    {
        Mouse->MMB = true;
    }
    else
    {
        Mouse->MMB = false;
    }
    if (MouseState & 4)
    {
        Mouse->RMB = true;
    }
    else
    {
        Mouse->RMB = false;
    }

    return 0;
}