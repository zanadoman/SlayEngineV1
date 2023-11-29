#include "game.h"

uint16 loadRequiredElements(game* Game);
uint16 loadAdditionalElements(game* Game);
uint16 loadTextures(game* Game);
uint16 loadFonts(game* Game);
uint16 loadSounds(game* Game);

uint16 loadGame(game* Game)
{
    loadRequiredElements(Game);
    loadAdditionalElements(Game);

    loadTextures(Game);
    loadFonts(Game);
    loadSounds(Game);

    return 0;
}

uint16 loadRequiredElements(game* Game)
{
    Game->Display = slayNew("SlayEngineV1 Demo", 1920, 1080);

    Game->DisplayPrevTick = 0;
    
    Game->Threads = arrNew(2);
    for (uint64 i = 0; i < Game->Threads->Length; i++)
    {
        Game->Threads->Values[i] = malloc(sizeof(pthread_t));
    }

    Game->Volume = 10;

    return 0;
}

uint16 loadAdditionalElements(game* Game)
{
    Game->Platforms = arrNew(5);
    Game->Platforms->Values[0] = newPlatform(-200, 550, 1200, 180);
    Game->Platforms->Values[1] = newPlatform(300, 450, 200, 30);
    Game->Platforms->Values[2] = newPlatform(200, 350, 100, 30);
    Game->Platforms->Values[3] = newPlatform(350, 250, 100, 30);
    Game->Platforms->Values[4] = newPlatform(500, 150, 100, 30);

    Game->Player = newPlayer();
    Game->Player->X = 386;
    Game->Player->Y = 410;
    Game->Player->MinX = -200;
    Game->Player->MaxX = 1000;

    Game->Camera = slayNewCamera(&Game->Player->X, &Game->Player->Y, 14, 20, -960, -800, 1.5);

    Game->Projectiles = arrNew(0);

    return 0;
}

uint16 loadTextures(game* Game)
{
    Game->TextureBackground = slayLoadTexture(Game->Display, "assets/background.jpg");
    Game->TexturePlatform = slayLoadTexture(Game->Display, "assets/platform.png");

    Game->Player->TextureLeft = slayLoadTexture(Game->Display, "assets/player_left.png");
    Game->Player->TextureRight = slayLoadTexture(Game->Display, "assets/player_right.png");

    return 0;
}

uint16 loadFonts(game* Game)
{
    Game->FontCrazyPixel = slayLoadFont("assets/crazy-pixel.ttf", 48);

    return 0;
}

uint16 loadSounds(game* Game)
{
    Game->Player->SoundFire = slayLoadSound("assets/player_fire.wav");

    return 0;
}