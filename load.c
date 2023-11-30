#include "game.h"

uint16 loadScene0(slayEngine* Engine);

uint16 loadGame(slayEngine* Engine)
{
    loadScene0(Engine);

    slayCursorVisibility(false);

    return 0;
}

uint16 loadScene0(slayEngine* Engine)
{
    scene0* scene;

    Engine->Scenes->Values[0] = malloc(sizeof(scene0));
    scene = Engine->Scenes->Values[0];

    scene->FontCrazyPixel = slayLoadFont("assets/crazy-pixel.ttf", 48);
    scene->Volume = 10;

    scene->Platforms = arrNew(5);
    scene->TextureBackground = slayLoadTexture(Engine, "assets/background.jpg");
    scene->TexturePlatform = slayLoadTexture(Engine, "assets/platform.png");
    scene->Platforms->Values[0] = newPlatform(-200, 550, 1200, 180);
    scene->Platforms->Values[1] = newPlatform(300, 450, 200, 30);
    scene->Platforms->Values[2] = newPlatform(200, 350, 100, 30);
    scene->Platforms->Values[3] = newPlatform(350, 250, 100, 30);
    scene->Platforms->Values[4] = newPlatform(500, 150, 100, 30);

    scene->Player = newPlayer();
    scene->Player->TextureLeft = slayLoadTexture(Engine, "assets/player_left.png");
    scene->Player->TextureRight = slayLoadTexture(Engine, "assets/player_right.png");
    scene->Player->SoundFire = slayLoadSound("assets/player_fire.wav");
    scene->Player->X = 386;
    scene->Player->Y = 410;
    scene->Player->MinX = -200;
    scene->Player->MaxX = 1000;
    Engine->Camera = slayNewCamera(&scene->Player->X, &scene->Player->Y, 14, 20, -960, -800, 1.5);

    scene->Projectiles = arrNew(0);

    return 0;
}