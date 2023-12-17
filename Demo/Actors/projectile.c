#include "../game.h"

projectile* newProjectile(actors Parent, double SpawnX, double SpawnY, double MinX, double MaxX, double MinY, double MaxY, double Angle);
uint8 playerProjectile(slayEngine* Engine, array Projectiles, player* Player, slaySound* SoundFire, uint8 Volume);
uint8 eagleProjectile(slayEngine* Engine, array Projectiles, eagle* Eagle, player* Player, array Platforms, crate* Crate, slaySound* SoundFire, uint8 Volume);

projectile* newProjectile(actors Parent, double SpawnX, double SpawnY, double MinX, double MaxX, double MinY, double MaxY, double Angle)
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

    result->Hitbox = slayNewHitbox(Parent, &result->X, &result->Y, 3, 0, 4, 4, -1, -1, 0, 0, 0, 0);

    return result;
}

uint8 updateProjectile(slayEngine* Engine, array Projectiles, player* Player, eagle* Eagle, array Platforms, crate* Crate, slaySound* SoundFire)
{
    uint8 collision;
    logic destroyed;

    //Actor shooting
    if (Player->Alive)
    {
        playerProjectile(Engine, Projectiles, Player, SoundFire, ((game*)Engine->Game)->Volume);
    }
    if (Eagle->Alive)
    {
        eagleProjectile(Engine, Projectiles, Eagle, Player, Platforms, Crate, SoundFire, ((game*)Engine->Game)->Volume);
    }

    for (uint16 i = 0; i < Projectiles->Length; i++)
    {
        destroyed = false;

        //Movement
        slayVectorTranslate(((projectile*)Projectiles->Values[i])->X, ((projectile*)Projectiles->Values[i])->Y, &((projectile*)Projectiles->Values[i])->X, &((projectile*)Projectiles->Values[i])->Y, ((projectile*)Projectiles->Values[i])->Speed * Engine->DeltaTime, ((projectile*)Projectiles->Values[i])->Angle);

        //Platform collision
        for (uint16 j = 0; j < Platforms->Length; j++)
        {
            collision = slayCollision(((projectile*)Projectiles->Values[i])->Hitbox, ((platform*)Platforms->Values[j])->Hitbox);

            if (slayCollNONE < collision || (((projectile*)Projectiles->Values[i])->X < ((projectile*)Projectiles->Values[i])->MinX - ((projectile*)Projectiles->Values[i])->Width || ((projectile*)Projectiles->Values[i])->MaxX < ((projectile*)Projectiles->Values[i])->X) || (((projectile*)Projectiles->Values[i])->Y < ((projectile*)Projectiles->Values[i])->MixY - ((projectile*)Projectiles->Values[i])->Height || ((projectile*)Projectiles->Values[i])->MaxY < ((projectile*)Projectiles->Values[i])->Y))
            {
                free(((projectile*)Projectiles->Values[i])->Hitbox);
                arrRemove(Projectiles, i);
                destroyed = true;
                i--;
                break;
            }
        }
        if (!destroyed && slayCollision(((projectile*)Projectiles->Values[i])->Hitbox, Crate->Hitbox))
        {
            free(((projectile*)Projectiles->Values[i])->Hitbox);
            arrRemove(Projectiles, i);
            destroyed = true;
            i--;
        }
        if (destroyed)
        {
            continue;
        }

        //Actor collision
        switch (((projectile*)Projectiles->Values[i])->Parent)
        {
            case actPLAYER:
                if (Eagle->Alive)
                {
                    collision = slayCollision(((projectile*)Projectiles->Values[i])->Hitbox, Eagle->Hitbox);
                    if (slayCollNONE < collision)
                    {
                        free(((projectile*)Projectiles->Values[i])->Hitbox);
                        arrRemove(Projectiles, i);
                        i--;

                        Eagle->Alive = false;
                        Eagle->DeathTick = slayGetTicks();

                        continue;
                    }
                }
                break;
            case actEAGLE:
                if (Player->Alive)
                {
                    collision = slayCollision(((projectile*)Projectiles->Values[i])->Hitbox, Player->Hitbox);
                    if (slayCollNONE < collision)
                    {
                        free(((projectile*)Projectiles->Values[i])->Hitbox);
                        arrRemove(Projectiles, i);
                        i--;

                        Player->Alive = false;
                        Player->DeathTick = slayGetTicks();

                        continue;
                    }
                }
                break;
        }
    }

    return 0;
}

