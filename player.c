#include "game.h"

player* newPlayer(double SpawnX, double SpawnY, uint16 Width, uint16 Height, double Speed, double JumpHeight, uint64 ReloadTime, uint64 LeftKey, uint64 RightKey, uint64 KeyJump, uint8 KeyFire, uint8 ColorR, uint8 ColorG, uint8 ColorB)
{
    player* result;

    result = malloc(sizeof(player));

    result->X = SpawnX;
    result->Y = SpawnY;

    result->Width = Width;
    result->Height = Height;

    result->Speed = Speed;
    result->JumpHeight = JumpHeight;
    result->AccelerationX = 0;
    result->AccelerationY = 0;
    result->Facing = 1;
    result->ReloadTime = ReloadTime;
    result->ReloadTick = 0;

    result->KeyLeft = LeftKey;
    result->KeyRight = RightKey;
    result->KeyJump = KeyJump;
    result->KeyFire = KeyFire;

    result->ColorR = ColorR;
    result->ColorG = ColorG;
    result->ColorB = ColorB;

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height);

    return result;
}

uint16 updatePlayer(game* Game)
{
    uint8 collision;
    boolean falling;

    //Horizontal movement
    if (slayKey(Game->Display, Game->Player->KeyLeft))
    {
        if (Game->Player->AccelerationX > -1)
        {
            Game->Player->AccelerationX -= 0.003 * Game->DeltaTime;
            if (Game->Player->AccelerationX < -1)
            {
                Game->Player->AccelerationX = -1;
            }
        }
        Game->Player->Facing = -1;
    }
    else if (slayKey(Game->Display, Game->Player->KeyRight))
    {
        if (Game->Player->AccelerationX < 1)
        {
            Game->Player->AccelerationX += 0.003 * Game->DeltaTime;
            if (Game->Player->AccelerationX > 1)
            {
                Game->Player->AccelerationX = 1;
            }
        }
        Game->Player->Facing = 1;
    }
    else
    {
        if (Game->Player->AccelerationX < 0)
        {
            Game->Player->AccelerationX += 0.005 * Game->DeltaTime;
            if (Game->Player->AccelerationX > 0)
            {
                Game->Player->AccelerationX = 0;
            }
        }
        else if (Game->Player->AccelerationX > 0)
        {
            Game->Player->AccelerationX -= 0.005 * Game->DeltaTime;
            if (Game->Player->AccelerationX < 0)
            {
                Game->Player->AccelerationX = 0;
            }
        }
    }
    Game->Player->X += Game->Player->Speed * Game->Player->AccelerationX * Game->DeltaTime;

    //Vertical movement
    Game->Player->Y += GRAVITY * Game->Player->AccelerationY * Game->DeltaTime;
    falling = true;
    for (uint64 i = 0; Game->Platforms[i] != NULL; i++)
    {
        collision = slayCollision(Game->Player->Hitbox, Game->Platforms[i]->Hitbox);

        if (collision == BOTTOMLEFT || collision == BOTTOM || collision == BOTTOMRIGHT)
        {
            Game->Player->Y = Game->Platforms[i]->Y - Game->Player->Height;
            Game->Player->AccelerationY = 0;
            falling = false;
            break;
        }
        else if (collision == TOPLEFT || collision == TOP || collision == TOPRIGHT)
        {
            Game->Player->Y = Game->Platforms[i]->Y + Game->Platforms[i]->Height + 1;
            Game->Player->AccelerationY = 0;
            break;
        }
    }
    if (falling)
    {
        Game->Player->AccelerationY += 0.003 * Game->DeltaTime;
        if (Game->Player->AccelerationY > 1)
        {
            Game->Player->AccelerationY = 1;
        }
    }
    else if (slayKey(Game->Display, Game->Player->KeyJump))
    {
        Game->Player->AccelerationY = -Game->Player->JumpHeight;
    }

    //Clamp player position
    if (Game->Player->X < 0)
    {
        Game->Player->X = 0;
    }
    else if (Game->Player->X > Game->Display->X - Game->Player->Width)
    {
        Game->Player->X = Game->Display->X - Game->Player->Width;
    }
    if (Game->Player->Y < 0)
    {
        Game->Player->Y = 0;
        Game->Player->AccelerationY = 0;
    }

    return 0;
}