#include "game.h"

uint16 renderScene0(slayEngine* Engine, scene0* Scene);

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
    slayRenderTexture(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, 0, slayFlipNone, Scene->TextureBackground);

    //Hint
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Movement: A/D", -150, -100, 1, 0, slayFlipNone, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Jump: SPACE", -150, -70, 1, 0, slayFlipNone, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Shoot: LMB", -150, -40, 1, 0, slayFlipNone, 0.5, 255, 255, 255, 255);

    //Platforms
    for (uint64 i = 0; i < Scene->Platforms->Length; i++)
    {
        slayRender3DTextureCamera(Engine, ((platform*)Scene->Platforms->Values[i])->X, ((platform*)Scene->Platforms->Values[i])->Y, ((platform*)Scene->Platforms->Values[i])->Width, ((platform*)Scene->Platforms->Values[i])->Height, 0, slayFlipNone, 0.95, 0.1, 0.005, Scene->TexturePlatform);
    }

    //Projectiles
    for (uint64 i = 0; i < Scene->Projectiles->Length; i++)
    {
        slayRenderTextureCamera(Engine, ((projectile*)Scene->Projectiles->Values[i])->X, ((projectile*)Scene->Projectiles->Values[i])->Y, ((projectile*)Scene->Projectiles->Values[i])->Width, ((projectile*)Scene->Projectiles->Values[i])->Height, ((projectile*)Scene->Projectiles->Values[i])->Angle, slayFlipNone, 1, ((game*)Engine->Game)->TextureProjectile);
    }

    //Player
    if (Scene->Player->Facing == 1)
    {
        slayRenderTextureCamera(Engine, Scene->Player->X, Scene->Player->Y, Scene->Player->Width, Scene->Player->Height, 0, slayFlipNone, 1, Scene->Player->TextureBase);
    }
    else
    {
        slayRenderTextureCamera(Engine, Scene->Player->X, Scene->Player->Y, Scene->Player->Width, Scene->Player->Height, 0, slayFlipHorizontal, 1, Scene->Player->TextureBase);
    }

    //FrameTime
    string text = strNew();
    UINTtoSTR(Engine->DeltaTime, text);
    strConcat(text, 3, "Frametime: ", text->String, "ms");
    slayRenderText(Engine, ((game*)Engine->Game)->FontCrazyPixel, text->String, 10, -10, 0.75, 0, slayFlipNone, 255, 255, 255, 255);
    strPurge(text);
}
