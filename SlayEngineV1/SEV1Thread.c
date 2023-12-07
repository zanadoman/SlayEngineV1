#include "SlayEngineV1.h"

uint8 slayThreadStart(slayEngine* Engine, uint64 ID, void* Function)
{
    pthread_create((pthread_t*)Engine->Threads->Values[ID], NULL, Function, (void*)Engine);

    return 0;
}

uint8 slayThreadWaitExit(slayEngine* Engine, uint64 ID)
{
    pthread_join(*(pthread_t*)Engine->Threads->Values[ID], NULL);

    return 0;
}