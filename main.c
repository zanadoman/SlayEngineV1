/*
Egérgomb input standardizálása
Player coordinátáinak elmentése, behúzása
Wiki írása
*/

#include "game.h"

#undef main

int main(int argc, char *argv[])
{
    slayEngine* Engine;

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 1, 2, 165);
    loadQueue(Engine);

    Engine->CurrentScene = 0;

    while(slayEvent(Engine))
    {
        slayUpdateDeltaTime(Engine);

        updateQueue(Engine);
        renderQueue(Engine);

        slayCapFPS(Engine);
    }

    return 0;
}