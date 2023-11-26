#include "game.h"

uint16 playerProjectile(game* Game);

projectile* newProjectile(double SpawnX, double SpawnY, uint16 Width, uint16 Height, double Speed, uint8 Facing, uint8 ColorR, uint8 ColorG, uint8 ColorB)
{
    projectile* result;

    result = malloc(sizeof(projectile));
    
    result->X = SpawnX;
    result->Y = SpawnY;

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
        //Horizontal movement
        ((projectile*)Game->Projectiles->Values[i])->X += ((projectile*)Game->Projectiles->Values[i])->Speed * ((projectile*)Game->Projectiles->Values[i])->Facing * Game->DeltaTime;

        //Collision and deletion handling
        for (j = 0; j < Game->Platforms->Length; j++)
        {
            collision = slayCollision(((projectile*)Game->Projectiles->Values[i])->Hitbox, ((platform*)Game->Platforms->Values[j])->Hitbox);

            if (collision > 0 || ((projectile*)Game->Projectiles->Values[i])->X < 0 || ((projectile*)Game->Projectiles->Values[i])->X > Game->Display->X - ((projectile*)Game->Projectiles->Values[i])->Width)
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
        arrInsert(Game->Projectiles, Game->Projectiles->Length, newProjectile(Game->Player->X + 10 + 20 * Game->Player->Facing, Game->Player->Y + 14, 10, 4, 0.75, Game->Player->Facing, 192, 192, 192));
    }

    return 0;
}