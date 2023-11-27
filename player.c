/*
Creates a new player object.
Updates the player object, describes how the player should behave.
*/

#include "game.h"

player* newPlayer()
{
    player* result;

    result = malloc(sizeof(player));

    result->Width = 28;
    result->Height = 40;

    result->AccelerationX = 0;
    result->AccelerationRateX = 0.003;
    result->DeaccelerationRateX = 0.005;
    result->AccelerationY = 0;
    result->AccelerationRateY = 0;
    result->DeaccelerationRateY = 0.003;

    result->Speed = 0.4;
    result->JumpHeight = 1.1;
    result->Facing = 1;
    result->ReloadTime = 200;
    result->ReloadTick = 0;

    result->KeyLeft = SDL_SCANCODE_LEFT;
    result->KeyRight = SDL_SCANCODE_RIGHT;
    result->KeyJump = SDL_SCANCODE_UP;
    result->KeyFire = SDL_SCANCODE_LCTRL;

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height);

    result->ProjectileRelativeX = 30;
    result->ProjectileRelativeY = 14;
    result->ProjectileWidth = 10;
    result->ProjectileHeight = 4;
    result->ProjectileSpeed = 0.75;
    result->ProjectileColorR = 192;
    result->ProjectileColorG = 192;
    result->ProjectileColorB = 192;

    return result;
}

uint16 updatePlayer(game* Game)
{
    uint8 collision;
    logic falling;

    //Horizontal movement
    if (slayKey(Game->Display, Game->Player->KeyLeft))
    {
        if (Game->Player->AccelerationX > -1)
        {
            Game->Player->AccelerationX -= Game->Player->AccelerationRateX * Game->DeltaTime;
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
            Game->Player->AccelerationX += Game->Player->AccelerationRateX * Game->DeltaTime;
            if (Game->Player->AccelerationX > 1)
            {
                Game->Player->AccelerationX = 1;
            }
        }
        Game->Player->Facing = 1;
    }
    else
    {
        //Deacceleration the handler
        if (Game->Player->AccelerationX < 0)
        {
            Game->Player->AccelerationX += Game->Player->DeaccelerationRateX * Game->DeltaTime;
            if (Game->Player->AccelerationX > 0)
            {
                Game->Player->AccelerationX = 0;
            }
        }
        else if (Game->Player->AccelerationX > 0)
        {
            Game->Player->AccelerationX -= Game->Player->DeaccelerationRateX * Game->DeltaTime;
            if (Game->Player->AccelerationX < 0)
            {
                Game->Player->AccelerationX = 0;
            }
        }
    }
    //Applies movement
    Game->Player->X += Game->Player->Speed * Game->Player->AccelerationX * Game->DeltaTime;

    //Vertical movement
    //Preapplies gravity
    Game->Player->Y += GRAVITY * Game->Player->AccelerationY * Game->DeltaTime;
    //Assumes the player is falling
    falling = true;
    for (uint64 i = 0; i < Game->Platforms->Length; i++)
    {
        //Stores the current collision data
        collision = slayCollision(Game->Player->Hitbox, ((platform*)Game->Platforms->Values[i])->Hitbox);

        //If the player collides with a platform from the top
        if (collision == BOTTOMLEFT || collision == BOTTOM || collision == BOTTOMRIGHT)
        {
            //If the player falling it stops the falling and places the player on the top of the platform
            if (Game->Player->AccelerationY >= 0)
            {
                Game->Player->Y = ((platform*)Game->Platforms->Values[i])->Y - Game->Player->Height;
                Game->Player->AccelerationY = 0;
                falling = false;
            }
            /*If the the player is not falling (jumping) but still collides with one of its bottom corners
            it handles the side collision with the platform*/
            else if (collision == BOTTOMLEFT)
            {
                Game->Player->X = ((platform*)Game->Platforms->Values[i])->X + ((platform*)Game->Platforms->Values[i])->Width;
                Game->Player->AccelerationX = 0;
            }
            else if (collision == BOTTOMRIGHT)
            {
                Game->Player->X = ((platform*)Game->Platforms->Values[i])->X - Game->Player->Width;
                Game->Player->AccelerationX = 0;
            }
            
            break;
        }
        //If the player collides with a platform from the bottom
        else if (collision == TOPLEFT || collision == TOP || collision == TOPRIGHT)
        {
            //Places the player under the platform and stops the jump by resetting the gravity acceleration
            Game->Player->Y = ((platform*)Game->Platforms->Values[i])->Y + ((platform*)Game->Platforms->Values[i])->Height + 1;
            Game->Player->AccelerationY = 0;
            break;
        }
    }
    //If the player is midair this will apply gravity acceleration to the player in a specific rate until 1
    if (falling)
    {
        Game->Player->AccelerationY += Game->Player->DeaccelerationRateY * Game->DeltaTime;
        if (Game->Player->AccelerationY > 1)
        {
            Game->Player->AccelerationY = 1;
        }
    }
    //Starts the jump by reversing gravity acceleration
    else if (slayKey(Game->Display, Game->Player->KeyJump))
    {
        Game->Player->AccelerationY = -Game->Player->JumpHeight;
    }

    //Clamp player position
    if (Game->Player->X < Game->Player->MinX)
    {
        Game->Player->X = Game->Player->MinX;
    }
    else if (Game->Player->X > Game->Player->MaxX - Game->Player->Width)
    {
        Game->Player->X = Game->Player->MaxX - Game->Player->Width;
    }

    return 0;
}