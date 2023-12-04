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

    result->Buttons->Values[0] = malloc(sizeof(button));
    ((button*)result->Buttons->Values[0])->X = 810;
    ((button*)result->Buttons->Values[0])->Y = 330;
    ((button*)result->Buttons->Values[0])->Width = 300;
    ((button*)result->Buttons->Values[0])->Height = 100;
    ((button*)result->Buttons->Values[0])->TextureBase = slayLoadTexture(Engine, "assets/buttons/buttonbase.png");
    ((button*)result->Buttons->Values[0])->TextureHover = slayLoadTexture(Engine, "assets/buttons/buttonhover.png");
    ((button*)result->Buttons->Values[0])->TextureCurrent = ((button*)result->Buttons->Values[0])->TextureBase;
    ((button*)result->Buttons->Values[0])->Hitbox = slayNewHitbox(&((button*)result->Buttons->Values[0])->X, &((button*)result->Buttons->Values[0])->Y, 0, 0, 300, 100);

    result->Buttons->Values[1] = malloc(sizeof(button));
    ((button*)result->Buttons->Values[1])->X = 810;
    ((button*)result->Buttons->Values[1])->Y = 630;
    ((button*)result->Buttons->Values[1])->Width = 300;
    ((button*)result->Buttons->Values[1])->Height = 100;
    ((button*)result->Buttons->Values[1])->TextureBase = slayLoadTexture(Engine, "assets/buttons/buttonbase.png");
    ((button*)result->Buttons->Values[1])->TextureHover = slayLoadTexture(Engine, "assets/buttons/buttonhover.png");
    ((button*)result->Buttons->Values[1])->TextureCurrent = ((button*)result->Buttons->Values[1])->TextureBase;
    ((button*)result->Buttons->Values[1])->Hitbox = slayNewHitbox(&((button*)result->Buttons->Values[1])->X, &((button*)result->Buttons->Values[1])->Y, 0, 0, 300, 100);

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
                *Paused = false;
            }
        }
        else
        {
            ((button*)Pause->Buttons->Values[0])->TextureCurrent = ((button*)Pause->Buttons->Values[0])->TextureBase;
        }

        if (slayCursorCollision(Engine, ((button*)Pause->Buttons->Values[1])->Hitbox))
        {
            ((button*)Pause->Buttons->Values[1])->TextureCurrent = ((button*)Pause->Buttons->Values[1])->TextureHover;

            if (slayKey(Engine, SDL_SCANCODE_LMB))
            {
                unloadSceneCurrent(Engine);
                loadScene0(Engine);
            }
        }
        else
        {
            ((button*)Pause->Buttons->Values[1])->TextureCurrent = ((button*)Pause->Buttons->Values[1])->TextureBase;
        }
    }

    return 0;
}