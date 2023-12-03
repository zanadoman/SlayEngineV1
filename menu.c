#include "game.h"

uint16 updateMenu(slayEngine* Engine, scene0* Scene)
{
    if (slayCursorCollision(Engine, Scene->ButtonScene1->Hitbox))
    {
        Scene->ButtonScene1->TextureCurrent = Scene->ButtonScene1->TextureHover;

        if (slayKey(Engine, SDL_SCANCODE_LMB))
        {
            unloadScene0(Engine);
            loadScene1(Engine);
        }
    }
    else
    {
        Scene->ButtonScene1->TextureCurrent = Scene->ButtonScene1->TextureBase;
    }

    return 0;
}