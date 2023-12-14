#include "SlayEngineV1.h"

uint8 slayThreadStart(slayEngine* Engine, uint64 ID, void* Function)
{
    if (pthread_create((pthread_t*)Engine->Threads->Values[ID], NULL, Function, (void*)Engine) != 0)
    {
        printf("ERROR Unable to create THREAD_%ld\n", ID);
        exit(1);
    }

    return 0;
}

uint8 slayThreadWaitExit(slayEngine* Engine, uint64 ID)
{
    if (pthread_join(*(pthread_t*)Engine->Threads->Values[ID], NULL) != 0)
    {
        printf("ERROR Unable to join THREAD_%ld\n", ID);
        exit(1);
    }

    return 0;
}