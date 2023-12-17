#include "../game.h"

player* newPlayer(slayEngine* Engine, uint16 KeyLeft, uint16 KeyRight, uint16 KeyJump, uint16 KeyFire)
{
    player* result;

    result = malloc(sizeof(player));

    result->X = 0;
    result->Y = 0;
    result->PrevX = 0;
    result->PrevY = 0;

    result->MinX = 0;
    result->MinY = 0;
    result->MaxX = 0;
    result->MaxY = 0;

    result->Width = 30; //66
    result->Height = 42; //64

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
    result->CenterX = 15;
    result->CenterY = 21;

    result->KeyLeft = KeyLeft;
    result->KeyRight = KeyRight;
    result->KeyJump = KeyJump;
    result->KeyFire = KeyFire;

    result->Alive = true;
    result->RespawnTime = 500;
    result->DeathTick = 0;

    result->TextureCurrent = NULL;

    result->Hitbox = slayNewHitbox(actPLAYER, &result->X, &result->Y, &result->PrevX, &result->PrevY, 0, 0, result->Width, result->Height, 1.2, 1, &result->MinX, &result->MinY, &result->MaxX, &result->MaxY);

    return result;
}

uint8 updatePlayer(slayEngine* Engine)
{
    player* Player;
    array Platforms;
    crate* Crate;
    array PhysicsLayer;

    uint8 collision;
    logic falling;
    double zoom;

    switch (Engine->CurrentScene)
    {
        case 0:
        return 1;
        
        case 1:
            Player = ((scene1*)Engine->Scenes->Values[1])->Player;
            Platforms = ((scene1*)Engine->Scenes->Values[1])->Platforms;
            Crate = ((scene1*)Engine->Scenes->Values[1])->Crate;
            PhysicsLayer = ((scene1*)Engine->Scenes->Values[1])->PhysicsLayer;
        break;

        case 2:
            Player = ((scene2*)Engine->Scenes->Values[2])->Player;
            Platforms = ((scene2*)Engine->Scenes->Values[2])->Platforms;
            Crate = NULL;
            PhysicsLayer = NULL;
        break;
    }

    //Applying movement
    Player->PrevX = Player->X;
    Player->PrevY = Player->Y;
    Player->X += Player->Speed * Player->AccelerationX * Engine->DeltaTime;
    Player->Y += GRAVITY * Player->AccelerationY * Engine->DeltaTime;

    //Clamp player position
    if (Player->X < Player->MinX)
    {
        Player->X = Player->MinX;
    }
    else if (Player->MaxX < Player->X + Player->Width)
    {
        Player->X = Player->MaxX - Player->Width;
    }

    //Collision
    collision = slayCollision2(Player->Hitbox, PhysicsLayer);
    slayApplyCollision2(Player->Hitbox, PhysicsLayer);

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

    if ((collision & slayCollBOTTOMLEFT) == slayCollBOTTOMLEFT || (collision & slayCollBOTTOM) == slayCollBOTTOM || (collision & slayCollBOTTOMRIGHT) == slayCollBOTTOMRIGHT)
    {
        Player->AccelerationY = 0;
        falling = false;
    }
    else if ((collision & slayCollTOPLEFT) == slayCollTOPLEFT || (collision & slayCollTOP) == slayCollTOP || (collision & slayCollTOPRIGHT) == slayCollTOPRIGHT)
    {
        Player->AccelerationY = 0;
    }

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

    //Flipbooks
    if (!Player->Alive)
    {
        Player->TextureCurrent = slayLoopFlipbook(((game*)Engine->Game)->Flipbooks->playerStunned);
    }
    else if (Player->AccelerationX == 0 && Player->AccelerationY == 0)
    {
        Player->TextureCurrent = slayLoopFlipbook(((game*)Engine->Game)->Flipbooks->playerIdle);
    }
    else if (Player->AccelerationX != 0 && Player->AccelerationY == 0)
    {
        Player->TextureCurrent = slayLoopFlipbook(((game*)Engine->Game)->Flipbooks->playerRun);
    }
    else if (Player->AccelerationY < 0)
    {
        Player->TextureCurrent = ((game*)Engine->Game)->Textures->playerJump;
    }
    else
    {
        Player->TextureCurrent = ((game*)Engine->Game)->Textures->playerFall;
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
    free(Player->Hitbox);
    free(Player);

    return 0;
}