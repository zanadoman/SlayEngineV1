#include "game.h"

pause* newPause()
{
    pause* result;

    result = malloc(sizeof(pause));

    result->X = 710;
    result->Y = 130;

    result->Width = 500;
    result->Height = 800;

    result->ColorR = 0;
    result->ColorG = 0;
    result->ColorB = 0;
    result->ColorA = 192;

    result->ButtonResume = malloc(sizeof(button));
    result->ButtonResume->X = 810;
    result->ButtonResume->Y = 330;
    result->ButtonResume->Width = 300;
    result->ButtonResume->Height = 100;
    result->ButtonResume->Hitbox = slayNewHitbox(&result->ButtonResume->X, &result->ButtonResume->Y, 0, 0, 300, 100);

    result->ButtonQuit = malloc(sizeof(button));
    result->ButtonQuit->X = 810;
    result->ButtonQuit->Y = 630;
    result->ButtonQuit->Width = 300;
    result->ButtonQuit->Height = 100;
    result->ButtonQuit->Hitbox = slayNewHitbox(&result->ButtonQuit->X, &result->ButtonQuit->Y, 0, 0, 300, 100);

    return result;
}

uint16 updatePause(slayEngine* Engine, pause* Pause, logic* Paused)
{
    if (slayKey(Engine, SDL_SCANCODE_ESCAPE))
    {
        *Paused = true;
    }

    if (*Paused)
    {
        if (slayCursorCollision(Engine, Pause->ButtonResume->Hitbox))
        {
            Pause->ButtonResume->TextureCurrent = Pause->ButtonResume->TextureHover;

            if (slayKey(Engine, SDL_SCANCODE_LMB))
            {
                *Paused = false;
            }
        }
        else
        {
            Pause->ButtonResume->TextureCurrent = Pause->ButtonResume->TextureBase;
        }

        if (slayCursorCollision(Engine, Pause->ButtonQuit->Hitbox))
        {
            Pause->ButtonQuit->TextureCurrent = Pause->ButtonQuit->TextureHover;
        }
        else
        {
            Pause->ButtonQuit->TextureCurrent = Pause->ButtonQuit->TextureBase;
        }
    }

    return 0;
}