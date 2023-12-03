#include "SlayEngineV1/SlayEngineV1.h"

#define GRAVITY 0.65

typedef struct
{
    double X;
    double Y;

    uint16 Width;
    uint16 Height;

    slayTexture* TextureBase;
    slayTexture* TextureHover;
    slayTexture* TextureCurrent;

    slayHitbox* Hitbox;
} button;

typedef struct
{
    double X;
    double Y;

    uint16 Width;
    uint16 Height;

    uint8 ColorR;
    uint8 ColorG;
    uint8 ColorB;
    uint8 ColorA;

    button* ButtonResume;
    button* ButtonQuit;
} pause;

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

    slayTexture* TextureBase;

    slaySound* SoundFire;

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
    uint8 ColorR;
    uint8 ColorG;
    uint8 ColorB;

    button* ButtonScene1;    
} scene0;

typedef struct
{
    pause* Pause;
    logic paused;

    array Platforms;
    slayTexture* TextureBackground;
    slayTexture* TexturePlatform;

    player* Player;

    array Projectiles;
} scene1;

typedef struct
{
    slayFont* FontCrazyPixel;
    uint8 Volume;
    slayTexture* TextureProjectile;
} game;


//Menu
uint16 updateMenu(slayEngine* Engine, scene0* Scene);

//Loading
uint16 loadGame(slayEngine* Engine);

uint16 loadScene0(slayEngine* Engine);
uint16 unloadScene0(slayEngine* Engine);

uint16 loadScene1(slayEngine* Engine);
uint16 unloadScene1(slayEngine* Engine);

//Update queue
uint16 updateQueue(slayEngine* Engine);

//Render queue
uint16 renderQueue(slayEngine* Engine);

//Player
player* newPlayer();
uint16 updatePlayer(slayEngine* Engine, player* Player, array Platforms);

//Level
platform* newPlatform(double X, double Y, uint16 Width, uint16 Height);

//Projectile
projectile* newProjectile(double SpawnX, double SpawnY, double MinX, double MaxX, double MinY, double MaxY, uint16 Width, uint16 Height, double Speed, double Angle);
uint16 updateProjectile(slayEngine* Engine, array Projectiles, player* Player, array Platforms);

//Pause
pause* newPause();
uint16 updatePause(slayEngine* Engine, pause* Pause, logic* Paused);