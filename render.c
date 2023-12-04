#include "game.h"

uint16 renderScene0(slayEngine* Engine, scene0* Scene);
uint16 renderScene1(slayEngine* Engine, scene1* Scene);
uint16 renderScene2(slayEngine* Engine, scene2* Scene);

uint16 renderQueue(slayEngine* Engine)
{
    slayRenderStart(Engine);

    switch (Engine->CurrentScene)
    {
        case 0:
            renderScene0(Engine, Engine->Scenes->Values[0]);
            break;
        case 1:
            renderScene1(Engine, Engine->Scenes->Values[1]);
            break;
        case 2:
            renderScene2(Engine, Engine->Scenes->Values[2]);
            break;
    }
    
    slayRenderEnd(Engine);

    return 0;
}

uint16 renderScene0(slayEngine* Engine, scene0* Scene)
{
    //Background
    slayRenderColor(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, Scene->ColorR, Scene->ColorG, Scene->ColorB, 255);

    //Button
    for (uint64 i = 0; i < Scene->Buttons->Length; i++)
    {
        slayRenderTexture(Engine, ((button*)Scene->Buttons->Values[i])->X, ((button*)Scene->Buttons->Values[i])->Y, ((button*)Scene->Buttons->Values[i])->Width, ((button*)Scene->Buttons->Values[i])->Height, 0, slayFlipNONE, ((button*)Scene->Buttons->Values[i])->TextureCurrent, 255);
    }

    return 0;
}

uint16 renderScene1(slayEngine* Engine, scene1* Scene)
{
    //Background
    slayRenderTexture(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, 0, slayFlipNONE, Scene->TextureBackground, 255);

    //Hint
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Movement: A/D", -150, -100, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Jump: SPACE", -150, -70, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Shoot: LMB", -150, -40, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);

    //Platforms
    for (uint64 i = 0; i < Scene->Platforms->Length; i++)
    {
        slayRender3DTextureCamera(Engine, ((platform*)Scene->Platforms->Values[i])->X, ((platform*)Scene->Platforms->Values[i])->Y, ((platform*)Scene->Platforms->Values[i])->Width, ((platform*)Scene->Platforms->Values[i])->Height, 0, slayFlipNONE, 0.95, 0.1, 0.005, Scene->TexturePlatform, 255);
    }

    //Projectiles
    for (uint64 i = 0; i < Scene->Projectiles->Length; i++)
    {
        slayRenderTextureCamera(Engine, ((projectile*)Scene->Projectiles->Values[i])->X, ((projectile*)Scene->Projectiles->Values[i])->Y, ((projectile*)Scene->Projectiles->Values[i])->Width, ((projectile*)Scene->Projectiles->Values[i])->Height, ((projectile*)Scene->Projectiles->Values[i])->Angle, slayFlipNONE, 1, ((game*)Engine->Game)->TextureProjectile, 255);
    }

    //Player
    if (Scene->Player->Facing == 1)
    {
        slayRenderTextureCamera(Engine, Scene->Player->X, Scene->Player->Y, Scene->Player->Width, Scene->Player->Height, 0, slayFlipNONE, 1, Scene->Player->TextureBase, 255);
    }
    else
    {
        slayRenderTextureCamera(Engine, Scene->Player->X, Scene->Player->Y, Scene->Player->Width, Scene->Player->Height, 0, slayFlipHORIZONTAL, 1, Scene->Player->TextureBase, 255);
    }

    //Pause
    if (Scene->paused)
    {
        slayRenderColor(Engine, Scene->Pause->X, Scene->Pause->Y, Scene->Pause->Width, Scene->Pause->Height, Scene->Pause->ColorR, Scene->Pause->ColorG, Scene->Pause->ColorB, Scene->Pause->ColorA);

        for (uint64 i = 0; i < Scene->Pause->Buttons->Length; i++)
        {
            slayRenderTexture(Engine, ((button*)Scene->Pause->Buttons->Values[i])->X, ((button*)Scene->Pause->Buttons->Values[i])->Y, ((button*)Scene->Pause->Buttons->Values[i])->Width, ((button*)Scene->Pause->Buttons->Values[i])->Height, 0, slayFlipNONE, ((button*)Scene->Pause->Buttons->Values[i])->TextureCurrent, 255);
        }
    }

    //FrameTime
    string text = strNew();
    UINTtoSTR(Engine->DeltaTime, text);
    strConcat(text, 3, "Frametime: ", text->String, "ms");
    slayRenderText(Engine, ((game*)Engine->Game)->FontCrazyPixel, text->String, 10, -10, 0.75, 0, slayFlipNONE, 255, 255, 255, 255);
    strPurge(text);

    return 0;
}

uint16 renderScene2(slayEngine* Engine, scene2* Scene)
{
    //Background
    slayRenderTexture(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, 0, slayFlipNONE, Scene->TextureBackground, 255);

    //Hint
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Movement: A/D", -150, -100, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Jump: SPACE", -150, -70, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);
    slayRenderTextCamera(Engine, ((game*)Engine->Game)->FontCrazyPixel, "Shoot: LMB", -150, -40, 1, 0, slayFlipNONE, 0.5, 255, 255, 255, 255);

    //Platforms
    for (uint64 i = 0; i < Scene->Platforms->Length; i++)
    {
        slayRender3DTextureCamera(Engine, ((platform*)Scene->Platforms->Values[i])->X, ((platform*)Scene->Platforms->Values[i])->Y, ((platform*)Scene->Platforms->Values[i])->Width, ((platform*)Scene->Platforms->Values[i])->Height, 0, slayFlipNONE, 0.95, 0.1, 0.005, Scene->TexturePlatform, 255);
    }

    //Player
    if (Scene->Player->Facing == 1)
    {
        slayRenderTextureCamera(Engine, Scene->Player->X, Scene->Player->Y, Scene->Player->Width, Scene->Player->Height, 0, slayFlipNONE, 1, Scene->Player->TextureBase, 255);
    }
    else
    {
        slayRenderTextureCamera(Engine, Scene->Player->X, Scene->Player->Y, Scene->Player->Width, Scene->Player->Height, 0, slayFlipHORIZONTAL, 1, Scene->Player->TextureBase, 255);
    }

    //Pause
    if (Scene->paused)
    {
        slayRenderColor(Engine, Scene->Pause->X, Scene->Pause->Y, Scene->Pause->Width, Scene->Pause->Height, Scene->Pause->ColorR, Scene->Pause->ColorG, Scene->Pause->ColorB, Scene->Pause->ColorA);

        for (uint64 i = 0; i < Scene->Pause->Buttons->Length; i++)
        {
            slayRenderTexture(Engine, ((button*)Scene->Pause->Buttons->Values[i])->X, ((button*)Scene->Pause->Buttons->Values[i])->Y, ((button*)Scene->Pause->Buttons->Values[i])->Width, ((button*)Scene->Pause->Buttons->Values[i])->Height, 0, slayFlipNONE, ((button*)Scene->Pause->Buttons->Values[i])->TextureCurrent, 255);
        }
    }

    //FrameTime
    string text = strNew();
    UINTtoSTR(Engine->DeltaTime, text);
    strConcat(text, 3, "Frametime: ", text->String, "ms");
    slayRenderText(Engine, ((game*)Engine->Game)->FontCrazyPixel, text->String, 10, -10, 0.75, 0, slayFlipNONE, 255, 255, 255, 255);
    strPurge(text);

    return 0;
}