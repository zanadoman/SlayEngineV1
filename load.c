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
    scene->Buttons = arrNew(2);
    
    scene->Buttons->Values[0] = malloc(sizeof(button));
    ((button*)scene->Buttons->Values[0])->TextureBase = slayLoadTexture(Engine, "assets/buttons/buttonbase.png");
    ((button*)scene->Buttons->Values[0])->TextureHover = slayLoadTexture(Engine, "assets/buttons/buttonhover.png");
    ((button*)scene->Buttons->Values[0])->TextureCurrent = ((button*)scene->Buttons->Values[0])->TextureBase;
    ((button*)scene->Buttons->Values[0])->X = 810;
    ((button*)scene->Buttons->Values[0])->Y = 330;
    ((button*)scene->Buttons->Values[0])->Width = 300;
    ((button*)scene->Buttons->Values[0])->Height = 100;
    ((button*)scene->Buttons->Values[0])->Pressed = false;
    ((button*)scene->Buttons->Values[0])->Hitbox = slayNewHitbox(&((button*)scene->Buttons->Values[0])->X, &((button*)scene->Buttons->Values[0])->Y, 0, 0, 300, 100);

    scene->Buttons->Values[1] = malloc(sizeof(button));
    ((button*)scene->Buttons->Values[1])->TextureBase = slayLoadTexture(Engine, "assets/buttons/buttonbase.png");
    ((button*)scene->Buttons->Values[1])->TextureHover = slayLoadTexture(Engine, "assets/buttons/buttonhover.png");
    ((button*)scene->Buttons->Values[1])->TextureCurrent = ((button*)scene->Buttons->Values[1])->TextureBase;
    ((button*)scene->Buttons->Values[1])->X = 810;
    ((button*)scene->Buttons->Values[1])->Y = 630;
    ((button*)scene->Buttons->Values[1])->Width = 300;
    ((button*)scene->Buttons->Values[1])->Height = 100;
    ((button*)scene->Buttons->Values[1])->Pressed = false;
    ((button*)scene->Buttons->Values[1])->Hitbox = slayNewHitbox(&((button*)scene->Buttons->Values[1])->X, &((button*)scene->Buttons->Values[1])->Y, 0, 0, 300, 100);

    //Scene
    Engine->CurrentScene = 0;

    return 0;
}

uint16 unloadScene0(slayEngine* Engine)
{
    scene0* scene;

    scene = Engine->Scenes->Values[0];

    //Buttons
    for (uint64 i = 0; i < scene->Buttons->Length; i++)
    {
        slayUnloadTexture(((button*)scene->Buttons->Values[i])->TextureBase);
        slayUnloadTexture(((button*)scene->Buttons->Values[i])->TextureHover);
        free(((button*)scene->Buttons->Values[i])->Hitbox);
        free(scene->Buttons->Values[i]);
    }
    arrPurge(scene->Buttons);

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
    scene->Pause = newPause(Engine);
    scene->paused = false;

    //Level
    scene->TextureBackground = slayLoadTexture(Engine, "assets/background.jpg");
    scene->TexturePlatform = slayLoadTexture(Engine, "assets/platform.png");
    scene->Platforms = arrNew(5);
    scene->Platforms->Values[0] = newPlatform(-200, 550, 1200, 180);
    scene->Platforms->Values[1] = newPlatform(300, 450, 200, 30);
    scene->Platforms->Values[2] = newPlatform(200, 350, 100, 30);
    scene->Platforms->Values[3] = newPlatform(350, 250, 100, 30);
    scene->Platforms->Values[4] = newPlatform(500, 150, 100, 30);
    
    //Player
    scene->Player = newPlayer(Engine);

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

    //Scene
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
    for (uint64 i = 0; i < scene->Pause->Buttons->Length; i++)
    {
        slayUnloadTexture(((button*)scene->Pause->Buttons->Values[i])->TextureBase);
        slayUnloadTexture(((button*)scene->Pause->Buttons->Values[i])->TextureHover);
        free(((button*)scene->Pause->Buttons->Values[i])->Hitbox);
        free(scene->Pause->Buttons->Values[i]);
    }
    arrPurge(scene->Pause->Buttons);
    free(scene->Pause);

    //Level
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

uint16 loadScene2(slayEngine* Engine)
{
    scene2* scene;
    array save;

    //Scene
    Engine->Scenes->Values[2] = malloc(sizeof(scene2));
    scene = Engine->Scenes->Values[2];

    //Pause
    scene->Pause = newPause(Engine);
    scene->paused = false;

    //Level
    scene->TextureBackground = slayLoadTexture(Engine, "assets/background.jpg");
    scene->TexturePlatform = slayLoadTexture(Engine, "assets/platform.png");
    scene->Platforms = arrNew(9);
    scene->Platforms->Values[0] = newPlatform(-450, 250 + slayRandom(-100, 100, 1), 100, 30);
    scene->Platforms->Values[1] = newPlatform(-250, 250 + slayRandom(-100, 100, 1), 100, 30);
    scene->Platforms->Values[2] = newPlatform(-50, 250 + slayRandom(-100, 100, 1), 100, 30);
    scene->Platforms->Values[3] = newPlatform(150, 250 + slayRandom(-100, 100, 2), 100, 30);
    scene->Platforms->Values[4] = newPlatform(350, 250, 100, 30);
    scene->Platforms->Values[5] = newPlatform(550, 250 + slayRandom(-100, 100, 3), 100, 30);
    scene->Platforms->Values[6] = newPlatform(750, 250 + slayRandom(-100, 100, 4), 100, 30);
    scene->Platforms->Values[7] = newPlatform(950, 250 + slayRandom(-100, 100, 1), 100, 30);
    scene->Platforms->Values[8] = newPlatform(1150, 250 + slayRandom(-100, 100, 1), 100, 30);
    
    //Player
    scene->Player = newPlayer(Engine);

    scene->Player->X = 386;
    scene->Player->Y = 210;

    scene->Player->MinX = -100000;
    scene->Player->MaxX = 100000;
    scene->Player->MinY = -100000;
    scene->Player->MaxY = 100000;

    slaySetCamera(Engine, &scene->Player->X, &scene->Player->Y, 14, 20, -960, -520, 1.5);

    //Scene
    Engine->CurrentScene = 2;

    return 0;
}

uint16 unloadScene2(slayEngine* Engine)
{
    scene2* scene;
    array save;

    scene = Engine->Scenes->Values[2];

    //Pause
    for (uint64 i = 0; i < scene->Pause->Buttons->Length; i++)
    {
        slayUnloadTexture(((button*)scene->Pause->Buttons->Values[i])->TextureBase);
        slayUnloadTexture(((button*)scene->Pause->Buttons->Values[i])->TextureHover);
        free(((button*)scene->Pause->Buttons->Values[i])->Hitbox);
        free(scene->Pause->Buttons->Values[i]);
    }
    arrPurge(scene->Pause->Buttons);
    free(scene->Pause);

    //Level
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

    //Scene
    free(scene);
    Engine->Scenes->Values[2] = NULL;

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
        case 2:
            unloadScene2(Engine);
            break;
    }

    return 0;
}