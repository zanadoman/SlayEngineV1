#include "SlayEngineV1/SlayEngineV1.h"

#define GRAVITY 0.65

typedef struct
{
    double X;
    double Y;

    uint16 Width;
    uint16 Height;

    double Speed;
    double JumpHeight;
    double AccelerationX;
    double AccelerationY;
    sint8 Facing;
    uint64 ReloadTime;
    uint64 ReloadTick;

    uint64 KeyLeft;
    uint64 KeyRight;
    uint64 KeyJump;
    uint64 KeyFire;

    uint8 ColorR;
    uint8 ColorG;
    uint8 ColorB;

    slayHitbox* Hitbox;
} player;

typedef struct
{
    double X;
    double Y;

    uint16 Width;
    uint16 Height;

    uint8 ColorR;
    uint8 ColorG;
    uint8 ColorB;

    slayHitbox* Hitbox;
} platform;

typedef struct
{
    double X;
    double Y;

    uint16 Width;
    uint16 Height;

    double Speed;
    sint8 Facing;

    uint8 ColorR;
    uint8 ColorG;
    uint8 ColorB;

    slayHitbox* Hitbox;
} projectile;


typedef struct
{
    display* Display;
    uint64 DeltaTime;
    uint64 DisplayPrevTick;

    array Platforms;
    player* Player;
    array Projectiles;
} game;

//Update queue
uint16 updateQueue(game* Game);

//Render queue
uint16 renderQueue(game* Game);

//Player
player* newPlayer(double SpawnX, double SpawnY, uint16 Width, uint16 Height, double Speed, double JumpHeight, uint64 ReloadTime, uint64 LeftKey, uint64 RightKey, uint64 KeyJump, uint8 KeyFire, uint8 ColorR, uint8 ColorG, uint8 ColorB);
uint16 updatePlayer(game* Game);

//Platform
platform* newPlatform(double X, double Y, uint16 Width, uint16 Height, uint8 R, uint8 G, uint8 B);

//Projectile
projectile* newProjectile(double SpawnX, double SpawnY, uint16 Width, uint16 Height, double Speed, uint8 Facing, uint8 ColorR, uint8 ColorG, uint8 ColorB);
uint16 updateProjectile(game* Game);