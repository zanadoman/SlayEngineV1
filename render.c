#include "game.h"

uint16 renderScene0(slayEngine* Engine, scene0* Scene);
uint16 renderBackground(slayEngine* Engine);
uint16 renderHint(slayEngine* Engine);
uint16 renderPlatform(slayEngine* Engine);
uint16 renderProjectile(slayEngine* Engine);
uint16 renderPlayer(slayEngine* Engine);
uint16 renderFrameTime(slayEngine* Engine);

uint16 renderQueue(slayEngine* Engine)
{
    slayRenderStart(Engine);

    switch (Engine->CurrentScene)
    {
        case 0:
            renderScene0(Engine, Engine->Scenes->Values[0]);
            break;
    }
    
    slayRenderEnd(Engine);

    return 0;
}

uint16 renderScene0(slayEngine* Engine, scene0* Scene)
{
    //Background
    slayRenderTexture(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, Scene->TextureBackground);

    //Hint
    slayRenderTextCamera(Engine, Scene->FontCrazyPixel, "Movement: Left/Right arrow", -150, -100, 1, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, Scene->FontCrazyPixel, "Jump: Up arrow", -150, -70, 1, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, Scene->FontCrazyPixel, "Shoot: LCTRL", -150, -40, 1, 0.5, 255, 255, 255, 255);

    //Platforms
    for (uint64 i = 0; i < Scene->Platforms->Length; i++)
    {
        slayRender3DTextureCamera(Engine, ((platform*)Scene->Platforms->Values[i])->X, ((platform*)Scene->Platforms->Values[i])->Y, ((platform*)Scene->Platforms->Values[i])->Width, ((platform*)Scene->Platforms->Values[i])->Height, 0.95, 0.1, 0.005, Scene->TexturePlatform);
    }

    //Projectiles
    for (uint64 i = 0; i < Scene->Projectiles->Length; i++)
    {
        slayRenderColorCamera(Engine, ((projectile*)Scene->Projectiles->Values[i])->X, ((projectile*)Scene->Projectiles->Values[i])->Y, ((projectile*)Scene->Projectiles->Values[i])->Width, ((projectile*)Scene->Projectiles->Values[i])->Height, 1, ((projectile*)Scene->Projectiles->Values[i])->ColorR, ((projectile*)Scene->Projectiles->Values[i])->ColorG, ((projectile*)Scene->Projectiles->Values[i])->ColorB, 255);
    }

    //Player
    if (Scene->Player->Facing == 1)
    {
        slayRenderTextureCamera(Engine, Scene->Player->X, Scene->Player->Y, Scene->Player->Width, Scene->Player->Height, 1, Scene->Player->TextureRight);
    }
    else
    {
        slayRenderTextureCamera(Engine, Scene->Player->X, Scene->Player->Y, Scene->Player->Width, Scene->Player->Height, 1, Scene->Player->TextureLeft);
    }

    //FrameTime
    string text;

    text = strNew();
    UINTtoSTR(Engine->DeltaTime, text);
    strConcat(text, 3, "Frametime: ", text->String, "ms");
    slayRenderText(Engine, Scene->FontCrazyPixel, text->String, 10, -10, 0.75, 255, 255, 255, 255);
    strPurge(text);
}
