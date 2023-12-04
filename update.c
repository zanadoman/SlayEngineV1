#include "game.h"

uint16 updateScene0(slayEngine* Engine, scene0* Scene);
uint16 updateScene1(slayEngine* Engine, scene1* Scene);
uint16 updateScene2(slayEngine* Engine, scene2* Scene);

void* updatePlayerThread(void* Engine);
void* updateProjectileThread(void* Engine);

uint16 updateQueue(slayEngine* Engine)
{
    switch (Engine->CurrentScene)
    {
        case 0:
            updateScene0(Engine, Engine->Scenes->Values[0]);
            break;
        case 1:
            updateScene1(Engine, Engine->Scenes->Values[1]);
            break;
        case 2:
            updateScene2(Engine, Engine->Scenes->Values[2]);
            break;
    }

    return 0;
}

uint16 updateScene0(slayEngine* Engine, scene0* Scene)
{
    //1
    updateMenu(Engine, Scene);
    //2

    return 0;
}

uint16 updateScene1(slayEngine* Engine, scene1* Scene)
{
    //1
    updatePause(Engine, Scene->Pause, &Scene->paused);
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

uint16 updateScene2(slayEngine* Engine, scene2* Scene)
{
    //1
    updatePause(Engine, Scene->Pause, &Scene->paused);
    if (Scene->paused)
    {
        return 1;
    }
    //2
    updatePlayer(Engine, Scene->Player, Scene->Platforms);
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