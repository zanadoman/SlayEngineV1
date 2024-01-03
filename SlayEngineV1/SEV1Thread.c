#include "SlayEngineV1.h"

uint8 slayThreadStart(slayEngine* Engine, uint64 ID, void* Function)
{
    if (Engine == NULL)
    {
        printf("slayThreadStart(): Engine must not be NULL\nParams: Engine: %p, ID: %lld, Function: %p\n", Engine, ID, Function);
        exit(1);
    }
    if (Function == NULL)
    {
        printf("slayThreadStart(): Function must not be NULL\nParams: Engine: %p, ID: %lld, Function: %p\n", Engine, ID, Function);
        exit(1);
    }

    for (uint64 i = Engine->Threads->Length; i <= ID; i++)
    {
        arrInsert(Engine->Threads, i);
    }

    Engine->Threads->Values[ID].Pointer = SDL_CreateThread(Function, NULL, Engine);
    if (Engine->Threads->Values[ID].Pointer == NULL)
    {
        printf("slayThreadStart(): SDL_CreateThread() failed\nParams: Engine: %p, ID: %lld, Function: %p\n", Engine, ID, Function);
        exit(1);
    }

    return 0;
}

uint8 slayThreadWaitExit(slayEngine* Engine, uint64 ID)
{
    if (Engine == NULL)
    {
        printf("slayThreadWaitExit(): Engine must not be NULL\nParams: Engine: %p, ID: %lld\n", Engine, ID);
        exit(1);
    }

    SDL_WaitThread(Engine->Threads->Values[ID].Pointer, NULL);

    return 0;
}