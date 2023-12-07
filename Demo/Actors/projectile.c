#include "../game.h"

uint16 playerProjectile(slayEngine* Engine, array Projectiles, player* Player, uint8 Volume);
uint16 eagleProjectile(slayEngine* Engine, array Projectiles, eagle* Eagle, player* Player, array Platforms, uint8 Volume);

projectile* newProjectile(double SpawnX, double SpawnY, double MinX, double MaxX, double MinY, double MaxY, uint16 Width, uint16 Height, double Speed, double Angle, actors Parent)
{
    projectile* result;

    result = malloc(sizeof(projectile));
    
    result->X = SpawnX;
    result->Y = SpawnY;

    result->MinX = MinX;
    result->MaxX = MaxX;
    result->MixY = MinY;
    result->MaxY = MaxY;

    result->Width = Width;
    result->Height = Height;

    result->Speed = Speed;
    result->Angle = Angle;

    result->Parent = Parent;

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height);

    return result;
}

uint16 updateProjectile(slayEngine* Engine, array Projectiles, player* Player, eagle* Eagle, array Platforms)
{
    uint8 collision;
    logic destroyed;
    uint64 j;

    playerProjectile(Engine, Projectiles, Player, ((game*)Engine->Game)->Volume);
    eagleProjectile(Engine, Projectiles, Eagle, Player, Platforms, ((game*)Engine->Game)->Volume);

    for (uint64 i = 0; i < Projectiles->Length; i++)
    {
        destroyed = false;

        slayVectorTranslate(((projectile*)Projectiles->Values[i])->X, ((projectile*)Projectiles->Values[i])->Y, &((projectile*)Projectiles->Values[i])->X, &((projectile*)Projectiles->Values[i])->Y, ((projectile*)Projectiles->Values[i])->Speed * Engine->DeltaTime, ((projectile*)Projectiles->Values[i])->Angle);

        for (j = 0; j < Platforms->Length; j++)
        {
            collision = slayCollision(((projectile*)Projectiles->Values[i])->Hitbox, ((platform*)Platforms->Values[j])->Hitbox);

            if (collision > 0 || (((projectile*)Projectiles->Values[i])->X < ((projectile*)Projectiles->Values[i])->MinX - ((projectile*)Projectiles->Values[i])->Width || ((projectile*)Projectiles->Values[i])->MaxX < ((projectile*)Projectiles->Values[i])->X) || (((projectile*)Projectiles->Values[i])->Y < ((projectile*)Projectiles->Values[i])->MixY - ((projectile*)Projectiles->Values[i])->Height || ((projectile*)Projectiles->Values[i])->MaxY < ((projectile*)Projectiles->Values[i])->Y))
            {
                free(((projectile*)Projectiles->Values[i])->Hitbox);
                arrRemove(Projectiles, i);
                destroyed = true;
                i--;
                break;
            }
        }
        if (destroyed)
        {
            continue;
        }

        switch (((projectile*)Projectiles->Values[i])->Parent)
        {
            case PLAYER:
                collision = slayCollision(((projectile*)Projectiles->Values[i])->Hitbox, Eagle->Hitbox);
                if (0 < collision)
                {
                    free(((projectile*)Projectiles->Values[i])->Hitbox);
                    arrRemove(Projectiles, i);
                    i--;
                    continue;
                }
                break;
            case EAGLE:
                collision = slayCollision(((projectile*)Projectiles->Values[i])->Hitbox, Player->Hitbox);
                if (0 < collision)
                {
                    free(((projectile*)Projectiles->Values[i])->Hitbox);
                    arrRemove(Projectiles, i);
                    i--;
                    continue;
                }
                break;
        }
    }

    return 0;
}

uint16 playerProjectile(slayEngine* Engine, array Projectiles, player* Player, uint8 Volume)
{
    slayObject object;
    double angle;

    if (slayKey(Engine, Player->KeyFire) && slayGetTicks() > Player->ReloadTick + Player->ReloadTime)
    {
        slayApplyCamera(Engine, &object, Player->X + Player->ProjectileRelativeX, Player->Y + Player->ProjectileRelativeY, 0, 0, 1);
        slayVectorAngle(object.x, object.y, Engine->Mouse->X, Engine->Mouse->Y, &angle);

        if ((Player->Facing == -1 && 90 < angle && angle < 270) || (Player->Facing == 1 && (270 < angle || angle < 90)))
        {
            Player->ReloadTick = slayGetTicks();
            arrInsert(Projectiles, Projectiles->Length, newProjectile(Player->X + Player->ProjectileRelativeX, Player->Y + Player->ProjectileRelativeY, Player->MinX, Player->MaxX, Player->MinY, Player->MaxY, Player->ProjectileWidth, Player->ProjectileHeight, Player->ProjectileSpeed, angle, PLAYER));
            slayPlaySound(Player->SoundFire, 1, Volume, 255, 255, 0);
        }
    }

    return 0;
}

uint16 eagleProjectile(slayEngine* Engine, array Projectiles, eagle* Eagle, player* Player, array Platforms, uint8 Volume)
{
    double length, angle;

    slayVectorLength(Eagle->X + Eagle->Width / 2, Eagle->Y + Eagle->Height / 2, Player->X + Player->ProjectileRelativeX, Player->Y + Player->ProjectileRelativeY, &length);
    slayVectorAngle(Eagle->X + Eagle->Width / 2, Eagle->Y + Eagle->Height / 2, Player->X + Player->ProjectileRelativeX, Player->Y + Player->ProjectileRelativeY, &angle);
    if (slayGetTicks() - Eagle->ReloadTick >= Eagle->ReloadTime && length <= Eagle->AttackRange && ((Eagle->Facing == -1 && 90 < angle && angle < 270) || (Eagle->Facing == 1 && (270 < angle || angle < 90))))
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
                arrInsert(Projectiles, Projectiles->Length, newProjectile(Eagle->X + Eagle->Width / 2, Eagle->Y + Eagle->Height / 2, Player->MinX, Player->MaxX, Player->MinY, Player->MaxY, Player->ProjectileWidth, Player->ProjectileHeight, Player->ProjectileSpeed, angle, EAGLE));
                if (Player->X < Eagle->X)
                {
                    slayPlaySound(Player->SoundFire, 1, Volume, 64, 255, 0);
                }
                else 
                {
                    slayPlaySound(Player->SoundFire, 1, Volume, 255, 64, 0);
                }
            }
        }
    }
}

uint16 destroyProjectiles(array Projectiles)
{
    for (uint64 i = 0; i < Projectiles->Length; i++)
    {
        free(((projectile*)Projectiles->Values[i])->Hitbox);
    }
    for (uint64 i = 0; i < Projectiles->Length; i++)
    {
        free(Projectiles->Values[i]);
    }
    arrPurge(Projectiles);

    return 0;
}