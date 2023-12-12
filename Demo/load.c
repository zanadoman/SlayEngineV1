#include "game.h"

uint8 loadGame(slayEngine* Engine)
{
    game* game;
    slayJSON* settings;

    Engine->Game = malloc(sizeof(game));
    game = Engine->Game;

    settings = slayLoadJSON("saves/settings.json");

    game->FontCrazyPixel = slayLoadFont("assets/crazy-pixel.ttf", 48);
    game->Volume = slayGetJSONKey(settings, "volume")->ValueNumber;
    game->TextureProjectile = slayLoadTexture(Engine, "assets/projectile.png");

    slayDestroyJSON(settings);

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