#include "../game.h"

eagle* newEagle(slayEngine* Engine)
{
    eagle* result;

    result = malloc(sizeof(eagle));

    result->X = 200;
    result->Y = 200;

    result->Widht = 60;
    result->Height = 60;

    result->Flipbook = slayNewFlipbook(Engine, 150, 6, "assets/eagle/eagle1.png", "assets/eagle/eagle2.png", "assets/eagle/eagle3.png", "assets/eagle/eagle4.png", "assets/eagle/eagle3.png", "assets/eagle/eagle2.png");
    result->TextureCurrent = result->Flipbook->Textures[0];

    result->Hitbox = NULL;

    return result;
}

uint16 updateEagle(slayEngine* Engine, eagle* Eagle)
{
    Eagle->TextureCurrent = slayTurnFlipbook(Eagle->Flipbook);

    return 0;
}

uint16 renderEagle(slayEngine* Engine, eagle* Eagle)
{
    slayRenderTextureCamera(Engine, Eagle->X, Eagle->Y, Eagle->Widht, Eagle->Height, 0, slayFlipNONE, 1, Eagle->TextureCurrent, 255);

    return 0;
}

uint16 destroyEagle(eagle* Eagle)
{
    free(Eagle->Hitbox);
    slayDestroyFlipbook(Eagle->Flipbook);
    free(Eagle);

    return 0;
}