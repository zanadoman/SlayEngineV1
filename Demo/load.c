#include "game.h"

uint8 loadGame(slayEngine* Engine)
{
    game* game;

    Engine->Game = malloc(sizeof(game));
    game = Engine->Game;

    game->FontCrazyPixel = slayLoadFont("assets/crazy-pixel.ttf", 48);
    game->Volume = 10;
    game->TextureProjectile = slayLoadTexture(Engine, "assets/projectile.png");

    return 0;
}

uint8 unloadSceneCurrent(slayEngine* Engine)
{
    switch (Engine->CurrentScene)
    {
        case 0:
            unloadScene0(Engine);
            break;
        case 1:
            unloadScene1(Engine);
            break;
        case 2:
            unloadScene2(Engine);
            break;
    }

    return 0;
}