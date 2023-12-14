/*
**Particle system
**Bloom
**Mouse cursor texture switching
**Networking
*/

#include "game.h"

#undef main

sint32 main(sint32 argc, char* *argv)
{
    slayEngine* Engine;

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 2, 3, 165, "assets/icon.png");
    loadGame(Engine);

    loadScene0(Engine);

    while (slayUpdate(Engine))
    {
        updateQueue(Engine);
        renderQueue(Engine);

        slayCapFPS(Engine);
    }

    unloadSceneCurrent(Engine);

    return 0;
}