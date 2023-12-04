#include "game.h"

uint16 updateMenu(slayEngine* Engine, scene0* Scene)
{
    if (slayCursorCollision(Engine, ((button*)Scene->Buttons->Values[0])->Hitbox))
    {
        ((button*)Scene->Buttons->Values[0])->TextureCurrent = ((button*)Scene->Buttons->Values[0])->TextureHover;

        if (slayKey(Engine, SDL_SCANCODE_LMB))
        {
            unloadScene0(Engine);
            loadScene1(Engine);
        }
    }
    else
    {
        ((button*)Scene->Buttons->Values[0])->TextureCurrent = ((button*)Scene->Buttons->Values[0])->TextureBase;
    }

    return 0;
}