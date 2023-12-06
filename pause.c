#include "game.h"

pause* newPause(slayEngine* Engine)
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

    result->Buttons = arrNew(2);

    result->Buttons->Values[0] = newButton(Engine, 810, 330, 300, 100, "assets/buttons/buttonbase.png", "assets/buttons/buttonhover.png");
    result->Buttons->Values[1] = newButton(Engine, 810, 630, 300, 100, "assets/buttons/buttonbase.png", "assets/buttons/buttonhover.png");

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
        if (slayCursorCollision(Engine, ((button*)Pause->Buttons->Values[0])->Hitbox))
        {
            ((button*)Pause->Buttons->Values[0])->TextureCurrent = ((button*)Pause->Buttons->Values[0])->TextureHover;

            if (slayKey(Engine, SDL_SCANCODE_LMB))
            {
                ((button*)Pause->Buttons->Values[0])->Pressed = true;
            }
            else if (((button*)Pause->Buttons->Values[0])->Pressed)
            {
                *Paused = false;

                ((button*)Pause->Buttons->Values[0])->Pressed = false;
            }
        }
        else
        {
            ((button*)Pause->Buttons->Values[0])->Pressed = false;
            ((button*)Pause->Buttons->Values[0])->TextureCurrent = ((button*)Pause->Buttons->Values[0])->TextureBase;
        }

        if (slayCursorCollision(Engine, ((button*)Pause->Buttons->Values[1])->Hitbox))
        {
            ((button*)Pause->Buttons->Values[1])->TextureCurrent = ((button*)Pause->Buttons->Values[1])->TextureHover;

            if (slayKey(Engine, SDL_SCANCODE_LMB))
            {
                ((button*)Pause->Buttons->Values[1])->Pressed = true;
            }
            else if (((button*)Pause->Buttons->Values[1])->Pressed)
            {
                unloadSceneCurrent(Engine);
                loadScene0(Engine);

                return 1;
            }
        }
        else
        {
            ((button*)Pause->Buttons->Values[1])->Pressed = false;
            ((button*)Pause->Buttons->Values[1])->TextureCurrent = ((button*)Pause->Buttons->Values[1])->TextureBase;
        }
    }

    return 0;
}

uint16 renderPause(slayEngine* Engine, pause* Pause)
{
    slayRenderColor(Engine, Pause->X, Pause->Y, Pause->Width, Pause->Height, Pause->ColorR, Pause->ColorG, Pause->ColorB, Pause->ColorA);

    for (uint64 i = 0; i < Pause->Buttons->Length; i++)
    {
        slayRenderTexture(Engine, ((button*)Pause->Buttons->Values[i])->X, ((button*)Pause->Buttons->Values[i])->Y, ((button*)Pause->Buttons->Values[i])->Width, ((button*)Pause->Buttons->Values[i])->Height, 0, slayFlipNONE, ((button*)Pause->Buttons->Values[i])->TextureCurrent, 255);
    }

    return 0;
}

uint16 destroyPause(pause* Pause)
{
    for (uint64 i = 0; i < Pause->Buttons->Length; i++)
    {
        destroyButton(Pause->Buttons->Values[i]);
    }
    arrPurge(Pause->Buttons);
    free(Pause);

    return 0;
}