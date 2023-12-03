#include "game.h"

uint16 updateScene1(slayEngine* Engine, scene1* Scene);

void* updatePlayerThread(void* Engine);
void* updateProjectileThread(void* Engine);

uint16 updateQueue(slayEngine* Engine)
{
    switch (Engine->CurrentScene)
    {
        case 1:
            updateScene1(Engine, Engine->Scenes->Values[1]);
            break;
    }

    return 0;
}

uint16 updateScene1(slayEngine* Engine, scene1* Scene)
{
    //1
    updatePause(Engine, &Scene->paused);
    if (Scene->paused)
    {
        return 1;
    }
    //2
    slayThreadStart(Engine, 0, updatePlayerThread);
    slayThreadStart(Engine, 1, updateProjectileThread);
    slayThreadWaitExit(Engine, 0);
    slayThreadWaitExit(Engine, 1);
    //3

    return 0;
}

void* updatePlayerThread(void* Engine)
{
    slayEngine* engine;

    engine = Engine;
    switch (((slayEngine*)Engine)->CurrentScene)
    {
        case 1:
            updatePlayer(engine, ((scene1*)engine->Scenes->Values[1])->Player, ((scene1*)engine->Scenes->Values[1])->Platforms);
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
        case 1:
            updateProjectile(engine, ((scene1*)engine->Scenes->Values[1])->Projectiles, ((scene1*)engine->Scenes->Values[1])->Player, ((scene1*)engine->Scenes->Values[1])->Platforms);
            break;
    }

    slayThreadExit;
}