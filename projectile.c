#include "game.h"

uint16 playerProjectile(slayEngine* Engine, array Projectiles, player* Player, uint8 Volume);

projectile* newProjectile(double SpawnX, double SpawnY, double MinX, double MaxX, double MinY, double MaxY, uint16 Width, uint16 Height, double Speed, double Angle)
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

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height);

    return result;
}

uint16 updateProjectile(slayEngine* Engine, array Projectiles, player* Player, array Platforms, uint8 Volume, uint64 DeltaTime)
{
    uint8 collision;
    uint64 j;

    playerProjectile(Engine, Projectiles, Player, Volume);

    for (uint64 i = 0; i < Projectiles->Length; i++)
    {
        slayVectorTranslate(((projectile*)Projectiles->Values[i])->X, ((projectile*)Projectiles->Values[i])->Y, &((projectile*)Projectiles->Values[i])->X, &((projectile*)Projectiles->Values[i])->Y, ((projectile*)Projectiles->Values[i])->Speed * DeltaTime, ((projectile*)Projectiles->Values[i])->Angle);

        for (j = 0; j < Platforms->Length; j++)
        {
            collision = slayCollision(((projectile*)Projectiles->Values[i])->Hitbox, ((platform*)Platforms->Values[j])->Hitbox);

            if (collision > 0 || (((projectile*)Projectiles->Values[i])->X < ((projectile*)Projectiles->Values[i])->MinX - ((projectile*)Projectiles->Values[i])->Width || ((projectile*)Projectiles->Values[i])->MaxX < ((projectile*)Projectiles->Values[i])->X) || (((projectile*)Projectiles->Values[i])->Y < ((projectile*)Projectiles->Values[i])->MixY - ((projectile*)Projectiles->Values[i])->Height || ((projectile*)Projectiles->Values[i])->MaxY < ((projectile*)Projectiles->Values[i])->Y))
            {
                free(((projectile*)Projectiles->Values[i])->Hitbox);
                arrRemove(Projectiles, i);
                i--;
                break;
            }
        }
    }

    return 0;
}

uint16 playerProjectile(slayEngine* Engine, array Projectiles, player* Player, uint8 Volume)
{
    SDL_Rect object;
    double angle;

    if (Engine->Mouse->LMB && slayGetTicks() > Player->ReloadTick + Player->ReloadTime)
    {
        slayApplyCamera(Engine, &object, Player->X, Player->Y, Player->Width, Player->Height, 1);
        object.x += object.w / 2;
        object.y += object.h / 2;
        slayVectorAngle(object.x, object.y, Engine->Mouse->X, Engine->Mouse->Y, &angle);

        if ((Player->Facing == -1 && 90 < angle && angle < 270) || (Player->Facing == 1 && (270 < angle || angle < 90)))
        {
            Player->ReloadTick = slayGetTicks();
            arrInsert(Projectiles, Projectiles->Length, newProjectile(Player->X + Player->ProjectileRelativeX, Player->Y + Player->ProjectileRelativeY, Player->MinX, Player->MaxX, Player->MinY, Player->MaxY, Player->ProjectileWidth, Player->ProjectileHeight, Player->ProjectileSpeed, angle));
            if (270 < angle || angle < 90)
            {
                slayPlaySound(Player->SoundFire, 1, Volume, 64, 255, 0);
            }
            else
            {
                slayPlaySound(Player->SoundFire, 1, Volume, 255, 64, 0);
            }
        }
    }

    return 0;
}