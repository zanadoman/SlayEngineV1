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
    double X, Y;

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 0, 165, NULL);

    X = 935;
    Y = 515;

    while (slayUpdate(Engine))
    {
        if (slayKey(Engine, SDL_SCANCODE_LEFT))
        {
            X -= 0.3 * Engine->DeltaTime;
        }
        else if (slayKey(Engine, SDL_SCANCODE_RIGHT))
        {
            X += 0.3 * Engine->DeltaTime;
        }
        if (slayKey(Engine, SDL_SCANCODE_UP))
        {
            Y -= 0.3 * Engine->DeltaTime;
        }
        else if (slayKey(Engine, SDL_SCANCODE_DOWN))
        {
            Y += 0.3 * Engine->DeltaTime;
        }

        slayRenderStart(Engine);
        slayRenderColor(Engine, X, Y, 50, 50, 0, 64, 0, 255);
        slayRenderEnd(Engine);

        slayCapFPS(Engine);
    }

    return 0;
}