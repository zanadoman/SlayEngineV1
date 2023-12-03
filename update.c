#include "game.h"

uint16 updateScene0(slayEngine* Engine);

void* updatePlayerThread(void* Engine);
void* updateProjectileThread(void* Engine);

uint16 updateQueue(slayEngine* Engine)
{
    switch (Engine->CurrentScene)
    {
        case 0:
            updateScene0(Engine);
            break;
    }

    return 0;
}

uint16 updateScene0(slayEngine* Engine)
{
    slayThreadStart(Engine, 0, updatePlayerThread);
    slayThreadStart(Engine, 1, updateProjectileThread);
    slayThreadWaitExit(Engine, 0);
    slayThreadWaitExit(Engine, 1);
}

void* updatePlayerThread(void* Engine)
{
    slayEngine* engine;

    engine = Engine;
    switch (((slayEngine*)Engine)->CurrentScene)
    {
        case 0:
            updatePlayer(engine, ((scene0*)engine->Scenes->Values[0])->Player, ((scene0*)engine->Scenes->Values[0])->Platforms);
            break;
    }

    slayThreadExit;
}

void* updateProjectileThread(void* Engine)
{
    slayEngine* engine;

    engine = Engine;
    switch (((slayEngine*)Engine)->CurrentScene)
    {
        case 0:
            updateProjectile(engine, ((scene0*)engine->Scenes->Values[0])->Projectiles, ((scene0*)engine->Scenes->Values[0])->Player, ((scene0*)engine->Scenes->Values[0])->Platforms);
            break;
    }

    slayThreadExit;
}