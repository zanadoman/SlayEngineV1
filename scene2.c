#include "game.h"

uint16 updateScene2(slayEngine* Engine, scene2* Scene)
{
    //1
    if (updatePause(Engine, Scene->Pause, &Scene->paused))
    {
        return 2;
    }
    if (Scene->paused)
    {
        slayMouseRelative(false);
        return 1;
    }
    else
    {
        slayMouseRelative(true);
    }
    //2
    updatePlayer(Engine, Scene->Player, Scene->Platforms);
    //3

    return 0;
}

uint16 renderScene2(slayEngine* Engine, scene2* Scene)
{
    //Background
    slayRenderTexture(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, 0, slayFlipNONE, Scene->TextureBackground, 255);

    //Hint
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Movement: A/D", -150, -100, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Jump: SPACE", -150, -70, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Shoot: LMB", -150, -40, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);

    //Platforms
    for (uint64 i = 0; i < Scene->Platforms->Length; i++)
    {
        slayRender3DTextureCamera(Engine, ((platform*)Scene->Platforms->Values[i])->X, ((platform*)Scene->Platforms->Values[i])->Y, ((platform*)Scene->Platforms->Values[i])->Width, ((platform*)Scene->Platforms->Values[i])->Height, 0, slayFlipNONE, 0.95, 0.1, 0.005, Scene->TexturePlatform, 255);
    }

    //Player
    if (Scene->Player->Facing == 1)
    {
        slayRenderTextureCamera(Engine, Scene->Player->X, Scene->Player->Y, Scene->Player->Width, Scene->Player->Height, 0, slayFlipNONE, 1, Scene->Player->TextureBase, 255);
    }
    else
    {
        slayRenderTextureCamera(Engine, Scene->Player->X, Scene->Player->Y, Scene->Player->Width, Scene->Player->Height, 0, slayFlipHORIZONTAL, 1, Scene->Player->TextureBase, 255);
    }

    //Pause
    if (Scene->paused)
    {
        slayRenderColor(Engine, Scene->Pause->X, Scene->Pause->Y, Scene->Pause->Width, Scene->Pause->Height, Scene->Pause->ColorR, Scene->Pause->ColorG, Scene->Pause->ColorB, Scene->Pause->ColorA);

        for (uint64 i = 0; i < Scene->Pause->Buttons->Length; i++)
        {
            slayRenderTexture(Engine, ((button*)Scene->Pause->Buttons->Values[i])->X, ((button*)Scene->Pause->Buttons->Values[i])->Y, ((button*)Scene->Pause->Buttons->Values[i])->Width, ((button*)Scene->Pause->Buttons->Values[i])->Height, 0, slayFlipNONE, ((button*)Scene->Pause->Buttons->Values[i])->TextureCurrent, 255);
        }
    }

    //FrameTime
    string text = strNew();
    UINTtoSTR(Engine->DeltaTime, text);
    strConcat(text, 3, "Frametime: ", text->String, "ms");
    slayRenderText(Engine, ((game*)Engine->Game)->FontCrazyPixel, text->String, 10, -10, 0.75, 0, slayFlipNONE, 255, 255, 255, 255);
    strPurge(text);

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
    scene->Player = newPlayer(Engine, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, 0);

    scene->Player->X = 386;
    scene->Player->Y = 210;

    scene->Player->MinX = -1000000;
    scene->Player->MaxX = 1000000;
    scene->Player->MinY = -1000000;
    scene->Player->MaxY = 1000000;

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