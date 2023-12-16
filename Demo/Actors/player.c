#include "../game.h"

player* newPlayer(slayEngine* Engine, uint16 KeyLeft, uint16 KeyRight, uint16 KeyJump, uint16 KeyFire)
{
    player* result;

    result = malloc(sizeof(player));

    result->Width = 66;
    result->Height = 64;

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
    result->CenterX = 33;
    result->CenterY = 43;

    result->KeyLeft = KeyLeft;
    result->KeyRight = KeyRight;
    result->KeyJump = KeyJump;
    result->KeyFire = KeyFire;

    result->Alive = true;
    result->RespawnTime = 500;
    result->DeathTick = 0;

    result->FlipbookIdle = slayNewFlipbook(Engine, 150, 4, "assets/player/idle/idle1.png", "assets/player/idle/idle2.png", "assets/player/idle/idle3.png", "assets/player/idle/idle4.png");
    result->FlipbookRun = slayNewFlipbook(Engine, 150, 6, "assets/player/run/run1.png", "assets/player/run/run2.png", "assets/player/run/run3.png", "assets/player/run/run4.png", "assets/player/run/run5.png", "assets/player/run/run6.png");
    result->FlipbookStunned = slayNewFlipbook(Engine, 150, 2, "assets/player/stunned/stunned1.png", "assets/player/stunned/stunned2.png");
    result->TextureJump = slayLoadTexture(Engine, "assets/player/jump.png");
    result->TextureFall = slayLoadTexture(Engine, "assets/player/fall.png");
    result->TextureCurrent = result->FlipbookIdle->Textures[0];

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 18, 22, 48, 64);

    return result;
}

uint8 updatePlayer(slayEngine* Engine, player* Player, array Platforms)
{
    uint8 collision;
    logic falling;
    double zoom;

    //Applying movement
    Player->PrevX = Player->X;
    Player->PrevY = Player->Y;
    Player->X += Player->Speed * Player->AccelerationX * Engine->DeltaTime;
    Player->Y += GRAVITY * Player->AccelerationY * Engine->DeltaTime;

    //Horizontal movement
    if (Player->Alive && slayKey(Engine, Player->KeyLeft))
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
    else if (Player->Alive && slayKey(Engine, Player->KeyRight))
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

    //Vertical movement
    falling = true;

    //Platform collision handling
    for (uint16 i = 0; i < Platforms->Length; i++)
    {
        collision = slayCollision(Player->Hitbox, ((platform*)Platforms->Values[i])->Hitbox);
        slayApplyCollision(collision, Player->PrevX, Player->PrevY, Player->Hitbox, ((platform*)Platforms->Values[i])->Hitbox);

        if (Player->Y + Player->Height <= ((platform*)Platforms->Values[i])->Y && (collision == slayCollBOTTOMLEFT || collision == slayCollBOTTOM || collision == slayCollBOTTOMRIGHT))
        {
            //Ground collision
            Player->AccelerationY = 0;
            falling = false;

            //Scene 2 platform generation
            if (Engine->CurrentScene == 2 && 4 < i)
            {
                for (uint8 j = 0; j < i - 4; j++)
                {
                    arrInsert(Platforms, Platforms->Length, newPlatform(((platform*)Platforms->Values[Platforms->Length - 1])->X + 200, ((platform*)Platforms->Values[Platforms->Length - 1])->Y + slayRandom(-100, 100, i), 100, 30));
                    arrRemove(Platforms, 0);
                }
            }
            else if (Engine->CurrentScene == 2 && i < 4)
            {
                for (uint8 j = 0; j < 4 - i; j++)
                {
                    arrInsert(Platforms, 0, newPlatform(((platform*)Platforms->Values[0])->X - 200, ((platform*)Platforms->Values[0])->Y + slayRandom(-100, 100, i), 100, 30));
                    arrRemove(Platforms, Platforms->Length - 1);
                }
            }
            
            break;
        }
        else if (((platform*)Platforms->Values[i])->Y + ((platform*)Platforms->Values[i])->Height <= Player->Y && (collision == slayCollTOPLEFT || collision == slayCollTOP || collision == slayCollTOPRIGHT))
        {
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
    else if (Player->Alive && slayKey(Engine, Player->KeyJump))
    {
        Player->AccelerationY = -Player->JumpHeight;
    }

    //Clamp player position
    if (Player->X < Player->MinX - Player->Hitbox->UpperLeftX)
    {
        Player->X = Player->MinX - Player->Hitbox->UpperLeftX;
    }
    else if (Player->X > Player->MaxX - Player->Width + Player->Hitbox->UpperLeftX)
    {
        Player->X = Player->MaxX - Player->Width + Player->Hitbox->UpperLeftX;
    }

    //Scene 2 falling
    if (Engine->CurrentScene == 2 && ((platform*)Platforms->Values[4])->Y + 1000 < Player->Y + Player->Hitbox->UpperLeftY)
    {
        Player->X = ((platform*)Platforms->Values[4])->X + 17;
        Player->Y = ((platform*)Platforms->Values[4])->Y - 1064;
    }

    //Flipbooks
    if (!Player->Alive)
    {
        Player->TextureCurrent = slayLoopFlipbook(Player->FlipbookStunned);
    }
    else if (Player->AccelerationX == 0 && Player->AccelerationY == 0)
    {
        Player->TextureCurrent = slayLoopFlipbook(Player->FlipbookIdle);
    }
    else if (Player->AccelerationX != 0 && Player->AccelerationY == 0)
    {
        Player->TextureCurrent = slayLoopFlipbook(Player->FlipbookRun);
    }
    else if (Player->AccelerationY < 0)
    {
        Player->TextureCurrent = Player->TextureJump;
    }
    else
    {
        Player->TextureCurrent = Player->TextureFall;
    }

    //Respawning
    if (!Player->Alive && Player->RespawnTime <= slayGetTicks() - Player->DeathTick)
    {
        Player->Alive = true;
    }

    return 0;
}

uint8 destroyPlayer(player* Player)
{
    slayDestroyFlipbook(Player->FlipbookIdle);
    slayDestroyFlipbook(Player->FlipbookRun);
    slayDestroyFlipbook(Player->FlipbookStunned);
    slayUnloadTexture(Player->TextureJump);
    slayUnloadTexture(Player->TextureFall);
    free(Player->Hitbox);
    free(Player);

    return 0;
}