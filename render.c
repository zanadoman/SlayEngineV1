/*
Contains the render queue for the object in the game that needs to be rendered.
The order of the render dictates who goes into which layer on the screen.
No one can be in the same layer. The first one is always the backround (bottom layer),
and the last one will be the top layer.
*/

#include "game.h"

uint16 renderBackground(game* Game);
uint16 renderPlatform(game* Game);
uint16 renderProjectile(game* Game);
uint16 renderPlayer(game* Game);

uint16 renderQueue(game* Game)
{
    //Bottom layer
    renderBackground(Game);
    renderPlatform(Game);
    renderProjectile(Game);
    renderPlayer(Game);
    SDL_RenderPresent(Game->Display->Renderer);
    //Top layer

    return 0;
}

uint16 renderBackground(game* Game)
{
    SDL_Rect Object;

    Object.x = 0;
    Object.y = 0;
    Object.w = Game->Display->Width;
    Object.h = Game->Display->Height;

    SDL_SetRenderDrawColor(Game->Display->Renderer, 255, 255, 255, 255);
    SDL_RenderClear(Game->Display->Renderer);
    SDL_RenderCopy(Game->Display->Renderer, Game->TextureBackground, NULL, &Object);

    return 0;
}

uint16 renderPlatform(game* Game)
{
    SDL_Rect Object;

    for (uint64 i = 0; i < Game->Platforms->Length; i++)
    {
        Object.x = (sint32)round(((platform*)Game->Platforms->Values[i])->X);
        Object.y = (sint32)round(((platform*)Game->Platforms->Values[i])->Y);
        Object.w = ((platform*)Game->Platforms->Values[i])->Width;
        Object.h = ((platform*)Game->Platforms->Values[i])->Height;

        SDL_SetRenderDrawColor(Game->Display->Renderer, ((platform*)Game->Platforms->Values[i])->ColorR, ((platform*)Game->Platforms->Values[i])->ColorG, ((platform*)Game->Platforms->Values[i])->ColorB, 255);
        SDL_RenderFillRect(Game->Display->Renderer, &Object);
    }

    return 0;
}

uint16 renderProjectile(game* Game)
{
    SDL_Rect Object;

    for (uint64 i = 0; i < Game->Projectiles->Length; i++)
    {
        Object.x = (sint32)round(((projectile*)Game->Projectiles->Values[i])->X);
        Object.y = (sint32)round(((projectile*)Game->Projectiles->Values[i])->Y);
        Object.w = ((projectile*)Game->Projectiles->Values[i])->Width;
        Object.h = ((projectile*)Game->Projectiles->Values[i])->Height;

        SDL_SetRenderDrawColor(Game->Display->Renderer, ((projectile*)Game->Projectiles->Values[i])->ColorR, ((projectile*)Game->Projectiles->Values[i])->ColorG, ((projectile*)Game->Projectiles->Values[i])->ColorB, 255);
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


    if (Game->Player->Facing == 1)
    {
        SDL_RenderCopy(Game->Display->Renderer, Game->Player->TextureRight, NULL, &Object);
    }
    else
    {
        SDL_RenderCopy(Game->Display->Renderer, Game->Player->TextureLeft, NULL, &Object);
    }

    return 0;
}
