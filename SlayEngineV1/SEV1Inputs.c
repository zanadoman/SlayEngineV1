#include "SlayEngineV1.h"

uint8 slayKey(slayDisplay* Display, uint64 Key)
{
    return SDL_GetKeyboardState(NULL)[Key];
}