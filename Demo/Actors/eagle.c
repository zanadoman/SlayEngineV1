#include "../game.h"

eagle* newEagle(slayEngine* Engine)
{
    eagle* result;

    result = malloc(sizeof(eagle));

    result->Width = 60;
    result->Height = 60;

    result->Speed = 0.2;
    result->Facing = 1;
    result->ReloadTime = 200;
    result->ReloadTick = 0;

    result->Flipbook = slayNewFlipbook(Engine, 150, 6, "assets/eagle/eagle1.png", "assets/eagle/eagle2.png", "assets/eagle/eagle3.png", "assets/eagle/eagle4.png", "assets/eagle/eagle3.png", "assets/eagle/eagle2.png");
    result->TextureCurrent = result->Flipbook->Textures[0];

    result->Hitbox = NULL;

    return result;
}

uint16 updateEagle(slayEngine* Engine, eagle* Eagle, player* Player, array Platforms, array Projectiles)
{
    double angle;

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

    //Shooting
    slayVectorAngle(Eagle->X + Eagle->Width / 2, Eagle->Y + Eagle->Height / 2, Player->X + Player->ProjectileRelativeX, Player->Y + Player->ProjectileRelativeY, &angle);
    if (slayGetTicks() - Eagle->ReloadTick >= Eagle->ReloadTime && ((Eagle->Facing == -1 && 90 < angle && angle < 270) || (Eagle->Facing == 1 && (270 < angle || angle < 90))))
    {
        for (uint64 i = 0; i <  Platforms->Length; i++)
        {
            if (!slayVectorRayCast(Eagle->X + Eagle->Width / 2, Eagle->Y + Eagle->Height / 2, Player->X + Player->ProjectileRelativeX, Player->Y + Player->ProjectileRelativeY, ((platform*)Platforms->Values[i])->Hitbox))
            {
                break;
            }
            else if (i == Platforms->Length - 1)
            {
                Eagle->ReloadTick = slayGetTicks();
                arrInsert(Projectiles, Projectiles->Length, newProjectile(Eagle->X + Eagle->Width / 2, Eagle->Y + Eagle->Height / 2, Player->MinX, Player->MaxX, Player->MinY, Player->MaxY, Player->ProjectileWidth, Player->ProjectileHeight, Player->ProjectileSpeed, angle));
            }
        }
    }

    return 0;
}

uint16 destroyEagle(eagle* Eagle)
{
    free(Eagle->Hitbox);
    slayDestroyFlipbook(Eagle->Flipbook);
    free(Eagle);

    return 0;
}