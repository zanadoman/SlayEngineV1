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
    uint64 projectileCount, j;
    projectile* *Projectiles;

    playerProjectile(Game);

    Projectiles = malloc(1);
    Projectiles[0] = NULL;
    projectileCount = 1;
    for (uint64 i = 0; Game->Projectiles[i] != NULL; i++)
    {
        //Horizontal movement
        Game->Projectiles[i]->X += Game->Projectiles[i]->Speed * Game->Projectiles[i]->Facing * Game->DeltaTime;

        //Collision and deletion handling
        for (j = 0; Game->Platforms[j] != NULL; j++)
        {
            collision = slayCollision(Game->Projectiles[i]->Hitbox, Game->Platforms[j]->Hitbox);

            if (collision > 0 || Game->Projectiles[i]->X < 0 || Game->Projectiles[i]->X > Game->Display->X - Game->Projectiles[i]->Width)
            {
                free(Game->Projectiles[i]->Hitbox);
                free(Game->Projectiles[i]);
                break;
            }
        }
        //Undestroyed projectile handling
        if (Game->Platforms[j] == NULL)
        {
            Projectiles = realloc(Projectiles, sizeof(projectile) * (projectileCount + 1));
            Projectiles[projectileCount] = NULL;
            Projectiles[projectileCount - 1] = Game->Projectiles[i];
            projectileCount++;
        }
    }
    //End of deletion handling
    free(Game->Projectiles);
    Game->Projectiles = Projectiles;

    return 0;
}

uint16 playerProjectile(game* Game)
{
    uint64 projectileCount;

    if (slayKey(Game->Display, Game->Player->KeyFire) && SDL_GetTicks64() > Game->Player->ReloadTick + Game->Player->ReloadTime)
    {
        Game->Player->ReloadTick = SDL_GetTicks64();

        projectileCount = 1;
        for (uint64 i = 0; Game->Projectiles[i] != NULL; i++)
        {
            projectileCount++;
        }
        Game->Projectiles = realloc(Game->Projectiles, sizeof(projectile) * (projectileCount + 1));
        Game->Projectiles[projectileCount] = NULL;
        Game->Projectiles[projectileCount - 1] = newProjectile(Game->Player->X + 10 + 20 * Game->Player->Facing, Game->Player->Y + 14, 10, 4, 0.75, Game->Player->Facing, 255, 0, 0);
    }

    return 0;
}