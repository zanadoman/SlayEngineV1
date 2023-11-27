#include "game.h"

uint16 playerProjectile(game* Game);

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

uint16 updateProjectile(game* Game)
{
    uint8 collision;
    uint64 j;

    playerProjectile(Game);

    for (uint64 i = 0; i < Game->Projectiles->Length; i++)
    {
        ((projectile*)Game->Projectiles->Values[i])->X += ((projectile*)Game->Projectiles->Values[i])->Speed * ((projectile*)Game->Projectiles->Values[i])->Facing * Game->DeltaTime;

        for (j = 0; j < Game->Platforms->Length; j++)
        {
            collision = slayCollision(((projectile*)Game->Projectiles->Values[i])->Hitbox, ((platform*)Game->Platforms->Values[j])->Hitbox);

            if (collision > 0 || ((projectile*)Game->Projectiles->Values[i])->X < ((projectile*)Game->Projectiles->Values[i])->MinX || ((projectile*)Game->Projectiles->Values[i])->X > ((projectile*)Game->Projectiles->Values[i])->MaxX - ((projectile*)Game->Projectiles->Values[i])->Width)
            {
                free(((projectile*)Game->Projectiles->Values[i])->Hitbox);
                arrRemove(Game->Projectiles, i);
                i--;
                break;
            }
        }
    }

    return 0;
}

uint16 playerProjectile(game* Game)
{
    if (slayKey(Game->Display, Game->Player->KeyFire) && SDL_GetTicks64() > Game->Player->ReloadTick + Game->Player->ReloadTime)
    {
        Game->Player->ReloadTick = SDL_GetTicks64();
        arrInsert(Game->Projectiles, Game->Projectiles->Length, newProjectile(Game->Player->X + Game->Player->ProjectileRelativeX * Game->Player->Facing, Game->Player->Y + Game->Player->ProjectileRelativeY, Game->Player->MinX, Game->Player->MaxX, Game->Player->ProjectileWidth, Game->Player->ProjectileHeight, Game->Player->ProjectileSpeed, Game->Player->Facing, Game->Player->ProjectileColorR, Game->Player->ProjectileColorG, Game->Player->ProjectileColorB));
    }

    return 0;
}