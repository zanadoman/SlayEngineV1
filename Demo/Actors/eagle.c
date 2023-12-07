#include "../game.h"

eagle* newEagle(slayEngine* Engine)
{
    eagle* result;

    result = malloc(sizeof(eagle));

    result->Width = 60;
    result->Height = 60;

    result->Speed = 0.2;
    result->Facing = 1;
    result->AttackRange = 400;
    result->ReloadTime = 200;
    result->ReloadTick = 0;

    result->Flipbook = slayNewFlipbook(Engine, 150, 6, "assets/eagle/eagle1.png", "assets/eagle/eagle2.png", "assets/eagle/eagle3.png", "assets/eagle/eagle4.png", "assets/eagle/eagle3.png", "assets/eagle/eagle2.png");
    result->TextureCurrent = result->Flipbook->Textures[0];

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height);

    return result;
}

uint16 updateEagle(slayEngine* Engine, eagle* Eagle)
{
    //Flipbook
    Eagle->TextureCurrent = slayTurnFlipbook(Eagle->Flipbook);

    //Horizontal movement
    if (Eagle->X < Eagle->MinX)
    {
        Eagle->Facing = 1;
    }
    else if (Eagle->MaxX < Eagle->X + Eagle->Width)
    {
        Eagle->Facing = -1;
    }
    Eagle->X += Eagle->Speed * Eagle->Facing * Engine->DeltaTime;

    return 0;
}

uint16 destroyEagle(eagle* Eagle)
{
    slayDestroyFlipbook(Eagle->Flipbook);
    free(Eagle->Hitbox);
    free(Eagle);

    return 0;
}