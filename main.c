#include "game.h"

#undef main

uint16 main(uint64 argc, char* *argv)
{
    slayEngine* Engine;

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 2, 2, 165);
    loadGame(Engine);

    loadScene0(Engine);

    while(slayEvent(Engine))
    {
        slayUpdateDeltaTime(Engine);

        updateQueue(Engine);
        renderQueue(Engine);

        slayCapFPS(Engine);
    }

    switch (Engine->CurrentScene)
    {
        case 1:
            unloadScene1(Engine);
            break;
    }

    return 0;
}