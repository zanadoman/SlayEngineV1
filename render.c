#include "game.h"

uint16 renderBackground(game* Game);
uint16 renderPlatform(game* Game);
uint16 renderProjectile(game* Game);
uint16 renderPlayer(game* Game);

uint16 renderQueue(game* Game)
{
    renderBackground(Game);
    renderPlatform(Game);
    renderProjectile(Game);
    renderPlayer(Game);
    SDL_RenderPresent(Game->Display->Renderer);

    return 0;
}

uint16 renderBackground(game* Game)
{
    SDL_SetRenderDrawColor(Game->Display->Renderer, 255, 255, 255, 255);
    SDL_RenderClear(Game->Display->Renderer);

    return 0;
}

uint16 renderPlatform(game* Game)
{
    SDL_Rect Object;

    for (uint64 i = 0; Game->Platforms[i] != NULL; i++)
    {
        Object.x = (sint32)round(Game->Platforms[i]->X);
        Object.y = (sint32)round(Game->Platforms[i]->Y);
        Object.w = Game->Platforms[i]->Width;
        Object.h = Game->Platforms[i]->Height;

        SDL_SetRenderDrawColor(Game->Display->Renderer, Game->Platforms[i]->ColorR, Game->Platforms[i]->ColorG, Game->Platforms[i]->ColorB, 255);
        SDL_RenderFillRect(Game->Display->Renderer, &Object);
    }

    return 0;
}

uint16 renderProjectile(game* Game)
{
    SDL_Rect Object;

    for (uint64 i = 0; Game->Projectiles[i] != NULL; i++)
    {
        Object.x = (sint32)round(Game->Projectiles[i]->X);
        Object.y = (sint32)round(Game->Projectiles[i]->Y);
        Object.w = Game->Projectiles[i]->Width;
        Object.h = Game->Projectiles[i]->Height;

        SDL_SetRenderDrawColor(Game->Display->Renderer, Game->Projectiles[i]->ColorR, Game->Projectiles[i]->ColorG, Game->Projectiles[i]->ColorB, 255);
        SDL_RenderFillRect(Game->Display->Renderer, &Object);
    }

    return 0;
}

uint16 renderPlayer(game* Game)
{
    SDL_Rect Object;

    Object.x = (sint32)round(Game->Player->X);
    Object.y = (sint32)round(Game->Player->Y);
    Object.w = Game->Player->Width;
    Object.h = Game->Player->Height;
    
    SDL_SetRenderDrawColor(Game->Display->Renderer, Game->Player->ColorR, Game->Player->ColorG, Game->Player->ColorB, 255);
    SDL_RenderFillRect(Game->Display->Renderer, &Object);

    return 0;
}
