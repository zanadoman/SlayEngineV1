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
    slayEngine* Engine;

    uint8 Volume;

    array Platforms;
    player* Player;
    array Projectiles;

    TTF_Font* FontCrazyPixel;
    SDL_Texture* TextureBackground;
    SDL_Texture* TexturePlatform;
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

//Level
platform* newPlatform(double X, double Y, uint16 Width, uint16 Height);

//Projectile
projectile* newProjectile(double SpawnX, double SpawnY, double MinX, double MaxX, uint16 Width, uint16 Height, double Speed, uint8 Facing, uint8 ColorR, uint8 ColorG, uint8 ColorB);
uint16 updateProjectile(game* Game);