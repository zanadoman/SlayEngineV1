#include "game.h"

uint16 renderBackground(game* Game);
uint16 renderHint(game* Game);
uint16 renderPlatform(game* Game);
uint16 renderProjectile(game* Game);
uint16 renderPlayer(game* Game);
uint16 renderFrameTime(game* Game);

uint16 renderQueue(game* Game)
{
    slayRenderStart(Game->Engine);

    renderBackground(Game);
    renderHint(Game);
    renderPlatform(Game);
    renderProjectile(Game);
    renderPlayer(Game);
    renderFrameTime(Game);
    
    slayRenderEnd(Game->Engine);

    return 0;
}

uint16 renderBackground(game* Game)
{
    slayRenderTexture(Game->Engine, 0, 0, Game->Engine->Display->Width, Game->Engine->Display->Height, Game->TextureBackground);

    return 0;
}

uint16 renderHint(game* Game)
{
    slayRenderTextCamera(Game->Engine, Game->FontCrazyPixel, "Movement: Left/Right arrow", -150, -100, 1, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Game->Engine, Game->FontCrazyPixel, "Jump: Up arrow", -150, -70, 1, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Game->Engine, Game->FontCrazyPixel, "Shoot: LCTRL", -150, -40, 1, 0.5, 255, 255, 255, 255);

    return 0;
}

uint16 renderPlatform(game* Game)
{
    for (uint64 i = 0; i < Game->Platforms->Length; i++)
    {
        slayRender3DTextureCamera(Game->Engine, ((platform*)Game->Platforms->Values[i])->X, ((platform*)Game->Platforms->Values[i])->Y, ((platform*)Game->Platforms->Values[i])->Width, ((platform*)Game->Platforms->Values[i])->Height, 0.95, 0.1, 0.005, Game->TexturePlatform);
    }

    return 0;
}

uint16 renderProjectile(game* Game)
{
    for (uint64 i = 0; i < Game->Projectiles->Length; i++)
    {
        slayRenderColorCamera(Game->Engine, ((projectile*)Game->Projectiles->Values[i])->X, ((projectile*)Game->Projectiles->Values[i])->Y, ((projectile*)Game->Projectiles->Values[i])->Width, ((projectile*)Game->Projectiles->Values[i])->Height, 1, ((projectile*)Game->Projectiles->Values[i])->ColorR, ((projectile*)Game->Projectiles->Values[i])->ColorG, ((projectile*)Game->Projectiles->Values[i])->ColorB, 255);
    }

    return 0;
}

uint16 renderPlayer(game* Game)
{
    if (Game->Player->Facing == 1)
    {
        slayRenderTextureCamera(Game->Engine, Game->Player->X, Game->Player->Y, Game->Player->Width, Game->Player->Height, 1, Game->Player->TextureRight);
    }
    else
    {
        slayRenderTextureCamera(Game->Engine, Game->Player->X, Game->Player->Y, Game->Player->Width, Game->Player->Height, 1, Game->Player->TextureLeft);
    }

    return 0;
}

uint16 renderFrameTime(game* Game)
{
    string text;

    text = strNew();
    UINTtoSTR(Game->Engine->DeltaTime, text);
    strConcat(text, 3, "Frametime: ", text->String, "ms");
    slayRenderText(Game->Engine, Game->FontCrazyPixel, text->String, 10, -10, 0.75, 255, 255, 255, 255);
    strPurge(text);

    return 0;
}
