/*
**Particle system
**Bloom
**Mouse cursor texture switching
**Networking
*/

#include "game.h"

#undef main

typedef struct
{
    double X;
    double Y;
} player;

sint32 main(sint32 argc, char* *argv)
{
    slayEngine* Engine;
    player Player;

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 3, 165, "assets/icon.png");

    Player.X = 500;
    Player.Y = 500;

    while (slayUpdate(Engine))
    {
        if (slayKey(Engine, SDL_SCANCODE_UP))
        {
            Player.Y -= 0.3 * Engine->DeltaTime;
        }
        else if (slayKey(Engine, SDL_SCANCODE_DOWN))
        {
            Player.Y += 0.3 * Engine->DeltaTime;
        }
        if (slayKey(Engine, SDL_SCANCODE_LEFT))
        {
            Player.X -= 0.3 * Engine->DeltaTime;
        }
        else if (slayKey(Engine, SDL_SCANCODE_RIGHT))
        {
            Player.X += 0.3 * Engine->DeltaTime;
        }

        slayRenderStart(Engine);
        slayRenderColor(Engine, Player.X, Player.Y, 50, 50, 0, 64, 0, 255);
        slayRenderEnd(Engine);

        slayCapFPS(Engine);
    }

    return 0;
}