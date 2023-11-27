#include "game.h"

uint16 loadRequiredElements(game* Game);
uint16 loadAdditionalElements(game* Game);
uint16 loadTextures(game* Game);
uint16 loadFonts(game* Game);

uint16 loadGame(game* Game)
{
    loadRequiredElements(Game);
    loadAdditionalElements(Game);

    loadTextures(Game);
    loadFonts(Game);

    return 0;
}

uint16 loadRequiredElements(game* Game)
{
    Game->Display = slayNew("SlayEngineV1 Demo", 800, 600);

    Game->DisplayPrevTick = 0;
    
    Game->Threads = arrNew(2);
    for (uint64 i = 0; i < Game->Threads->Length; i++)
    {
        Game->Threads->Values[i] = malloc(sizeof(pthread_t));
    }

    return 0;
}

uint16 loadAdditionalElements(game* Game)
{
    Game->Platforms = arrNew(5);
    Game->Platforms->Values[0] = newPlatform(1800, 2550, 1200, 500, 24, 24, 48);
    Game->Platforms->Values[1] = newPlatform(2300, 2450, 200, 30, 24, 24, 48);
    Game->Platforms->Values[2] = newPlatform(2200, 2350, 100, 30, 24, 24, 48);
    Game->Platforms->Values[3] = newPlatform(2350, 2250, 100, 30, 24, 24, 48);
    Game->Platforms->Values[4] = newPlatform(2500, 2150, 100, 30, 24, 24, 48);

    Game->Player = newPlayer();
    Game->Player->X = 2386;
    Game->Player->Y = 2410;
    Game->Player->MinX = 1800;
    Game->Player->MaxX = 3000;

    Game->Camera = slayNewCamera(&Game->Player->X, &Game->Player->Y, -386, -400);

    Game->Projectiles = arrNew(0);

    return 0;
}

uint16 loadTextures(game* Game)
{
    Game->TextureBackground = slayLoadTexture(Game->Display, "assets/background.jpg");

    Game->Player->TextureLeft = slayLoadTexture(Game->Display, "assets/player_left.png");
    Game->Player->TextureRight = slayLoadTexture(Game->Display, "assets/player_right.png");

    return 0;
}

uint16 loadFonts(game* Game)
{
    Game->FontCrazyPixel12 = slayLoadFont("assets/crazy-pixel.ttf", 48);

    return 0;
}