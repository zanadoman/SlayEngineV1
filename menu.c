#include "game.h"

uint16 updateMenu(slayEngine* Engine, scene0* Scene)
{
    if (slayCursorCollision(Engine, ((button*)Scene->Buttons->Values[0])->Hitbox))
    {
        ((button*)Scene->Buttons->Values[0])->TextureCurrent = ((button*)Scene->Buttons->Values[0])->TextureHover;

        if (slayKey(Engine, SDL_SCANCODE_LMB))
        {
            ((button*)Scene->Buttons->Values[0])->Pressed = true;
        }
        else if (((button*)Scene->Buttons->Values[0])->Pressed)
        {
            unloadScene0(Engine);
            loadScene1(Engine);

            return 1;
        }
    }
    else
    {
        ((button*)Scene->Buttons->Values[0])->Pressed = false;
        ((button*)Scene->Buttons->Values[0])->TextureCurrent = ((button*)Scene->Buttons->Values[0])->TextureBase;
    }

    if (slayCursorCollision(Engine, ((button*)Scene->Buttons->Values[1])->Hitbox))
    {
        ((button*)Scene->Buttons->Values[1])->TextureCurrent = ((button*)Scene->Buttons->Values[1])->TextureHover;

        if (slayKey(Engine, SDL_SCANCODE_LMB))
        {
            ((button*)Scene->Buttons->Values[1])->Pressed = true;
        }
        else if (((button*)Scene->Buttons->Values[1])->Pressed)
        {
            unloadScene0(Engine);
            loadScene2(Engine);

            return 1;
        }
    }
    else
    {
        ((button*)Scene->Buttons->Values[1])->Pressed = false;
        ((button*)Scene->Buttons->Values[1])->TextureCurrent = ((button*)Scene->Buttons->Values[1])->TextureBase;
    }

    return 0;
}