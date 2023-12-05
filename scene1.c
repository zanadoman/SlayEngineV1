#include "game.h"

uint16 updateScene1(slayEngine* Engine, scene1* Scene)
{
    //1
    if (updatePause(Engine, Scene->Pause, &Scene->paused))
    {
        return 2;
    }
    if (Scene->paused)
    {
        return 1;
    }
    //2
    slayThreadStart(Engine, 0, updatePlayerThread);
    slayThreadStart(Engine, 1, updateProjectileThread);
    slayThreadWaitExit(Engine, 0);
    slayThreadWaitExit(Engine, 1);
    //3

    return 0;
}

uint16 renderScene1(slayEngine* Engine, scene1* Scene)
{
    //Background
    slayRenderTexture(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, 0, slayFlipNONE, Scene->TextureBackground, 255);

    //Mountains
    for (double i = 0; i < 5; i++)
    {
        slayRenderTextureCamera(Engine, -3560 + 1583 * i, -1000, 1584, 3312, 0, slayFlipNONE, 0.2, Scene->TextureMountain, 255);
    }

    //Hint
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Movement: A/D", -150, 300, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Jump: SPACE", -150, 330, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Shoot: LMB", -150, 360, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);

    //Shrooms
    slayRenderTextureCamera(Engine, 210, 320, 32, 30, 0, slayFlipNONE, 0.98, Scene->TextureShroom, 255);
    slayRenderTextureCamera(Engine, 550, 120, 32, 30, 0, slayFlipNONE, 0.98, Scene->TextureShroom, 255);

    //Platforms
    for (uint64 i = 0; i < Scene->Platforms->Length; i++)
    {
        slayRender3DTextureCamera(Engine, ((platform*)Scene->Platforms->Values[i])->X, ((platform*)Scene->Platforms->Values[i])->Y, ((platform*)Scene->Platforms->Values[i])->Width, ((platform*)Scene->Platforms->Values[i])->Height, 0, slayFlipNONE, 0.98, 0.04, 0.005, Scene->TexturePlatform, 255);
    }

    //Projectiles
    for (uint64 i = 0; i < Scene->Projectiles->Length; i++)
    {
        slayRenderTextureCamera(Engine, ((projectile*)Scene->Projectiles->Values[i])->X, ((projectile*)Scene->Projectiles->Values[i])->Y, ((projectile*)Scene->Projectiles->Values[i])->Width, ((projectile*)Scene->Projectiles->Values[i])->Height, ((projectile*)Scene->Projectiles->Values[i])->Angle, slayFlipNONE, 1, ((game*)Engine->Game)->TextureProjectile, 255);
    }

    //Player
    renderPlayer(Engine, Scene->Player);

    //Bush
    slayRenderTextureCamera(Engine, 700, 508, 69, 42, 0, slayFlipNONE, 1.02, Scene->TextureBush, 255);

    //Pause
    if (Scene->paused)
    {
        renderPause(Engine, Scene->Pause);
    }

    //FrameTime
    string text = strNew();
    UINTtoSTR(Engine->DeltaTime, text);
    strConcat(text, 3, "Frametime: ", text->String, "ms");
    slayRenderText(Engine, ((game*)Engine->Game)->FontCrazyPixel, text->String, 10, -10, 0.75, 0, slayFlipNONE, 0, 0, 0, 255);
    strPurge(text);

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
    scene->TextureBackground = slayLoadTexture(Engine, "assets/level/background.png");
    scene->TextureMountain = slayLoadTexture(Engine, "assets/level/mountain.png");
    scene->TextureShroom = slayLoadTexture(Engine, "assets/level/shroom.png");
    scene->TextureBush = slayLoadTexture(Engine, "assets/level/bush.png");
    scene->TexturePlatform = slayLoadTexture(Engine, "assets/level/platform.png");
    scene->Platforms = arrNew(5);
    scene->Platforms->Values[0] = newPlatform(-200, 550, 1200, 360);
    scene->Platforms->Values[1] = newPlatform(300, 450, 200, 30);
    scene->Platforms->Values[2] = newPlatform(200, 350, 100, 30);
    scene->Platforms->Values[3] = newPlatform(350, 250, 100, 30);
    scene->Platforms->Values[4] = newPlatform(500, 150, 100, 30);
    
    //Player
    scene->Player = newPlayer(Engine, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE, SDL_SCANCODE_LMB);

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
        scene->Player->X = 367;
        scene->Player->Y = 386;
    }
    arrPurge(save);

    scene->Player->MinX = -200;
    scene->Player->MaxX = 1000;
    scene->Player->MinY = -500;
    scene->Player->MaxY = 600;

    slaySetCamera(Engine, &scene->Player->X, &scene->Player->Y, 33, 32, -960, -800, 1.5);
    
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
    uint16 destroyPause(pause* Pause);

    //Level
    slayUnloadTexture(scene->TextureBackground);
    slayUnloadTexture(scene->TextureMountain);
    slayUnloadTexture(scene->TextureShroom);
    slayUnloadTexture(scene->TextureBush);
    slayUnloadTexture(scene->TexturePlatform);
    uint16 destroyPlatforms(array Platforms);

    //Player
    destroyPlayer(scene->Player);

    //Projectiles
    destroyProjectiles(scene->Projectiles);

    //Scene
    free(scene);
    Engine->Scenes->Values[1] = NULL;

    return 0;
}

