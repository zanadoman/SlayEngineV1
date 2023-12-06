#include "SlayEngineV1/SlayEngineV1.h"

#define GRAVITY 0.65

typedef struct buttonStruct button;
typedef struct gameStruct game;
typedef struct scene0Struct scene0;
typedef struct scene1Struct scene1;
typedef struct scene2Struct scene2;
typedef struct platformStruct platform;
typedef struct playerStruct player;
typedef struct projectileStruct projectile;
typedef struct pauseStruct pause;

struct buttonStruct
{
    double X;
    double Y;

    uint16 Width;
    uint16 Height;

    logic Pressed;

    slayTexture* TextureBase;
    slayTexture* TextureHover;
    slayTexture* TextureCurrent;

    slayHitbox* Hitbox;
};

//Loading____________________________________________________________

struct gameStruct
{
    slayFont* FontCrazyPixel;
    uint8 Volume;
    slayTexture* TextureProjectile;
};

uint16 loadGame(slayEngine* Engine);
uint16 unloadSceneCurrent(slayEngine* Engine);

//Update queue_______________________________________________________

uint16 updateQueue(slayEngine* Engine);

void* updatePlayerThread(void* Engine);
void* updateProjectileThread(void* Engine);

//Render queue_______________________________________________________

uint16 renderQueue(slayEngine* Engine);

//Scene0_____________________________________________________________

struct scene0Struct
{
    uint8 ColorR;
    uint8 ColorG;
    uint8 ColorB;

    array Buttons;   
};

uint16 updateScene0(slayEngine* Engine, scene0* Scene);
uint16 renderScene0(slayEngine* Engine, scene0* Scene);

uint16 loadScene0(slayEngine* Engine);
uint16 unloadScene0(slayEngine* Engine);

//Scene1_____________________________________________________________

struct scene1Struct
{
    pause* Pause;
    logic paused;

    array Platforms;
    slayTexture* TextureBackground;
    slayTexture* TextureMountain;
    slayTexture* TextureShroom;
    slayTexture* TextureBush;
    slayTexture* TexturePlatform;

    player* Player;

    array Projectiles;
};

uint16 updateScene1(slayEngine* Engine, scene1* Scene);
uint16 renderScene1(slayEngine* Engine, scene1* Scene);

uint16 loadScene1(slayEngine* Engine);
uint16 unloadScene1(slayEngine* Engine);

//Scene2_____________________________________________________________

struct scene2Struct
{
    pause* Pause;
    logic paused;

    array Platforms;
    slayTexture* TextureBackground;
    slayTexture* TexturePlatform;

    player* Player;
};

uint16 updateScene2(slayEngine* Engine, scene2* Scene);
uint16 renderScene2(slayEngine* Engine, scene2* Scene);

uint16 loadScene2(slayEngine* Engine);
uint16 unloadScene2(slayEngine* Engine);

//Level______________________________________________________________

struct platformStruct
{
    double X;
    double Y;

    uint16 Width;
    uint16 Height;

    slayHitbox* Hitbox;
};

platform* newPlatform(double X, double Y, uint16 Width, uint16 Height);
uint16 destroyPlatforms(array Platforms);

//Common_____________________________________________________________

uint16 renderFrameTime(slayEngine* Engine);

//Player_____________________________________________________________

struct playerStruct
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

    slayFlipbook* FlipbookIdle;
    slayFlipbook* FlipbookRun;
    slayTexture* TextureJump;
    slayTexture* TextureFall;
    slayTexture* TextureCurrent;
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
};

player* newPlayer(slayEngine* Engine, uint64 KeyLeft, uint64 KeyRight, uint64 KeyJump, uint64 KeyFire);
uint16 updatePlayer(slayEngine* Engine, player* Player, array Platforms);
uint16 renderPlayer(slayEngine* Engine, player* Player);
uint16 destroyPlayer(player* Player);

//Projectile_________________________________________________________

struct projectileStruct
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
};

projectile* newProjectile(double SpawnX, double SpawnY, double MinX, double MaxX, double MinY, double MaxY, uint16 Width, uint16 Height, double Speed, double Angle);
uint16 updateProjectile(slayEngine* Engine, array Projectiles, player* Player, array Platforms);
uint16 destroyProjectiles(array Projectiles);

//Menu_______________________________________________________________

uint16 updateMenu(slayEngine* Engine, scene0* Scene);

//Pause______________________________________________________________

struct pauseStruct
{
    double X;
    double Y;

    uint16 Width;
    uint16 Height;

    uint8 ColorR;
    uint8 ColorG;
    uint8 ColorB;
    uint8 ColorA;

    array Buttons;
};

pause* newPause(slayEngine* Engine);
uint16 updatePause(slayEngine* Engine, pause* Pause, logic* Paused);
uint16 renderPause(slayEngine* Engine, pause* Pause);
uint16 destroyPause(pause* Pause);