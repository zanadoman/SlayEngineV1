#include "../game.h"

uint16 playerProjectile(slayEngine* Engine, array Projectiles, player* Player, slaySound* SoundFire, uint8 Volume);
uint16 eagleProjectile(slayEngine* Engine, array Projectiles, eagle* Eagle, player* Player, array Platforms, slaySound* SoundFire, uint8 Volume);

projectile* newProjectile(double SpawnX, double SpawnY, double MinX, double MaxX, double MinY, double MaxY, double Angle, actors Parent)
{
    projectile* result;

    result = malloc(sizeof(projectile));
    
    result->X = SpawnX;
    result->Y = SpawnY;

    result->MinX = MinX;
    result->MaxX = MaxX;
    result->MixY = MinY;
    result->MaxY = MaxY;

    result->Width = 10;
    result->Height = 4;

    result->Speed = 0.75;
    result->Angle = Angle;

    result->Parent = Parent;

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 3, 0, 4, 4);

    return result;
}

uint16 updateProjectile(slayEngine* Engine, array Projectiles, player* Player, eagle* Eagle, array Platforms, slaySound* SoundFire)
{
    uint8 collision;
    logic destroyed;
    uint64 j;

    playerProjectile(Engine, Projectiles, Player, SoundFire, ((game*)Engine->Game)->Volume);
    eagleProjectile(Engine, Projectiles, Eagle, Player, Platforms, SoundFire, ((game*)Engine->Game)->Volume);

    for (uint64 i = 0; i < Projectiles->Length; i++)
    {
        destroyed = false;

        //Movement
        slayVectorTranslate(((projectile*)Projectiles->Values[i])->X, ((projectile*)Projectiles->Values[i])->Y, &((projectile*)Projectiles->Values[i])->X, &((projectile*)Projectiles->Values[i])->Y, ((projectile*)Projectiles->Values[i])->Speed * Engine->DeltaTime, ((projectile*)Projectiles->Values[i])->Angle);

        //Platform collision
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

        //Actor collision
        switch (((projectile*)Projectiles->Values[i])->Parent)
        {
            case PLAYER:
                collision = slayCollision(((projectile*)Projectiles->Values[i])->Hitbox, Eagle->Hitbox);
                if (0 < collision)
                {
                    free(((projectile*)Projectiles->Values[i])->Hitbox);
                    arrRemove(Projectiles, i);
                    i--;

                    if (Eagle->Alive)
                    {
                        Eagle->Alive = false;
                        Eagle->DeathTick = slayGetTicks();
                    }

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

                    if (Eagle->Alive)
                    {
                        Player->Alive = false;
                        Player->DeathTick = slayGetTicks();
                    }

                    continue;
                }
                break;
        }
    }

    return 0;
}

uint16 playerProjectile(slayEngine* Engine, array Projectiles, player* Player, slaySound* SoundFire, uint8 Volume)
{
    slayObject object;
    double angle;

    if (Player->Alive && slayKey(Engine, Player->KeyFire) && slayGetTicks() > Player->ReloadTick + Player->ReloadTime)
    {
        slayApplyCamera(Engine, &object, Player->X + Player->CenterX, Player->Y + Player->CenterY, 0, 0, 1);
        slayVectorAngle(object.x, object.y, Engine->Mouse->X, Engine->Mouse->Y, &angle);

        if ((Player->Facing == -1 && 90 < angle && angle < 270) || (Player->Facing == 1 && (270 < angle || angle < 90)))
        {
            Player->ReloadTick = slayGetTicks();
            arrInsert(Projectiles, Projectiles->Length, newProjectile(Player->X + Player->CenterX, Player->Y + Player->CenterY, Player->MinX, Player->MaxX, Player->MinY, Player->MaxY, angle, PLAYER));
            slayPlaySound(SoundFire, 1, Volume, 255, 255, 0);
        }
    }

    return 0;
}

uint16 eagleProjectile(slayEngine* Engine, array Projectiles, eagle* Eagle, player* Player, array Platforms, slaySound* SoundFire, uint8 Volume)
{
    double length, angle;

    slayVectorLength(Eagle->X + Eagle->Width / 2, Eagle->Y + Eagle->Height / 2, Player->X + Player->CenterX, Player->Y + Player->CenterY, &length);
    slayVectorAngle(Eagle->X + Eagle->Width / 2, Eagle->Y + Eagle->Height / 2, Player->X + Player->CenterX, Player->Y + Player->CenterY, &angle);
    if (Eagle->Alive && slayGetTicks() - Eagle->ReloadTick >= Eagle->ReloadTime && length <= Eagle->AttackRange && ((Eagle->Facing == -1 && 90 < angle && angle < 270) || (Eagle->Facing == 1 && (270 < angle || angle < 90))))
    {
        for (uint64 i = 0; i <  Platforms->Length; i++)
        {
            if (!slayVectorRayCast(Eagle->X + Eagle->Width / 2, Eagle->Y + Eagle->Height / 2, Player->X + Player->CenterX, Player->Y + Player->CenterY, ((platform*)Platforms->Values[i])->Hitbox))
            {
                break;
            }
            else if (i == Platforms->Length - 1)
            {
                Eagle->ReloadTick = slayGetTicks();
                arrInsert(Projectiles, Projectiles->Length, newProjectile(Eagle->X + Eagle->Width / 2, Eagle->Y + Eagle->Height / 2, Eagle->MinX, Eagle->MaxX, Eagle->MinY, Eagle->MaxY, angle, EAGLE));
                if (Player->X < Eagle->X)
                {
                    slayPlaySound(SoundFire, 1, Volume, 64, 255, 0);
                }
                else 
                {
                    slayPlaySound(SoundFire, 1, Volume, 255, 64, 0);
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