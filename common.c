#include "game.h"

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