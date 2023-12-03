#include "game.h"

#undef main

uint16 main(uint64 argc, char* *argv)
{
    slayEngine* Engine;

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 1, 2, 165);
    loadGame(Engine);

    loadScene0(Engine);
    Engine->CurrentScene = 0;

    while(slayEvent(Engine))
    {
        slayUpdateDeltaTime(Engine);

        updateQueue(Engine);
        renderQueue(Engine);

        slayCapFPS(Engine);
    }

    saveQueue(Engine);

    return 0;
}