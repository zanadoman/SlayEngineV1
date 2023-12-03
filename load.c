#include "game.h"

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

uint16 loadScene1(slayEngine* Engine)
{
    scene1* scene;
    array save;

    //Scene
    Engine->Scenes->Values[1] = malloc(sizeof(scene1));
    scene = Engine->Scenes->Values[1];

    //Platform
    scene->Platforms = arrNew(5);
    scene->TextureBackground = slayLoadTexture(Engine, "assets/background.jpg");
    scene->TexturePlatform = slayLoadTexture(Engine, "assets/platform.png");
    scene->Platforms->Values[0] = newPlatform(-200, 550, 1200, 180);
    scene->Platforms->Values[1] = newPlatform(300, 450, 200, 30);
    scene->Platforms->Values[2] = newPlatform(200, 350, 100, 30);
    scene->Platforms->Values[3] = newPlatform(350, 250, 100, 30);
    scene->Platforms->Values[4] = newPlatform(500, 150, 100, 30);

    //Player
    scene->Player = newPlayer();
    scene->Player->TextureBase = slayLoadTexture(Engine, "assets/player_base.png");
    scene->Player->SoundFire = slayLoadSound("assets/player_fire.wav");
    save = arrNew(0);
    if (fileRead("scene1.txt", save))
    {
        scene->Player->X = STRtoDOUBLE(((string)save->Values[0])->String, NULL);
        scene->Player->Y = STRtoDOUBLE(((string)save->Values[1])->String, NULL);
        scene->Player->Facing = STRtoDOUBLE(((string)save->Values[2])->String, NULL);
        strPurge(save->Values[0]);
        strPurge(save->Values[1]);
        strPurge(save->Values[2]);
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
    
    //Projectiles
    scene->Projectiles = arrNew(0);

    return 0;
}

uint16 unloadScene1(slayEngine* Engine)
{
    scene1* scene;
    array save;

    scene = Engine->Scenes->Values[1];

    save = arrNew(3);
    save->Values[0] = strNew();
    save->Values[1] = strNew();
    save->Values[2] = strNew();
    DOUBLEtoSTR(scene->Player->X, save->Values[0]);
    DOUBLEtoSTR(scene->Player->Y, save->Values[1]);
    SINTtoSTR(scene->Player->Facing, save->Values[2]);
    fileWrite(save, "scene1.txt");

    //Platform
    slayUnloadTexture(scene->TextureBackground);
    slayUnloadTexture(scene->TexturePlatform);
    for (uint64 i = 0; i < scene->Platforms->Length; i++)
    {
        free(((platform*)scene->Platforms->Values[i])->Hitbox);
    }
    for (uint64 i = 0; i < scene->Platforms->Length; i++)
    {
        free(scene->Platforms->Values[i]);
    }

    //Player
    slayUnloadTexture(scene->Player->TextureBase);
    slayUnloadSound(scene->Player->SoundFire);
    free(((player*)scene->Player)->Hitbox);
    free(scene->Player);

    //Projectiles
    for (uint64 i = 0; i < scene->Projectiles->Length; i++)
    {
        free(((projectile*)scene->Projectiles->Values[i])->Hitbox);
    }
    for (uint64 i = 0; i < scene->Projectiles->Length; i++)
    {
        free(scene->Projectiles->Values[i]);
    }

    return 0;
}