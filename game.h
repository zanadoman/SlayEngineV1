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

    SDL_Texture* TextureBase;

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

    slayHitbox* Hitbox;
} platform;

typedef struct
{
    double X;
    double Y;

    double MinX;
    double MaxX;
    double MixY;
    double MaxY;

    uint16 Width;
    uint16 Height;

    double Speed;
    double Angle;

    slayHitbox* Hitbox;
} projectile;

typedef struct
{
    array Platforms;
    SDL_Texture* TextureBackground;
    SDL_Texture* TexturePlatform;

    player* Player;

    array Projectiles;
} scene0;

typedef struct
{
    TTF_Font* FontCrazyPixel;
    uint8 Volume;
    SDL_Texture* TextureProjectile;
} game;


//Load queue
uint16 loadQueue(slayEngine* Engine);

//Update queue
uint16 updateQueue(slayEngine* Engine);

//Render queue
uint16 renderQueue(slayEngine* Engine);

//Player
player* newPlayer();
uint16 updatePlayer(slayEngine* Engine, player* Player, array Platforms, uint64 DeltaTime);

//Level
platform* newPlatform(double X, double Y, uint16 Width, uint16 Height);

//Projectile
projectile* newProjectile(double SpawnX, double SpawnY, double MinX, double MaxX, double MinY, double MaxY, uint16 Width, uint16 Height, double Speed, double Angle);
uint16 updateProjectile(slayEngine* Engine, array Projectiles, player* Player, array Platforms, uint8 Volume, uint64 DeltaTime);