#include "game.h"

uint16 playerProjectile(array Projectiles, player* Player, uint8 Volume);

projectile* newProjectile(double SpawnX, double SpawnY, double MinX, double MaxX, uint16 Width, uint16 Height, double Speed, uint8 Facing, uint8 ColorR, uint8 ColorG, uint8 ColorB)
{
    projectile* result;

    result = malloc(sizeof(projectile));
    
    result->X = SpawnX;
    result->Y = SpawnY;

    result->MinX = MinX;
    result->MaxX = MaxX;

    result->Width = Width;
    result->Height = Height;

    result->Speed = Speed;
    result->Facing = Facing;

    result->ColorR = ColorR;
    result->ColorG = ColorG;
    result->ColorB = ColorB;

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height);

    return result;
}

uint16 updateProjectile(array Projectiles, player* Player, array Platforms, uint8 Volume, uint64 DeltaTime)
{
    uint8 collision;
    uint64 j;

    playerProjectile(Projectiles, Player, Volume);

    for (uint64 i = 0; i < Projectiles->Length; i++)
    {
        ((projectile*)Projectiles->Values[i])->X += ((projectile*)Projectiles->Values[i])->Speed * ((projectile*)Projectiles->Values[i])->Facing * DeltaTime;

        for (j = 0; j < Platforms->Length; j++)
        {
            collision = slayCollision(((projectile*)Projectiles->Values[i])->Hitbox, ((platform*)Platforms->Values[j])->Hitbox);

            if (collision > 0 || ((projectile*)Projectiles->Values[i])->X < ((projectile*)Projectiles->Values[i])->MinX || ((projectile*)Projectiles->Values[i])->X > ((projectile*)Projectiles->Values[i])->MaxX - ((projectile*)Projectiles->Values[i])->Width)
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

uint16 playerProjectile(array Projectiles, player* Player, uint8 Volume)
{
    if (slayKey(Player->KeyFire) && slayGetTicks() > Player->ReloadTick + Player->ReloadTime)
    {
        Player->ReloadTick = slayGetTicks();
        arrInsert(Projectiles, Projectiles->Length, newProjectile(Player->X + Player->ProjectileRelativeX * Player->Facing, Player->Y + Player->ProjectileRelativeY, Player->MinX, Player->MaxX, Player->ProjectileWidth, Player->ProjectileHeight, Player->ProjectileSpeed, Player->Facing, Player->ProjectileColorR, Player->ProjectileColorG, Player->ProjectileColorB));
        if (Player->Facing == 1)
        {
            slayPlaySound(Player->SoundFire, 1, Volume, 32, 255, 0);
        }
        else
        {
            slayPlaySound(Player->SoundFire, 1, Volume, 255, 32, 0);
        }
    }

    return 0;
}