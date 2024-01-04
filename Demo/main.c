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

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 3, 165, "assets/icon.png");

    while (slayUpdate(Engine))
    {
        slayRenderStart(Engine);
        slayRenderColor(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, 0, 64, 0, 255);
        slayRenderEnd(Engine);

        slayCapFPS(Engine);
    }

    return 0;
}