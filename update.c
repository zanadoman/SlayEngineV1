#include "game.h"

uint16 updateZoomIn(Game);
void* updatePlayerThread(void* Game);
void* updateProjectileThread(void* Game);

uint16 updateQueue(game* Game)
{
    //0.
    updateZoomIn(Game);
    //1.
    pthread_create((pthread_t*)Game->Threads->Values[0], NULL, updatePlayerThread, (void*)Game);
    pthread_create((pthread_t*)Game->Threads->Values[1], NULL, updateProjectileThread, (void*)Game);
    pthread_join(*(pthread_t*)Game->Threads->Values[0], NULL);
    pthread_join(*(pthread_t*)Game->Threads->Values[1], NULL);
    //2.

    return 0;
}

uint16 updateZoomIn(game* Game)
{
    if (Game->Camera->Zoom < 1)
    {
        Game->Camera->Zoom += 0.0002 * Game->DeltaTime;
    }
    else if (Game->Camera->Zoom > 1)
    {
        Game->Camera->Zoom = 1;
    }

    return 0;
}

void* updatePlayerThread(void* Game)
{
    updatePlayer(Game);
    pthread_exit(NULL);
}

void* updateProjectileThread(void* Game)
{
    updateProjectile((game*)Game);
    pthread_exit(NULL);
}