#include "game.h"

uint16 renderBackground(game* Game);
uint16 renderHint(game* Game);
uint16 renderPlatform(game* Game);
uint16 renderProjectile(game* Game);
uint16 renderPlayer(game* Game);
uint16 renderFPSCounter(game* Game);

uint16 renderQueue(game* Game)
{
    slayRenderStart(Game->Display);

    renderBackground(Game);
    renderHint(Game);
    renderPlatform(Game);
    renderProjectile(Game);
    renderPlayer(Game);
    renderFPSCounter(Game);
    
    slayRenderEnd(Game->Display);

    return 0;
}

uint16 renderBackground(game* Game)
{
    slayRenderTexture(Game->Display, 0, 0, Game->Display->Width, Game->Display->Height, Game->TextureBackground);

    return 0;
}

uint16 renderHint(game* Game)
{
    slayRenderTextCamera(Game->Display, Game->FontCrazyPixel, "Movement: Left/Right arrow", -150, -100, 1, 0.5, 255, 255, 255, 255, Game->Camera);
    slayRenderTextCamera(Game->Display, Game->FontCrazyPixel, "Jump: Up arrow", -150, -70, 1, 0.5, 255, 255, 255, 255, Game->Camera);
    slayRenderTextCamera(Game->Display, Game->FontCrazyPixel, "Shoot: LCTRL", -150, -40, 1, 0.5, 255, 255, 255, 255, Game->Camera);

    return 0;
}

uint16 renderPlatform(game* Game)
{
    for (uint64 i = 0; i < Game->Platforms->Length; i++)
    {
        slayRender3DTextureCamera(Game->Display, ((platform*)Game->Platforms->Values[i])->X, ((platform*)Game->Platforms->Values[i])->Y, ((platform*)Game->Platforms->Values[i])->Width, ((platform*)Game->Platforms->Values[i])->Height, 0.95, 1.05, 0.001, Game->TexturePlatform, Game->Camera);
    }

    return 0;
}

uint16 renderProjectile(game* Game)
{
    for (uint64 i = 0; i < Game->Projectiles->Length; i++)
    {
        slayRenderColorCamera(Game->Display, ((projectile*)Game->Projectiles->Values[i])->X, ((projectile*)Game->Projectiles->Values[i])->Y, ((projectile*)Game->Projectiles->Values[i])->Width, ((projectile*)Game->Projectiles->Values[i])->Height, 1, ((projectile*)Game->Projectiles->Values[i])->ColorR, ((projectile*)Game->Projectiles->Values[i])->ColorG, ((projectile*)Game->Projectiles->Values[i])->ColorB, 255, Game->Camera);
    }

    return 0;
}

uint16 renderPlayer(game* Game)
{
    if (Game->Player->Facing == 1)
    {
        slayRenderTextureCamera(Game->Display, Game->Player->X, Game->Player->Y, Game->Player->Width, Game->Player->Height, 1, Game->Player->TextureRight, Game->Camera);
    }
    else
    {
        slayRenderTextureCamera(Game->Display, Game->Player->X, Game->Player->Y, Game->Player->Width, Game->Player->Height, 1, Game->Player->TextureLeft, Game->Camera);
    }

    return 0;
}

uint16 renderFPSCounter(game* Game)
{
    string text;

    text = strNew();
    UINTtoSTR(Game->DeltaTime, text);
    strConcat(text, 3, "Frametime: ", text->String, "ms");
    slayRenderText(Game->Display, Game->FontCrazyPixel, text->String, 10, -10, 0.75, 255, 255, 255, 255);
    strPurge(text);

    return 0;
}
