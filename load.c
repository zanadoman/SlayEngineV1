#include "game.h"

uint16 loadGame(slayEngine* Engine);
uint16 loadScene0(slayEngine* Engine);

uint16 loadQueue(slayEngine* Engine)
{
    loadGame(Engine);
    loadScene0(Engine);

    return 0;
}

uint16 loadGame(slayEngine* Engine)
{
    game* game;

    Engine->Game = malloc(sizeof(game));
    game = Engine->Game;

    game->FontCrazyPixel = slayLoadFont("assets/crazy-pixel.ttf", 48);
    game->Volume = 10;
    game->TextureProjectile = slayLoadTexture(Engine, "assets/projectile.png");

    return 0;
}

uint16 loadScene0(slayEngine* Engine)
{
    scene0* scene;
    array save;

    Engine->Scenes->Values[0] = malloc(sizeof(scene0));
    scene = Engine->Scenes->Values[0];

    scene->Platforms = arrNew(5);
    scene->TextureBackground = slayLoadTexture(Engine, "assets/background.jpg");
    scene->TexturePlatform = slayLoadTexture(Engine, "assets/platform.png");
    scene->Platforms->Values[0] = newPlatform(-200, 550, 1200, 180);
    scene->Platforms->Values[1] = newPlatform(300, 450, 200, 30);
    scene->Platforms->Values[2] = newPlatform(200, 350, 100, 30);
    scene->Platforms->Values[3] = newPlatform(350, 250, 100, 30);
    scene->Platforms->Values[4] = newPlatform(500, 150, 100, 30);

    scene->Player = newPlayer();
    scene->Player->TextureBase = slayLoadTexture(Engine, "assets/player_base.png");
    scene->Player->SoundFire = slayLoadSound("assets/player_fire.wav");
    save = arrNew(0);
    if (fileRead("save.txt", save))
    {
        ((scene0*)Engine->Scenes->Values[0])->Player->X = STRtoDOUBLE(((string)save->Values[0])->String, NULL);
        ((scene0*)Engine->Scenes->Values[0])->Player->Y = STRtoDOUBLE(((string)save->Values[1])->String, NULL);
        strPurge(save->Values[0]);
        strPurge(save->Values[1]);
    }
    else
    {
        scene->Player->X = 386;
        scene->Player->Y = 410;
    }
    arrPurge(save);
    scene->Player->MinX = -200;
    scene->Player->MaxX = 1000;
    scene->Player->MinY = -500;
    scene->Player->MaxY = 600;
    slaySetCamera(Engine, &scene->Player->X, &scene->Player->Y, 14, 20, -960, -800, 1.5);
    
    scene->Projectiles = arrNew(0);

    return 0;
}