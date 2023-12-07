#include "../SlayEngineV1/SlayEngineV1.h"

#define GRAVITY 0.65

typedef struct buttonStruct button;
typedef struct gameStruct game;
typedef struct scene0Struct scene0;
typedef struct scene1Struct scene1;
typedef struct scene2Struct scene2;
typedef struct platformStruct platform;
typedef struct playerStruct player;
typedef struct eagleStruct eagle;
typedef struct projectileStruct projectile;
typedef struct pauseStruct pause;

typedef enum
{
    PLAYER,
    EAGLE,
    PROJECTILE,
} actors;

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
void* updateEagleThread(void* Engine);
void* updateProjectileThread(void* Engine);

//Render queue_______________________________________________________

uint16 renderQueue(slayEngine* Engine);

uint16 renderPlayer(slayEngine* Engine, player* Player);
uint16 renderEagle(slayEngine* Engine, eagle* Eagle);
uint16 renderPause(slayEngine* Engine, pause* Pause);
uint16 renderFrameTime(slayEngine* Engine);

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

    slaySound* SoundFire;

    player* Player;
    eagle* Eagle;

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

//Button_____________________________________________________________

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

button* newButton(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, char* TextureBase, char* TextureHover);
logic updateButton(slayEngine* Engine, button* Button);
uint16 destroyButton(button* Button);

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
    double CenterX;
    double CenterY;

    uint64 KeyLeft;
    uint64 KeyRight;
    uint64 KeyJump;
    uint64 KeyFire;

    logic Alive;
    uint64 RespawnTime;
    uint64 DeathTick;

    slayFlipbook* FlipbookIdle;
    slayFlipbook* FlipbookRun;
    slayFlipbook* FlipbookStunned;
    slayTexture* TextureJump;
    slayTexture* TextureFall;
    slayTexture* TextureCurrent;

    slayHitbox* Hitbox;
};

player* newPlayer(slayEngine* Engine, uint64 KeyLeft, uint64 KeyRight, uint64 KeyJump, uint64 KeyFire);
uint16 updatePlayer(slayEngine* Engine, player* Player, array Platforms);
uint16 destroyPlayer(player* Player);

//Eagle______________________________________________________________

struct eagleStruct
{
    double X;
    double Y;

    double MinX;
    double MaxX;
    double MinY;
    double MaxY;

    uint16 Width;
    uint16 Height;

    double Speed;
    double Facing;
    double AttackRange;
    uint64 ReloadTime;
    uint64 ReloadTick;

    logic Alive;
    uint64 RespawnTime;
    uint64 DeathTick;

    slayFlipbook* FlipbookFlying;
    slayFlipbook* FlipbookDying;
    slayTexture* TextureCurrent;
    
    slayHitbox* Hitbox;
};

eagle* newEagle(slayEngine* Engine);
uint16 updateEagle(slayEngine* Engine, eagle* Eagle);
uint16 destroyEagle(eagle* Eagle);

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

    actors Parent;

    slayHitbox* Hitbox;
};

projectile* newProjectile(double SpawnX, double SpawnY, double MinX, double MaxX, double MinY, double MaxY, double Angle, actors Parent);
uint16 updateProjectile(slayEngine* Engine, array Projectiles, player* Player, eagle* Eagle, array Platforms, slaySound* SoundFire);
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

    logic Pressed;

    uint8 ColorR;
    uint8 ColorG;
    uint8 ColorB;
    uint8 ColorA;

    array Buttons;
};

pause* newPause(slayEngine* Engine);
uint16 updatePause(slayEngine* Engine, pause* Pause, logic* Paused);
uint16 destroyPause(pause* Pause);