uint8 playerProjectile(slayEngine* Engine, array Projectiles, player* Player, slaySound* SoundFire, uint8 Volume)
{
    slayObject object;
    double angle;

    if (slayKey(Engine, Player->KeyFire) && Player->ReloadTime < slayGetTicks() - Player->ReloadTick)
    {
        slayApplyCamera(Engine, &object, Player->X + Player->CenterX, Player->Y + Player->CenterY, 0, 0, 1);
        slayVectorAngle(object.x, object.y, Engine->Mouse->X, Engine->Mouse->Y, &angle);

        if ((Player->Facing == -1 && 90 < angle && angle < 270) || (Player->Facing == 1 && (270 < angle || angle < 90)))
        {
            Player->ReloadTick = slayGetTicks();
            arrInsert(Projectiles, Projectiles->Length, newProjectile(actPLAYER, Player->X + Player->CenterX, Player->Y + Player->CenterY, Player->MinX, Player->MaxX, Player->MinY, Player->MaxY, angle));
            slayPlaySound(SoundFire, 1, Volume, 255, 255, 0);
        }
    }

    return 0;
}

uint8 eagleProjectile(slayEngine* Engine, array Projectiles, eagle* Eagle, player* Player, array Platforms, crate* Crate, slaySound* SoundFire, uint8 Volume)
{
    double length, angle;

    slayVectorLength(Eagle->X + Eagle->Width / 2.0, Eagle->Y + Eagle->Height / 2.0, Player->X + Player->CenterX, Player->Y + Player->CenterY, &length);
    slayVectorAngle(Eagle->X + Eagle->Width / 2.0, Eagle->Y + Eagle->Height / 2.0, Player->X + Player->CenterX, Player->Y + Player->CenterY, &angle);
    
    if (length <= Eagle->AttackRange && Eagle->ReloadTime < slayGetTicks() - Eagle->ReloadTick && ((Eagle->Facing == -1 && 90 < angle && angle < 270) || (Eagle->Facing == 1 && (270 < angle || angle < 90))))
    {
        for (uint16 i = 0; i <  Platforms->Length; i++)
        {
            if (!slayVectorRayCast(Eagle->X + Eagle->Width / 2.0, Eagle->Y + Eagle->Height / 2.0, Player->X + Player->CenterX, Player->Y + Player->CenterY, ((platform*)Platforms->Values[i])->Hitbox, 0, 3))
            {
                return 1;
            }
        }

        if (!slayVectorRayCast(Eagle->X + Eagle->Width / 2.0, Eagle->Y + Eagle->Height / 2.0, Player->X + Player->CenterX, Player->Y + Player->CenterY, Crate->Hitbox, 0, 3))
        {
            return 1;
        }
        
        Eagle->ReloadTick = slayGetTicks();
        arrInsert(Projectiles, Projectiles->Length, newProjectile(actEAGLE, Eagle->X + Eagle->Width / 2.0, Eagle->Y + Eagle->Height / 2.0, Eagle->MinX, Eagle->MaxX, Eagle->MinY, Eagle->MaxY, angle));
        if (Player->X < Eagle->X)
        {
            slayPlaySound(SoundFire, 1, Volume, 64, 255, 0);
        }
        else 
        {
            slayPlaySound(SoundFire, 1, Volume, 255, 64, 0);
        }
    }

    return 0;
}

uint8 destroyProjectiles(array Projectiles)
{
    for (uint16 i = 0; i < Projectiles->Length; i++)
    {
        free(((projectile*)Projectiles->Values[i])->Hitbox);
    }
    for (uint16 i = 0; i < Projectiles->Length; i++)
    {
        free(Projectiles->Values[i]);
    }
    arrPurge(Projectiles);

    return 0;
}