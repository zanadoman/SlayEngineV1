/*
Initializes the game struct.
Loads assets into the game.
*/

#include "game.h"

uint16 loadRequiredElements(game* Game);
uint16 loadAdditionalElements(game* Game);
uint16 loadTextures(game* Game);

uint16 loadGame(game* Game)
{
    loadRequiredElements(Game);
    loadAdditionalElements(Game);

    loadTextures(Game);

    return 0;
}

uint16 loadRequiredElements(game* Game)
{
    //Creating the game window
    Game->Display = slayNew("SlayEngineV1 Demo", 800, 600);

    //Initializing the previous tick to 0
    Game->DisplayPrevTick = 0;
    
    //Threads & Thread init
    Game->Threads = arrNew(2);
    for (uint64 i = 0; i < Game->Threads->Length; i++)
    {
        Game->Threads->Values[i] = malloc(sizeof(pthread_t));
    }

    return 0;
}

uint16 loadAdditionalElements(game* Game)
{
    //Creating platforms
    Game->Platforms = arrNew(5);
    Game->Platforms->Values[0] = newPlatform(1800, 2550, 1200, 500, 24, 24, 48);
    Game->Platforms->Values[1] = newPlatform(2300, 2450, 200, 30, 24, 24, 48);
    Game->Platforms->Values[2] = newPlatform(2200, 2350, 100, 30, 24, 24, 48);
    Game->Platforms->Values[3] = newPlatform(2350, 2250, 100, 30, 24, 24, 48);
    Game->Platforms->Values[4] = newPlatform(2500, 2150, 100, 30, 24, 24, 48);

    //Creating the player
    Game->Player = newPlayer();
    Game->Player->X = 2386;
    Game->Player->Y = 2410;
    Game->Player->MinX = 1800;
    Game->Player->MaxX = 3000;

    //Init the camera
    Game->Camera = slayNewCamera(&Game->Player->X, &Game->Player->Y, -386, -400);

    //Initializing the array for projectiles
    Game->Projectiles = arrNew(0);

    return 0;
}

uint16 loadTextures(game* Game)
{
    //Background texture
    Game->TextureBackground = slayLoadTexture(Game->Display, "assets/background.jpg");

    //Player textures
    Game->Player->TextureLeft = slayLoadTexture(Game->Display, "assets/player_left.png");
    Game->Player->TextureRight = slayLoadTexture(Game->Display, "assets/player_right.png");

    return 0;
}