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

uint16 loadScene0(slayEngine* Engine)
{
    scene0* scene;

    //Scene
    Engine->Scenes->Values[0] = malloc(sizeof(scene0));
    scene = Engine->Scenes->Values[0];

    //Color
    scene->ColorR = 0;
    scene->ColorG = 0;
    scene->ColorB = 0;

    //Button
    scene->ButtonScene1 = malloc(sizeof(button));
    scene->ButtonScene1->TextureBase = slayLoadTexture(Engine, "assets/buttons/buttonbase.png");
    scene->ButtonScene1->TextureHover = slayLoadTexture(Engine, "assets/buttons/buttonhover.png");
    scene->ButtonScene1->TextureCurrent = scene->ButtonScene1->TextureBase;
    scene->ButtonScene1->X = 810;
    scene->ButtonScene1->Y = 330;
    scene->ButtonScene1->Width = 300;
    scene->ButtonScene1->Height = 100;
    scene->ButtonScene1->Hitbox = slayNewHitbox(&scene->ButtonScene1->X, &scene->ButtonScene1->Y, 0, 0, 300, 100);

    Engine->CurrentScene = 0;

    return 0;
}

uint16 unloadScene0(slayEngine* Engine)
{
    scene0* scene;

    scene = Engine->Scenes->Values[0];

    //Buttons
    slayUnloadTexture(scene->ButtonScene1->TextureBase);
    slayUnloadTexture(scene->ButtonScene1->TextureHover);
    free(scene->ButtonScene1->Hitbox);
    free(scene->ButtonScene1);

    //Scene
    free(scene);
    Engine->Scenes->Values[0] = NULL;

    return 0;
}

uint16 loadScene1(slayEngine* Engine)
{
    scene1* scene;
    array save;

    //Scene
    Engine->Scenes->Values[1] = malloc(sizeof(scene1));
    scene = Engine->Scenes->Values[1];

    //Pause
    scene->Pause = newPause();
    scene->Pause->ButtonResume->TextureBase = slayLoadTexture(Engine, "assets/buttons/buttonbase.png");
    scene->Pause->ButtonResume->TextureHover = slayLoadTexture(Engine, "assets/buttons/buttonhover.png");
    scene->Pause->ButtonResume->TextureCurrent = scene->Pause->ButtonResume->TextureBase;
    scene->Pause->ButtonQuit->TextureBase = slayLoadTexture(Engine, "assets/buttons/buttonbase.png");
    scene->Pause->ButtonQuit->TextureHover = slayLoadTexture(Engine, "assets/buttons/buttonhover.png");
    scene->Pause->ButtonQuit->TextureCurrent = scene->Pause->ButtonQuit->TextureBase;
    scene->paused = false;

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
    if (fileRead("saves/scene1.txt", save) && save->Length == 3)
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

    Engine->CurrentScene = 1;

    return 0;
}

uint16 unloadScene1(slayEngine* Engine)
{
    scene1* scene;
    array save;

    scene = Engine->Scenes->Values[1];

    //Save
    save = arrNew(3);
    save->Values[0] = strNew();
    save->Values[1] = strNew();
    save->Values[2] = strNew();
    DOUBLEtoSTR(scene->Player->X, save->Values[0]);
    DOUBLEtoSTR(scene->Player->Y, save->Values[1]);
    SINTtoSTR(scene->Player->Facing, save->Values[2]);
    fileWrite(save, "saves/scene1.txt");
    strPurge(save->Values[0]);
    strPurge(save->Values[1]),
    strPurge(save->Values[2]);
    arrPurge(save);

    //Pause
    slayUnloadTexture(scene->Pause->ButtonResume->TextureBase);
    slayUnloadTexture(scene->Pause->ButtonResume->TextureHover);
    free(scene->Pause->ButtonResume->Hitbox);
    free(scene->Pause->ButtonResume);
    slayUnloadTexture(scene->Pause->ButtonQuit->TextureBase);
    slayUnloadTexture(scene->Pause->ButtonQuit->TextureHover);
    free(scene->Pause->ButtonQuit->Hitbox);
    free(scene->Pause->ButtonQuit);
    free(scene->Pause);

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
    arrPurge(scene->Platforms);

    //Player
    slayUnloadTexture(scene->Player->TextureBase);
    slayUnloadSound(scene->Player->SoundFire);
    free(scene->Player->Hitbox);
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
    arrPurge(scene->Projectiles);

    //Scene
    free(scene);
    Engine->Scenes->Values[1] = NULL;

    return 0;
}

uint16 unloadSceneCurrent(slayEngine* Engine)
{
    switch (Engine->CurrentScene)
    {
        case 0:
            unloadScene0(Engine);
            break;
        case 1:
            unloadScene1(Engine);
            break;
    }

    return 0;
}