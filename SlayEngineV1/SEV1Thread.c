#include "SlayEngineV1.h"

uint8 slayThreadStart(slayEngine* Engine, uint64 ID, void* Function)
{
    if (Engine->Threads->Length <= ID)
    {
        for (uint64 i = Engine->Threads->Length; i <= ID; i++)
        {
            if (arrInsert(Engine->Threads, i, NULL) != 0)
            {
                printf("ERROR Unable to expand THREADS_%ld\n", ID);
                exit(1);
            }
        }
    }

    Engine->Threads->Values[ID] = SDL_CreateThread(Function, NULL, Engine);
    if (Engine->Threads->Values[ID] == NULL)
    {
        printf("ERROR Unable to create THREAD_%ld\n", ID);
        exit(1);
    }

    return 0;
}

uint8 slayThreadWaitExit(slayEngine* Engine, uint64 ID)
{
    SDL_WaitThread(Engine->Threads->Values[ID], NULL);

    return 0;
}