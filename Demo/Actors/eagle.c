#include "../game.h"

eagle* newEagle(slayEngine* Engine)
{
    eagle* result;

    result = malloc(sizeof(eagle));

    result->X = 0;
    result->Y = 0;

    result->MinX = 0;
    result->MaxX = 0;
    result->MinY = 0;
    result->MaxY = 0;

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

    result->Hitbox = slayNewHitbox(result, actEAGLE, &result->X, &result->Y, 0, 0, result->Width, result->Height, 100, 200);

    result->TextureCurrent = NULL;

    return result;
}

uint8 updateEagle(slayEngine* Engine)
{
    eagle* Eagle;

    switch (Engine->CurrentScene)
    {
        case 0:
        return 1;

        case 1:
            Eagle = ((scene1*)Engine->Scenes->Values[1])->Eagle;
        break;

        case 2:
        return 1;
    }

    if (Eagle->Alive)
    {
        //Horizontal movement
        //Eagle->X += Eagle->Speed * Eagle->Facing * Engine->DeltaTime;

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
        Eagle->TextureCurrent = slayLoopFlipbook(((game*)Engine->Game)->Flipbooks->eagleFlying);
    }
    else
    {
        //Flipbooks (Dying)
        Eagle->TextureCurrent = slayPlayFlipbook(((game*)Engine->Game)->Flipbooks->eagleDying);
    }

    //Respawning
    if (!Eagle->Alive && Eagle->RespawnTime <= slayGetTicks() - Eagle->DeathTick)
    {
        Eagle->Alive = true;
        slayResetFlipbook(((game*)Engine->Game)->Flipbooks->eagleDying);
    }

    return 0;
}

uint8 destroyEagle(eagle* Eagle)
{
    free(Eagle->Hitbox);
    free(Eagle);

    return 0;
}