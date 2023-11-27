/*
Contains the update queue for the object in the game that needs to be updated.
The queue is split to phases and phases are split to threads.
Each phase starts multiple threads and wait for them to finish.
A thread will always call the corresponding update function from the object's code.
*/

#include "game.h"

void* updatePlayerThread(void* Game);
void* updateProjectileThread(void* Game);

uint16 updateQueue(game* Game)
{
    //1.
    pthread_create((pthread_t*)Game->Threads->Values[0], NULL, updatePlayerThread, (void*)Game);
    pthread_create((pthread_t*)Game->Threads->Values[1], NULL, updateProjectileThread, (void*)Game);
    pthread_join(*(pthread_t*)Game->Threads->Values[0], NULL);
    pthread_join(*(pthread_t*)Game->Threads->Values[1], NULL);
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