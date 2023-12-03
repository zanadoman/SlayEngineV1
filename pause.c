#include "game.h"

uint16 updatePause(slayEngine* Engine, logic* Paused)
{
    if (slayKey(Engine, SDL_SCANCODE_ESCAPE))
    {
        *Paused = true;
    }

    return 0;
}