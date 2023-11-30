#include "game.h"

void* updatePlayerThread(void* Game);
void* updateProjectileThread(void* Game);

uint16 updateQueue(game* Game)
{
    //1.
    pthread_create((pthread_t*)Game->Engine->Threads->Values[0], NULL, updatePlayerThread, (void*)Game);
    pthread_create((pthread_t*)Game->Engine->Threads->Values[1], NULL, updateProjectileThread, (void*)Game);
    pthread_join(*(pthread_t*)Game->Engine->Threads->Values[0], NULL);
    pthread_join(*(pthread_t*)Game->Engine->Threads->Values[1], NULL);
    //2.

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