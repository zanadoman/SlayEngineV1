#include "game.h"

uint16 loadTextures(game* Game)
{
    SDL_Surface* surface;

    surface = IMG_Load("assets/player.png");
    if (surface == NULL)
    {
        printf("ERROR Cannot find player.png\n");
        SDL_Quit();
        return 1;
    }
    Game->Player->Texture = SDL_CreateTextureFromSurface(Game->Display->Renderer, surface);
    SDL_FreeSurface(surface);

    return 0;
}