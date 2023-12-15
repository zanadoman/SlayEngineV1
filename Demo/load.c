#include "game.h"

uint8 loadGame(slayEngine* Engine)
{
    slayJSON* settings;

    Engine->Game = malloc(sizeof(game));

    settings = slayLoadJSON("saves/settings.json");

    ((game*)Engine->Game)->FontCrazyPixel = slayLoadFont("assets/crazy-pixel.ttf", 48);
    ((game*)Engine->Game)->Volume = slayGetJSONKey(settings, "volume")->ValueNumber;
    ((game*)Engine->Game)->TextureProjectile = slayLoadTexture(Engine, "assets/projectile.png");

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