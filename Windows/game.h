#include "SlayEngineV1/SlayEngineV1.h"

#define GRAVITY 0.65

typedef struct
{
    double X;
    double Y;

    double MinX;
    double MaxX;
    double MinY;
    double MaxY;

    uint16 Width;
    uint16 Height;

    double AccelerationX;
    double AccelerationRateX;
    double DeaccelerationRateX;
    double AccelerationY;
    double AccelerationRateY;
    double DeaccelerationRateY;

    double Speed;
    double JumpHeight;
    sint8 Facing;
    uint64 ReloadTime;
    uint64 ReloadTick;

    uint64 KeyLeft;
    uint64 KeyRight;
    uint64 KeyJump;
    uint64 KeyFire;

    SDL_Texture* TextureLeft;
    SDL_Texture* TextureRight;

    Mix_Chunk* SoundFire;

    slayHitbox* Hitbox;

    double ProjectileRelativeX;
    double ProjectileRelativeY;
    uint16 ProjectileWidth;
    uint16 ProjectileHeight;
    double ProjectileSpeed;
    uint8 ProjectileColorR;
    uint8 ProjectileColorG;
    uint8 ProjectileColorB;
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

    double MinX;
    double MaxX;

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
    slayDisplay* Display;
    array Threads;
    uint64 DeltaTime;
    uint64 DisplayPrevTick;
    uint8 Volume;

    TTF_Font* FontCrazyPixel;
    slayCamera* Camera;
    array Platforms;
    player* Player;
    array Projectiles;

    SDL_Texture* TextureBackground;
} game;

//Load queue
uint16 loadGame(game* Game);

//Update queue
uint16 updateQueue(game* Game);

//Render queue
uint16 renderQueue(game* Game);

//Player
player* newPlayer();
uint16 updatePlayer(game* Game);

//Platform
platform* newPlatform(double X, double Y, uint16 Width, uint16 Height, uint8 R, uint8 G, uint8 B);

//Projectile
projectile* newProjectile(double SpawnX, double SpawnY, double MinX, double MaxX, uint16 Width, uint16 Height, double Speed, uint8 Facing, uint8 ColorR, uint8 ColorG, uint8 ColorB);
uint16 updateProjectile(game* Game);