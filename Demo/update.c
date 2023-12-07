#include "game.h"

uint8 updateQueue(slayEngine* Engine)
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

void* updateEagleThread(void* Engine)
{
    slayEngine* engine;

    engine = Engine;
    switch (((slayEngine*)Engine)->CurrentScene)
    {
        case 1:
            updateEagle(engine, ((scene1*)engine->Scenes->Values[1])->Eagle);
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
            updateProjectile(engine, ((scene1*)engine->Scenes->Values[1])->Projectiles, ((scene1*)engine->Scenes->Values[1])->Player, ((scene1*)engine->Scenes->Values[1])->Eagle, ((scene1*)engine->Scenes->Values[1])->Platforms, ((scene1*)engine->Scenes->Values[1])->SoundFire);
            break;
    }

    slayThreadExit;
}