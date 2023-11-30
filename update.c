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
    pthread_create((pthread_t*)Engine->Threads->Values[0], NULL, updatePlayerThread, (void*)Engine);
    pthread_create((pthread_t*)Engine->Threads->Values[1], NULL, updateProjectileThread, (void*)Engine);
    pthread_join(*(pthread_t*)Engine->Threads->Values[0], NULL);
    pthread_join(*(pthread_t*)Engine->Threads->Values[1], NULL);
}

void* updatePlayerThread(void* Engine)
{
    slayEngine* engine;

    engine = Engine;
    switch (((slayEngine*)Engine)->CurrentScene)
    {
        case 0:
            updatePlayer(((scene0*)engine->Scenes->Values[0])->Player, ((scene0*)engine->Scenes->Values[0])->Platforms, engine->DeltaTime);
            break;
    }

    pthread_exit(NULL);
}

void* updateProjectileThread(void* Engine)
{
    slayEngine* engine;

    engine = Engine;
    switch (((slayEngine*)Engine)->CurrentScene)
    {
        case 0:
            updateProjectile(((scene0*)engine->Scenes->Values[0])->Projectiles, ((scene0*)engine->Scenes->Values[0])->Player, ((scene0*)engine->Scenes->Values[0])->Platforms, ((scene0*)engine->Scenes->Values[0])->Volume, engine->DeltaTime);
            break;
    }

    pthread_exit(NULL);
}