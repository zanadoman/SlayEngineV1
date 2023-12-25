#include "game.h"

uint8 updateQueue(slayEngine* Engine)
{
    switch (Engine->CurrentScene)
    {
        case 0:
            updateScene0(Engine);
        break;

        case 1:
            updateScene1(Engine);
        break;

        case 2:
            updateScene2(Engine);
        break;
    }

    return 0;
}

int updatePlayerThread(void* Engine)
{
    updatePlayer(Engine);
    return 0;
}

int updateEagleThread(void* Engine)
{
    updateEagle(Engine);
    return 0;
}

int updateProjectileThread(void* Engine)
{
    //updateProjectile(Engine);
    return 0;
}