#include "../game.h"

uint8 updateScene1(slayEngine* Engine)
{
    scene1* Scene;

    Scene = Engine->Scenes->Values[1];

    //1
    if (updatePause(Engine, Scene->Pause, &Scene->paused) || Scene->paused)
    {
        return 1;
    }

    //2
    slayThreadStart(Engine, actPLAYER, updatePlayerThread);
    slayThreadStart(Engine, actEAGLE, updateEagleThread);
    //slayThreadStart(Engine, actPROJECTILE, updateProjectileThread);
    slayThreadWaitExit(Engine, actPLAYER);
    slayThreadWaitExit(Engine, actEAGLE);
    //slayThreadWaitExit(Engine, actPROJECTILE);
    //3
    slayResolveCollisionLayer(Scene->PhysicsLayer, 255);

    return 0;
}

uint8 renderScene1(slayEngine* Engine)
{
    game* Game;
    scene1* Scene;

    Game = Engine->Game;
    Scene = Engine->Scenes->Values[1];

    //Background
    slayRenderTexture(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, 0, slayFlipNONE, Game->Textures->levelBackground, 255, 255, 255, 255);

    //Mountains
    for (double i = 0; i < 5; i++)
    {
        slayRenderTextureCamera(Engine, -3560 + 1583 * i, -1000, 1584, 3312, 0, slayFlipNONE, 0.2, Game->Textures->levelMountain, 255, 255, 255, 255);
    }

    //Hint
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Movement: A/D", -150, 300, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Jump: SPACE", -150, 330, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Shoot: LMB", -150, 360, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);

    //Shrooms
    slayRenderTextureCamera(Engine, 210, 320, 32, 30, 0, slayFlipNONE, 0.98, Game->Textures->levelShroom, 255, 255, 255, 255);
    slayRenderTextureCamera(Engine, 550, 120, 32, 30, 0, slayFlipNONE, 0.98, Game->Textures->levelShroom, 255, 255, 255, 255);

    //Platforms
    for (uint8 i = 0; i < Scene->Platforms->Length; i++)
    {
        slayRender3DTextureCamera(Engine, ((platform*)Scene->Platforms->Values[i])->X, ((platform*)Scene->Platforms->Values[i])->Y, ((platform*)Scene->Platforms->Values[i])->Width, ((platform*)Scene->Platforms->Values[i])->Height, 0, slayFlipNONE, 1.02, 0.04, 0.005, Game->Textures->levelPlatform, 255, 255, 255, 255);
        slayRenderHitboxCamera(Engine, ((platform*)Scene->Platforms->Values[i])->Hitbox, 1, 255, 0, 0, 128);
    }

    //Projectiles
    for (uint16 i = 0; i < Scene->Projectiles->Length; i++)
    {
        slayRenderTextureCamera(Engine, ((projectile*)Scene->Projectiles->Values[i])->X, ((projectile*)Scene->Projectiles->Values[i])->Y, ((projectile*)Scene->Projectiles->Values[i])->Width, ((projectile*)Scene->Projectiles->Values[i])->Height, ((projectile*)Scene->Projectiles->Values[i])->Angle, slayFlipNONE, 1, Game->Textures->projectile, 255, 255, 255, 255);
    }

    //Eagle
    renderEagle(Engine, Scene->Eagle);

    //Player
    renderPlayer(Engine, Scene->Player);

    //Bush
    slayRenderTextureCamera(Engine, 700, 508, 69, 42, 0, slayFlipNONE, 1.02, Game->Textures->levelBush, 255, 255, 255, 255);

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
    scene->Platforms = arrNew(5);
    scene->Platforms->Values[0] = newPlatform(-200, 550, 1200, 360);
    scene->Platforms->Values[1] = newPlatform(300, 450, 200, 30);
    scene->Platforms->Values[2] = newPlatform(200, 350, 100, 30);
    scene->Platforms->Values[3] = newPlatform(350, 250, 100, 30);
    scene->Platforms->Values[4] = newPlatform(500, 150, 100, 30);

    //Player
    scene->Player = newPlayer(Engine, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE, SDL_SCANCODE_LMB);

    save = slayLoadJSON("saves/scene1_player.json");
    if (save != NULL)
    {
        scene->Player->X = slayGetJSONKey(save, "X")->ValueNumber;
        scene->Player->Y = slayGetJSONKey(save, "Y")->ValueNumber;
        scene->Player->Facing = slayGetJSONKey(save, "Facing")->ValueNumber;
        
        slayDestroyJSON(save);
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

    slaySetCamera(Engine, &scene->Player->X, &scene->Player->Y, scene->Player->CenterX, scene->Player->CenterY, -950, -800, 1.5);

    //Eagle
    scene->Eagle = newEagle(Engine);
    scene->Eagle->X = 370;
    scene->Eagle->Y = 50;
    scene->Eagle->MinX = -200;
    scene->Eagle->MinY = -500;
    scene->Eagle->MaxX = 1000;
    scene->Eagle->MaxY = 600;
    
    //Projectiles
    scene->Projectiles = arrNew(0);

    //Collision layer
    scene->PhysicsLayer = arrNew(0);
    for (uint8 i = 0; i < scene->Platforms->Length; i++)
    {
        arrInsert(scene->PhysicsLayer, scene->PhysicsLayer->Length, ((platform*)scene->Platforms->Values[i])->Hitbox);
        if (i == 3)
        {
            arrInsert(scene->PhysicsLayer, scene->PhysicsLayer->Length, scene->Player->Hitbox);
        }
    }
    arrInsert(scene->PhysicsLayer, scene->PhysicsLayer->Length, scene->Eagle->Hitbox);

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
    slayDestroyJSON(save);

    //Pause
    destroyPause(scene->Pause);

    //Level
    destroyPlatforms(scene->Platforms);

    //Player
    destroyPlayer(scene->Player);

    //Eagle
    destroyEagle(scene->Eagle);

    //Projectiles
    //destroyProjectiles(scene->Projectiles);

    //Physics layer
    free(scene->PhysicsLayer);

    //Scene
    free(scene);
    Engine->Scenes->Values[1] = NULL;

    return 0;
}
