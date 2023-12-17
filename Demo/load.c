#include "game.h"

uint8 loadGame(slayEngine* Engine)
{
    game* Game;
    slayJSON* settings;

    Engine->Game = malloc(sizeof(game));
    Game = Engine->Game;
    settings = slayLoadJSON("saves/settings.json");

    Game->FontCrazyPixel = slayLoadFont("assets/crazy-pixel.ttf", 48);
    Game->Volume = slayGetJSONKey(settings, "volume")->ValueNumber;

    //Textures
    Game->Textures = malloc(sizeof(commonTextures));

    Game->Textures->playerJump = slayLoadTexture(Engine, "assets/player/jump.png");
    Game->Textures->playerFall = slayLoadTexture(Engine, "assets/player/fall.png");

    Game->Textures->levelBackground = slayLoadTexture(Engine, "assets/level/background.png");
    Game->Textures->levelMountain = slayLoadTexture(Engine, "assets/level/mountain.png");
    Game->Textures->levelShroom = slayLoadTexture(Engine, "assets/level/shroom.png");
    Game->Textures->levelBush = slayLoadTexture(Engine, "assets/level/bush.png");
    Game->Textures->levelPlatform = slayLoadTexture(Engine, "assets/level/platform.png");
    Game->Textures->levelCrate = slayLoadTexture(Engine, "assets/level/crate.png");

    Game->Textures->projectile = slayLoadTexture(Engine, "assets/projectile.png");

    //Flipbooks
    Game->Flipbooks = malloc(sizeof(commonFlipbooks));

    Game->Flipbooks->playerIdle = slayNewFlipbook(Engine, 150, 4, "assets/player/idle/idle1.png", "assets/player/idle/idle2.png", "assets/player/idle/idle3.png", "assets/player/idle/idle4.png");
    Game->Flipbooks->playerRun = slayNewFlipbook(Engine, 150, 6, "assets/player/run/run1.png", "assets/player/run/run2.png", "assets/player/run/run3.png", "assets/player/run/run4.png", "assets/player/run/run5.png", "assets/player/run/run6.png");
    Game->Flipbooks->playerStunned = slayNewFlipbook(Engine, 150, 2, "assets/player/stunned/stunned1.png", "assets/player/stunned/stunned2.png");

    Game->Flipbooks->eagleFlying = slayNewFlipbook(Engine, 150, 6, "assets/eagle/flying/flying1.png", "assets/eagle/flying/flying2.png", "assets/eagle/flying/flying3.png", "assets/eagle/flying/flying4.png", "assets/eagle/flying/flying3.png", "assets/eagle/flying/flying2.png");
    Game->Flipbooks->eagleDying = slayNewFlipbook(Engine, 150, 7, "assets/eagle/dying/dying1.png", "assets/eagle/dying/dying2.png", "assets/eagle/dying/dying3.png", "assets/eagle/dying/dying4.png", "assets/eagle/dying/dying5.png", "assets/eagle/dying/dying6.png", NULL);

    //Sounds
    Game->Sounds = malloc(sizeof(commonSounds));

    Game->Sounds->gunFire = slayLoadSound("assets/player_fire.wav");

    slayDestroyJSON(settings);

    return 0;
}

uint8 unloadSceneCurrent(slayEngine* Engine)
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