#include "game.h"

#undef main

uint16 main(uint64 argc, char* *argv)
{
    slayEngine* Engine;

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 2, 2, 165);
    loadGame(Engine);

    loadScene1(Engine);
    Engine->CurrentScene = 1;

    while(slayEvent(Engine))
    {
        slayUpdateDeltaTime(Engine);

        updateQueue(Engine);
        renderQueue(Engine);

        slayCapFPS(Engine);
    }

    unloadScene1(Engine);

    return 0;
}