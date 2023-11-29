#include "SlayEngineV1.h"

uint8 slayKey(slayDisplay* Display, uint64 Key)
{
    SDL_PollEvent(&Display->Event);
    const uint8 *state = SDL_GetKeyboardState(NULL);

    return state[Key];
}