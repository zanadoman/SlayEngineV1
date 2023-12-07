#include "game.h"

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

uint16 renderPlayer(slayEngine* Engine, player* Player)
{
    if (Player->Facing == 1)
    {
        slayRenderTextureCamera(Engine, Player->X, Player->Y, Player->Width, Player->Height, 0, slayFlipNONE, 1, Player->TextureCurrent, 255);
    }
    else
    {
        slayRenderTextureCamera(Engine, Player->X, Player->Y, Player->Width, Player->Height, 0, slayFlipHORIZONTAL, 1, Player->TextureCurrent, 255);
    }

    return 0;
}

uint16 renderEagle(slayEngine* Engine, eagle* Eagle)
{
    if (Eagle->Facing == 1)
    {
        slayRenderTextureCamera(Engine, Eagle->X, Eagle->Y, Eagle->Widht, Eagle->Height, 0, slayFlipHORIZONTAL, 1, Eagle->TextureCurrent, 255);
    }
    else
    {
        slayRenderTextureCamera(Engine, Eagle->X, Eagle->Y, Eagle->Widht, Eagle->Height, 0, slayFlipNONE, 1, Eagle->TextureCurrent, 255);
    }

    return 0;
}

uint16 renderPause(slayEngine* Engine, pause* Pause)
{
    slayRenderColor(Engine, Pause->X, Pause->Y, Pause->Width, Pause->Height, Pause->ColorR, Pause->ColorG, Pause->ColorB, Pause->ColorA);

    for (uint64 i = 0; i < Pause->Buttons->Length; i++)
    {
        slayRenderTexture(Engine, ((button*)Pause->Buttons->Values[i])->X, ((button*)Pause->Buttons->Values[i])->Y, ((button*)Pause->Buttons->Values[i])->Width, ((button*)Pause->Buttons->Values[i])->Height, 0, slayFlipNONE, ((button*)Pause->Buttons->Values[i])->TextureCurrent, 255);
    }

    return 0;
}

uint16 renderFrameTime(slayEngine* Engine)
{
    string text;

    text = strNew();
    UINTtoSTR(Engine->DeltaTime, text);
    strConcat(text, 3, "Frametime: ", text->String, "ms");
    slayRenderText(Engine, ((game*)Engine->Game)->FontCrazyPixel, text->String, 10, -10, 0.75, 0, slayFlipNONE, 0, 0, 0, 255);
    strPurge(text);

    return 0;
}