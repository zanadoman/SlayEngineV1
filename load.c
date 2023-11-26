#include "game.h"

uint16 loadTextures(game* Game)
{
    SDL_Surface* surface;

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