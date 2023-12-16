#include "../game.h"

uint8 updateScene2(slayEngine* Engine, scene2* Scene)
{
    //1
    if (updatePause(Engine, Scene->Pause, &Scene->paused) || Scene->paused)
    {
        slayMouseRelative(false);

        return 1;
    }
    else
    {
        slayMouseRelative(true);
    }
    //2
    updatePlayer(Engine, Scene->Player, Scene->Platforms, NULL);
    //3

    return 0;
}

uint8 renderScene2(slayEngine* Engine, scene2* Scene)
{
    //Background
    slayRenderTexture(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, 0, slayFlipNONE, Scene->TextureBackground, 255, 255, 255, 255);

    //Hint
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Movement: A/D", -150, -100, 1, 0, slayFlipNONE, 0.5, 0, 0, 0, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Jump: SPACE", -150, -70, 1, 0, slayFlipNONE, 0.5, 0, 0, 0, 255);

    //Platforms
    for (uint8 i = 0; i < Scene->Platforms->Length; i++)
    {
        slayRender3DTextureCamera(Engine, ((platform*)Scene->Platforms->Values[i])->X, ((platform*)Scene->Platforms->Values[i])->Y, ((platform*)Scene->Platforms->Values[i])->Width, ((platform*)Scene->Platforms->Values[i])->Height, 0, slayFlipNONE, 1.02, 0.04, 0.005, Scene->TexturePlatform, 255, 255, 255, 255);
    }

    //Player
    renderPlayer(Engine, Scene->Player);

    //Pause
    if (Scene->paused)
    {
        renderPause(Engine, Scene->Pause);
    }

    //FrameTime
    renderFrameTime(Engine);

    return 0;
}

uint8 loadScene2(slayEngine* Engine)
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
    scene->TextureBackground = slayLoadTexture(Engine, "assets/level/background.png");
    scene->TexturePlatform = slayLoadTexture(Engine, "assets/level/platform.png");
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
    scene->Player = newPlayer(Engine, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE, 0);

    scene->Player->X = 367;
    scene->Player->Y = 186;

    scene->Player->MinX = -1000000;
    scene->Player->MaxX = 1000000;
    scene->Player->MinY = -1000000;
    scene->Player->MaxY = 1000000;

    slaySetCamera(Engine, &scene->Player->X, &scene->Player->Y, 33, 32, -960, -520, 1.5);

    //Scene
    Engine->CurrentScene = 2;

    return 0;
}

uint8 unloadScene2(slayEngine* Engine)
{
    scene2* scene;
    array save;

    scene = Engine->Scenes->Values[2];

    //Pause
    destroyPause(scene->Pause);

    //Level
    slayUnloadTexture(scene->TextureBackground);
    slayUnloadTexture(scene->TexturePlatform);
    destroyPlatforms(scene->Platforms);

    //Player
    destroyPlayer(scene->Player);

    //Scene
    free(scene);
    Engine->Scenes->Values[2] = NULL;

    return 0;
}