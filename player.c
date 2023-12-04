#include "game.h"

player* newPlayer(slayEngine* Engine)
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

    result->KeyLeft = SDL_SCANCODE_A;
    result->KeyRight = SDL_SCANCODE_D;
    result->KeyJump = SDL_SCANCODE_SPACE;
    result->KeyFire = SDL_SCANCODE_LMB;

    result->TextureBase = slayLoadTexture(Engine, "assets/player_base.png");
    result->SoundFire = slayLoadSound("assets/player_fire.wav");

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height);

    result->ProjectileRelativeX = 9;
    result->ProjectileRelativeY = 14;
    result->ProjectileWidth = 10;
    result->ProjectileHeight = 4;
    result->ProjectileSpeed = 0.75;
    result->ProjectileColorR = 192;
    result->ProjectileColorG = 192;
    result->ProjectileColorB = 192;

    return result;
}

uint16 updatePlayer(slayEngine* Engine, player* Player, array Platforms)
{
    uint8 collision;
    logic falling;
    double zoom;

    //Horizontal movement
    if (slayKey(Engine, Player->KeyLeft))
    {
        if (Player->AccelerationX > -1)
        {
            Player->AccelerationX -= Player->AccelerationRateX * Engine->DeltaTime;
            if (Player->AccelerationX < -1)
            {
                Player->AccelerationX = -1;
            }
        }
        Player->Facing = -1;
    }
    else if (slayKey(Engine, Player->KeyRight))
    {
        if (Player->AccelerationX < 1)
        {
            Player->AccelerationX += Player->AccelerationRateX * Engine->DeltaTime;
            if (Player->AccelerationX > 1)
            {
                Player->AccelerationX = 1;
            }
        }
        Player->Facing = 1;
    }
    else
    {
        //Deacceleration
        if (Player->AccelerationX < 0)
        {
            Player->AccelerationX += Player->DeaccelerationRateX * Engine->DeltaTime;
            if (Player->AccelerationX > 0)
            {
                Player->AccelerationX = 0;
            }
        }
        else if (Player->AccelerationX > 0)
        {
            Player->AccelerationX -= Player->DeaccelerationRateX * Engine->DeltaTime;
            if (Player->AccelerationX < 0)
            {
                Player->AccelerationX = 0;
            }
        }
    }
    Player->X += Player->Speed * Player->AccelerationX * Engine->DeltaTime;

    //Vertical movement
    Player->Y += GRAVITY * Player->AccelerationY * Engine->DeltaTime;
    falling = true;
    for (uint64 i = 0; i < Platforms->Length; i++)
    {
        collision = slayCollision(Player->Hitbox, ((platform*)Platforms->Values[i])->Hitbox);

        if (collision == slayCollBOTTOMLEFT || collision == slayCollBOTTOM || collision == slayCollBOTTOMRIGHT)
        {
            //Ground collision
            if (Player->AccelerationY >= 0)
            {
                Player->Y = ((platform*)Platforms->Values[i])->Y - Player->Height;
                Player->AccelerationY = 0;
                falling = false;
            }
            //Side collision
            else if (collision == slayCollBOTTOMLEFT)
            {
                Player->X = ((platform*)Platforms->Values[i])->X + ((platform*)Platforms->Values[i])->Width;
                Player->AccelerationX = 0;
            }
            else if (collision == slayCollBOTTOMRIGHT)
            {
                Player->X = ((platform*)Platforms->Values[i])->X - Player->Width;
                Player->AccelerationX = 0;
            }
            
            break;
        }
        else if (collision == slayCollTOPLEFT || collision == slayCollTOP || collision == slayCollTOPRIGHT)
        {
            Player->Y = ((platform*)Platforms->Values[i])->Y + ((platform*)Platforms->Values[i])->Height + 1;
            Player->AccelerationY = 0;
            break;
        }
    }

    //Falling or jumping
    if (falling)
    {
        Player->AccelerationY += Player->DeaccelerationRateY * Engine->DeltaTime;
        if (Player->AccelerationY > 1)
        {
            Player->AccelerationY = 1;
        }
    }
    else if (slayKey(Engine, Player->KeyJump))
    {
        Player->AccelerationY = -Player->JumpHeight;
    }

    //Clamp player position
    if (Player->X < Player->MinX)
    {
        Player->X = Player->MinX;
    }
    else if (Player->X > Player->MaxX - Player->Width)
    {
        Player->X = Player->MaxX - Player->Width;
    }

    return 0;
}