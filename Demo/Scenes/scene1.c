#include "../game.h"

uint8 updateScene1(slayEngine* Engine, scene1* Scene)
{
    //1
    if (updatePause(Engine, Scene->Pause, &Scene->paused) || Scene->paused)
    {
        return 1;
    }
    //2
    slayThreadStart(Engine, PLAYER, updatePlayerThread);
    slayThreadStart(Engine, EAGLE, updateEagleThread);
    slayThreadStart(Engine, PROJECTILE, updateProjectileThread);
    slayThreadWaitExit(Engine, PLAYER);
    slayThreadWaitExit(Engine, EAGLE);
    slayThreadWaitExit(Engine, PROJECTILE);
    //3

    return 0;
}

uint8 renderScene1(slayEngine* Engine, scene1* Scene)
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
    for (uint8 i = 0; i < Scene->Platforms->Length; i++)
    {
        slayRender3DTextureCamera(Engine, ((platform*)Scene->Platforms->Values[i])->X, ((platform*)Scene->Platforms->Values[i])->Y, ((platform*)Scene->Platforms->Values[i])->Width, ((platform*)Scene->Platforms->Values[i])->Height, 0, slayFlipNONE, 1.02, 0.04, 0.005, Scene->TexturePlatform, 255);
    }

    //Projectiles
    for (uint16 i = 0; i < Scene->Projectiles->Length; i++)
    {
        slayRenderTextureCamera(Engine, ((projectile*)Scene->Projectiles->Values[i])->X, ((projectile*)Scene->Projectiles->Values[i])->Y, ((projectile*)Scene->Projectiles->Values[i])->Width, ((projectile*)Scene->Projectiles->Values[i])->Height, ((projectile*)Scene->Projectiles->Values[i])->Angle, slayFlipNONE, 1, ((game*)Engine->Game)->TextureProjectile, 255);
    }

    //Eagle
    renderEagle(Engine, Scene->Eagle);

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
    renderFrameTime(Engine);

    return 0;
}

uint8 loadScene1(slayEngine* Engine)
{
    scene1* scene;
    slayJSON* save;

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

    //Sounds
    scene->SoundFire = slayLoadSound("assets/player_fire.wav");
    
    //Player
    scene->Player = newPlayer(Engine, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE, SDL_SCANCODE_LMB);

    save = slayLoadJSON("saves/scene1_player.json");
    if (save != NULL)
    {
        scene->Player->X = slayGetJSONKey(save, "X")->ValueNumber;
        scene->Player->Y = slayGetJSONKey(save, "Y")->ValueNumber;
        scene->Player->Facing = slayGetJSONKey(save, "Facing")->ValueNumber;
        
        slayUnloadJSON(save);
    }
    else
    {
        scene->Player->X = 367;
        scene->Player->Y = 386;
        scene->Player->Facing = 1;
    }

    scene->Player->MinX = -200;
    scene->Player->MaxX = 1000;
    scene->Player->MinY = -500;
    scene->Player->MaxY = 600;

    slaySetCamera(Engine, &scene->Player->X, &scene->Player->Y, 33, 32, -960, -800, 1.5);

    //Eagle
    scene->Eagle = newEagle(Engine);
    scene->Eagle->X = 370;
    scene->Eagle->Y = 50;
    scene->Eagle->MinX = -200;
    scene->Eagle->MaxX = 1000;
    scene->Eagle->MinY = -500;
    scene->Eagle->MaxY = 600;
    
    //Projectiles
    scene->Projectiles = arrNew(0);

    //Scene
    Engine->CurrentScene = 1;

    return 0;
}

uint8 unloadScene1(slayEngine* Engine)
{
    scene1* scene;
    slayJSON* save;

    scene = Engine->Scenes->Values[1];

    //Save
    save = slayNewJSON();
    
    slayAddJSONKeyNumber(save, "X", scene->Player->X);
    slayAddJSONKeyNumber(save, "Y", scene->Player->Y);
    slayAddJSONKeyNumber(save, "Facing", scene->Player->Facing);

    slaySaveJSON(save, "saves/scene1_player.json");
    slayUnloadJSON(save);

    //Pause
    destroyPause(scene->Pause);

    //Level
    slayUnloadTexture(scene->TextureBackground);
    slayUnloadTexture(scene->TextureMountain);
    slayUnloadTexture(scene->TextureShroom);
    slayUnloadTexture(scene->TextureBush);
    slayUnloadTexture(scene->TexturePlatform);
    destroyPlatforms(scene->Platforms);

    //Sounds
    slayUnloadSound(scene->SoundFire);

    //Player
    destroyPlayer(scene->Player);

    //Eagle
    destroyEagle(scene->Eagle);

    //Projectiles
    destroyProjectiles(scene->Projectiles);

    //Scene
    free(scene);
    Engine->Scenes->Values[1] = NULL;

    return 0;
}

