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

void* updatePlayerThread(void* Engine)
{
    updatePlayer(Engine);
    slayThreadExit;
}

void* updateEagleThread(void* Engine)
{
    updateEagle(Engine);
    slayThreadExit;
}

void* updateProjectileThread(void* Engine)
{
    updateProjectile(Engine);
    slayThreadExit;
}