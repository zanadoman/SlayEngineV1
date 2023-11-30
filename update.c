#include "game.h"

void* updatePlayerThread(void* Engine);
void* updateProjectileThread(void* Engine);

uint16 updateQueue(slayEngine* Engine)
{
    switch (Engine->CurrentScene)
    {
        case 0:
            pthread_create((pthread_t*)Engine->Threads->Values[0], NULL, updatePlayerThread, (void*)Engine);
            pthread_create((pthread_t*)Engine->Threads->Values[1], NULL, updateProjectileThread, (void*)Engine);
            pthread_join(*(pthread_t*)Engine->Threads->Values[0], NULL);
            pthread_join(*(pthread_t*)Engine->Threads->Values[1], NULL);
            break;
    }

    return 0;
}

void* updatePlayerThread(void* Engine)
{
    switch (((slayEngine*)Engine)->CurrentScene)
    {
        case 0:
            updatePlayer(((scene0*)((slayEngine*)Engine)->Scenes->Values[0])->Player, ((scene0*)((slayEngine*)Engine)->Scenes->Values[0])->Platforms, ((slayEngine*)Engine)->DeltaTime);
            break;
    }

    pthread_exit(NULL);
}

void* updateProjectileThread(void* Engine)
{
    switch (((slayEngine*)Engine)->CurrentScene)
    {
        case 0:
            updateProjectile(((scene0*)((slayEngine*)Engine)->Scenes->Values[0])->Projectiles, ((scene0*)((slayEngine*)Engine)->Scenes->Values[0])->Player, ((scene0*)((slayEngine*)Engine)->Scenes->Values[0])->Platforms, ((scene0*)((slayEngine*)Engine)->Scenes->Values[0])->Volume, ((slayEngine*)Engine)->DeltaTime);
            break;
    }

    pthread_exit(NULL);
}