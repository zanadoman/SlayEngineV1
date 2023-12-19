#include "../SlayEngineV1/SlayEngineV1.h"

#define GRAVITY 0.65

typedef struct gameStruct game;
typedef struct commonTexturesStruct commonTextures;
typedef struct commonFlipbooksStruct commonFlipbooks;
typedef struct commonSoundsStruct commonSounds;

typedef struct scene0Struct scene0;
typedef struct scene1Struct scene1;
typedef struct scene2Struct scene2;

typedef struct platformStruct platform;
typedef struct playerStruct player;
typedef struct eagleStruct eagle;
typedef struct projectileStruct projectile;
typedef struct pauseStruct pause;
typedef struct buttonStruct button;

typedef enum
{
    actBUTTON,
    actPLATFORM,
    actPLAYER,
    actEAGLE,
    actPROJECTILE,
    
    actLENGTH
} actors;

//Loading____________________________________________________________

struct gameStruct
{
    slayFont* FontCrazyPixel;
    uint8 Volume;

    commonTextures* Textures;
    commonFlipbooks* Flipbooks;
    commonSounds* Sounds;
};

struct commonTexturesStruct
{
    slayTexture* playerJump;
    slayTexture* playerFall;

    slayTexture* levelBackground;
    slayTexture* levelMountain;
    slayTexture* levelShroom;
    slayTexture* levelBush;
    slayTexture* levelPlatform;

    slayTexture* projectile;
};
struct commonFlipbooksStruct
{
    slayFlipbook* playerIdle;
    slayFlipbook* playerRun;
    slayFlipbook* playerStunned;

    slayFlipbook* eagleFlying;
    slayFlipbook* eagleDying;
};
struct commonSoundsStruct
{
    slaySound* gunFire;
};

uint8 loadGame(slayEngine* Engine);
uint8 unloadSceneCurrent(slayEngine* Engine);

//Update queue_______________________________________________________

uint8 updateQueue(slayEngine* Engine);

void* updatePlayerThread(void* Engine);
void* updateEagleThread(void* Engine);
void* updateProjectileThread(void* Engine);

//Render queue_______________________________________________________

uint8 renderQueue(slayEngine* Engine);

uint8 renderPlayer(slayEngine* Engine, player* Player);
uint8 renderEagle(slayEngine* Engine, eagle* Eagle);
uint8 renderPause(slayEngine* Engine, pause* Pause);
uint8 renderFrameTime(slayEngine* Engine);

//Scene0_____________________________________________________________

struct scene0Struct
{
    uint8 ColorR;
    uint8 ColorG;
    uint8 ColorB;

    array Buttons;   
};

uint8 updateScene0(slayEngine* Engine);
uint8 renderScene0(slayEngine* Engine);

uint8 loadScene0(slayEngine* Engine);
uint8 unloadScene0(slayEngine* Engine);

//Scene1_____________________________________________________________

struct scene1Struct
{
    pause* Pause;
    logic paused;

    array Platforms;
    player* Player;
    eagle* Eagle;

    array PhysicsLayer;

    array Projectiles;
};

uint8 updateScene1(slayEngine* Engine);
uint8 renderScene1(slayEngine* Engine);

uint8 loadScene1(slayEngine* Engine);
uint8 unloadScene1(slayEngine* Engine);

//Scene2_____________________________________________________________

struct scene2Struct
{
    pause* Pause;
    logic paused;

    array Platforms;
    player* Player;
};

uint8 updateScene2(slayEngine* Engine);
uint8 renderScene2(slayEngine* Engine);

uint8 loadScene2(slayEngine* Engine);
uint8 unloadScene2(slayEngine* Engine);

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

uint8 destroyPlatforms(array Platforms);

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

    slayOverlapbox* Overlapbox;
};

button* newButton(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, char* TextureBase, char* TextureHover);
logic updateButton(slayEngine* Engine, button* Button);
uint8 destroyButton(button* Button);

//Player_____________________________________________________________

struct playerStruct
{
    double X;
    double Y;
    double PrevX;
    double PrevY;

    double MinX;
    double MinY;
    double MaxX;
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
    uint16 ReloadTime;
    uint32 ReloadTick;
    double CenterX;
    double CenterY;

    uint16 KeyLeft;
    uint16 KeyRight;
    uint16 KeyJump;
    uint16 KeyFire;

    logic Alive;
    uint16 RespawnTime;
    uint32 DeathTick;

    slayTexture* TextureCurrent;

    slayHitbox* Hitbox;
};

player* newPlayer(slayEngine* Engine, uint16 KeyLeft, uint16 KeyRight, uint16 KeyJump, uint16 KeyFire);
uint8 updatePlayer(slayEngine* Engine);
uint8 destroyPlayer(player* Player);

//Eagle______________________________________________________________

struct eagleStruct
{
    double X;
    double Y;

    double MinX;
    double MinY;
    double MaxX;
    double MaxY;

    uint16 Width;
    uint16 Height;

    double Speed;
    double Facing;
    double AttackRange;
    uint16 ReloadTime;
    uint32 ReloadTick;

    logic Alive;
    uint16 RespawnTime;
    uint32 DeathTick;

    slayTexture* TextureCurrent;
};

eagle* newEagle(slayEngine* Engine);
uint8 updateEagle(slayEngine* Engine);
uint8 destroyEagle(eagle* Eagle);

//Projectile_________________________________________________________

struct projectileStruct
{
    double X;
    double Y;

    double MinX;
    double MinY;
    double MaxX;
    double MaxY;

    uint16 Width;
    uint16 Height;

    double Speed;
    double Angle;

    actors Parent;

    slayHitbox* Hitbox;
};

uint8 updateProjectile(slayEngine* Engine);
uint8 destroyProjectiles(array Projectiles);

//Menu_______________________________________________________________

uint8 updateMenu(slayEngine* Engine, scene0* Scene);

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
uint8 updatePause(slayEngine* Engine, pause* Pause, logic* Paused);
uint8 destroyPause(pause* Pause);