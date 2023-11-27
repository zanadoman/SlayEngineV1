#include "game.h"

uint16 renderBackground(game* Game);
uint16 renderPlatform(game* Game);
uint16 renderProjectile(game* Game);
uint16 renderPlayer(game* Game);

uint16 renderQueue(game* Game)
{
    slayRenderStart(Game->Display, 255, 255, 255);
    renderBackground(Game);
    renderPlatform(Game);
    renderProjectile(Game);
    renderPlayer(Game);
    slayRenderEnd(Game->Display);

    return 0;
}

uint16 renderBackground(game* Game)
{
    slayRenderTexture(Game->Display, 0, 0, Game->Display->Width, Game->Display->Height, Game->TextureBackground);

    return 0;
}

uint16 renderPlatform(game* Game)
{
    for (uint64 i = 0; i < Game->Platforms->Length; i++)
    {
        slayRenderColorCamera(Game->Display, ((platform*)Game->Platforms->Values[i])->X, ((platform*)Game->Platforms->Values[i])->Y, ((platform*)Game->Platforms->Values[i])->Width, ((platform*)Game->Platforms->Values[i])->Height, ((platform*)Game->Platforms->Values[i])->ColorR, ((platform*)Game->Platforms->Values[i])->ColorG, ((platform*)Game->Platforms->Values[i])->ColorB, 255, Game->Camera);
    }

    return 0;
}

uint16 renderProjectile(game* Game)
{
    for (uint64 i = 0; i < Game->Projectiles->Length; i++)
    {
        slayRenderColorCamera(Game->Display, ((projectile*)Game->Projectiles->Values[i])->X, ((projectile*)Game->Projectiles->Values[i])->Y, ((projectile*)Game->Projectiles->Values[i])->Width, ((projectile*)Game->Projectiles->Values[i])->Height, ((projectile*)Game->Projectiles->Values[i])->ColorR, ((projectile*)Game->Projectiles->Values[i])->ColorG, ((projectile*)Game->Projectiles->Values[i])->ColorB, 255, Game->Camera);
    }

    return 0;
}

uint16 renderPlayer(game* Game)
{
    if (Game->Player->Facing == 1)
    {
        slayRenderTextureCamera(Game->Display, Game->Player->X, Game->Player->Y, Game->Player->Width, Game->Player->Height, Game->Player->TextureRight, Game->Camera);
    }
    else
    {
        slayRenderTextureCamera(Game->Display, Game->Player->X, Game->Player->Y, Game->Player->Width, Game->Player->Height, Game->Player->TextureLeft, Game->Camera);
    }

    return 0;
}
