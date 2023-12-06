#include "game.h"

button* newButton(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, char* TextureBase, char* TextureHover)
{
    button* result;

    result = malloc(sizeof(button));

    result->TextureBase = slayLoadTexture(Engine, TextureBase);
    result->TextureHover = slayLoadTexture(Engine, TextureHover);
    result->TextureCurrent = result->TextureBase;

    result->X = X;
    result->Y = Y;
    result->Width = Width;
    result->Height = Height;

    result->Pressed = false;
    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height);

    return result;
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

uint16 destroyButton(button* Button)
{
    slayUnloadTexture(Button->TextureBase);
    slayUnloadTexture(Button->TextureHover);
    free(Button->Hitbox);
    free(Button);

    return 0;
}