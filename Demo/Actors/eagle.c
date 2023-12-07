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

    result->Alive = true;
    result->RespawnTime = 10000;
    result->DeathTick = 0;

    result->FlipbookFlying = slayNewFlipbook(Engine, 150, 6, "assets/eagle/flying/flying1.png", "assets/eagle/flying/flying2.png", "assets/eagle/flying/flying3.png", "assets/eagle/flying/flying4.png", "assets/eagle/flying/flying3.png", "assets/eagle/flying/flying2.png");
    result->FlipbookDying = slayNewFlipbook(Engine, 150, 7, "assets/eagle/dying/dying1.png", "assets/eagle/dying/dying2.png", "assets/eagle/dying/dying3.png", "assets/eagle/dying/dying4.png", "assets/eagle/dying/dying5.png", "assets/eagle/dying/dying6.png", "assets/eagle/dying/dying7.png");
    result->TextureCurrent = result->FlipbookFlying->Textures[0];

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height);

    return result;
}

uint16 updateEagle(slayEngine* Engine, eagle* Eagle)
{
    if (Eagle->Alive)
    {
        //Flipbook
        Eagle->TextureCurrent = slayTurnFlipbook(Eagle->FlipbookFlying);

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
    }
    else if (Eagle->FlipbookDying->Current != 6)
    {
        Eagle->TextureCurrent = slayTurnFlipbook(Eagle->FlipbookDying);
    }

    if (!Eagle->Alive && slayGetTicks() - Eagle->DeathTick > Eagle->RespawnTime)
    {
        Eagle->Alive = true;
        Eagle->FlipbookDying->Current = 0;
    }

    return 0;
}

uint16 destroyEagle(eagle* Eagle)
{
    slayDestroyFlipbook(Eagle->FlipbookFlying);
    slayDestroyFlipbook(Eagle->FlipbookDying);
    free(Eagle->Hitbox);
    free(Eagle);

    return 0;
}