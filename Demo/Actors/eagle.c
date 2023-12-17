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
    result->RespawnTime = 2000;
    result->DeathTick = 0;

    result->FlipbookFlying = slayNewFlipbook(Engine, 150, 6, "assets/eagle/flying/flying1.png", "assets/eagle/flying/flying2.png", "assets/eagle/flying/flying3.png", "assets/eagle/flying/flying4.png", "assets/eagle/flying/flying3.png", "assets/eagle/flying/flying2.png");
    result->FlipbookDying = slayNewFlipbook(Engine, 150, 7, "assets/eagle/dying/dying1.png", "assets/eagle/dying/dying2.png", "assets/eagle/dying/dying3.png", "assets/eagle/dying/dying4.png", "assets/eagle/dying/dying5.png", "assets/eagle/dying/dying6.png", NULL);
    result->TextureCurrent = result->FlipbookFlying->Textures[0];

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height, -1, -1, 0, 0, 0, 0);

    return result;
}

uint8 updateEagle(slayEngine* Engine, eagle* Eagle)
{
    if (Eagle->Alive)
    {
        //Horizontal movement
        Eagle->X += Eagle->Speed * Eagle->Facing * Engine->DeltaTime;

        //Clamp position
        if (Eagle->X < Eagle->MinX)
        {
            Eagle->Facing = 1;
        }
        else if (Eagle->MaxX < Eagle->X + Eagle->Width)
        {
            Eagle->Facing = -1;
        }

        //Flipbooks
        Eagle->TextureCurrent = slayLoopFlipbook(Eagle->FlipbookFlying);
    }
    else
    {
        //Flipbooks (Dying)
        Eagle->TextureCurrent = slayPlayFlipbook(Eagle->FlipbookDying);
    }

    //Respawning
    if (!Eagle->Alive && Eagle->RespawnTime <= slayGetTicks() - Eagle->DeathTick)
    {
        Eagle->Alive = true;
        slayResetFlipbook(Eagle->FlipbookDying);
    }

    return 0;
}

uint8 destroyEagle(eagle* Eagle)
{
    slayDestroyFlipbook(Eagle->FlipbookFlying);
    slayDestroyFlipbook(Eagle->FlipbookDying);
    free(Eagle->Hitbox);
    free(Eagle);

    return 0;
}