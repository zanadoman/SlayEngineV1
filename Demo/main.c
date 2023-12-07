#include "game.h"

#undef main

uint16 main(uint8 argc, char* *argv)
{
    slayEngine* Engine;

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 2, 3, 165, "assets/icon.png");
    loadGame(Engine);

    loadScene0(Engine);

    while (slayEvent(Engine))
    {
        slayUpdateDeltaTime(Engine);

        updateQueue(Engine);
        renderQueue(Engine);

        slayCapFPS(Engine);
    }

    unloadSceneCurrent(Engine);

    return 0;
}