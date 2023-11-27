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

    //Loading the textures
    if (loadTextures(Game) != 0)
    {
        return 1;
    }

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
    Game->Platforms->Values[0] = newPlatform(1500, 2550, 1800, 500, 32, 32, 64);
    Game->Platforms->Values[1] = newPlatform(2300, 2450, 200, 30, 32, 32, 64);
    Game->Platforms->Values[2] = newPlatform(2200, 2350, 100, 30, 32, 32, 64);
    Game->Platforms->Values[3] = newPlatform(2350, 2250, 100, 30, 32, 32, 64);
    Game->Platforms->Values[4] = newPlatform(2500, 2150, 100, 30, 32, 32, 64);

    //Creating the player
    Game->Player = newPlayer(2386, 2510, 1500, 3300, 0, 0, 1, 28, 40, 0.003, 0.005, 0, 0.003, 0.4, 1.1, 200, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_LCTRL);

    //Init the camera
    Game->Camera = slayNewCamera(&Game->Player->X, &Game->Player->Y, -386, -400);

    //Initializing the array for projectiles
    Game->Projectiles = arrNew(0);

    return 0;
}

uint16 loadTextures(game* Game)
{
    SDL_Surface* surface;

    //Background texture
    surface = IMG_Load("assets/background.jpg");
    if (surface == NULL)
    {
        printf("ERROR Cannot find background.jpg\n");
        SDL_Quit();
        return 1;
    }
    Game->TextureBackground = SDL_CreateTextureFromSurface(Game->Display->Renderer, surface);

    //Player textures
    surface = IMG_Load("assets/player_left.png");
    if (surface == NULL)
    {
        printf("ERROR Cannot find player_left.png\n");
        SDL_Quit();
        return 1;
    }
    Game->Player->TextureLeft = SDL_CreateTextureFromSurface(Game->Display->Renderer, surface);
    surface = IMG_Load("assets/player_right.png");
    if (surface == NULL)
    {
        printf("ERROR Cannot find player_right.png\n");
        SDL_Quit();
        return 1;
    }
    Game->Player->TextureRight = SDL_CreateTextureFromSurface(Game->Display->Renderer, surface);

    SDL_FreeSurface(surface);
    return 0;
}