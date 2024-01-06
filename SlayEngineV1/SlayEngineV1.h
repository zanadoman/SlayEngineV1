#include "Includes/SDL.h"
#include "Includes/SDL_image.h"
#include "Includes/SDL_ttf.h"
#include "Includes/SDL_mixer.h"

#include "Includes/NeoTypes.h"

#define EPSILON 0.0001
#define PI 3.141592653589793

typedef struct slayEngineStruct slayEngine;
typedef struct slayDisplayStruct slayDisplay;
typedef struct slayParticleBatchStruct slayParticleBatch;
typedef struct slayParticleStruct slayParticle;
typedef struct slayMouseStruct slayMouse;
typedef struct slayOverlapboxStruct slayOverlapbox;
typedef struct slayHitboxStruct slayHitbox;
typedef struct slayCameraStruct slayCamera;
typedef struct flipbookStruct slayFlipbook;

//Engine_____________________________________________________________

struct slayEngineStruct
{
    slayDisplay* Display;
    slayCamera* Camera;
    slayMouse* Mouse;

    array Threads;

    uint64 PrevTick;
    uint64 DeltaTime;
    uint64 MaxFPS;

    array Scenes;
    uint64 CurrentScene;

    void* Game;
};

struct slayDisplayStruct
{
    uint16 Width;
    uint16 Height;
    SDL_Window *Window;
    SDL_Renderer *Renderer;
    SDL_Event Event;
};

slayEngine* slayNewEngine(char* Title, uint16 Width, uint16 Height, uint64 Scenes, uint16 MaxFPS, char* IconPath);

//Control____________________________________________________________

#define slayGetTicks SDL_GetTicks

logic slayUpdate(slayEngine* Engine);
uint8 slayCapFPS(slayEngine* Engine);
sint64 slayRandom(sint64 Min, sint64 Max, double Seed);

//Render_____________________________________________________________

#define slayTexture SDL_Texture
#define slayFont TTF_Font
#define slayObject SDL_Rect

#define slayFlipNONE SDL_FLIP_NONE
#define slayFlipHORIZONTAL SDL_FLIP_HORIZONTAL
#define slayFlipVERTICAL SDL_FLIP_VERTICAL

slayTexture* slayLoadTexture(slayEngine* Engine, char* Path);
#define slayUnloadTexture SDL_DestroyTexture
slayFont* slayLoadFont(char* Path, uint8 Size);
#define slayUnloadFont TTF_CloseFont

uint8 slayRenderStart(slayEngine* Engine);
uint8 slayRenderEnd(slayEngine* Engine);

uint8 slayRenderColor(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint8 slayRenderColorCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint8 slayRender3DColorCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);

uint8 slayRenderTexture(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, slayTexture* Texture, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 Alpha);
uint8 slayRenderTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double Distance, slayTexture* Texture, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 Alpha);
uint8 slayRender3DTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, slayTexture* Texture, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 Alpha);

uint8 slayRenderText(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, uint16 Height, double Angle, uint8 Flip, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint8 slayRenderTextCamera(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, uint16 Height, double Angle, uint8 Flip, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint8 slayRender3DTextCamera(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, uint16 Height, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);

//Particle___________________________________________________________

struct slayParticleBatchStruct
{
    slayParticle* *Particles;
    uint64 Count;

    uint16 MinWidth;
    uint16 MaxWidth;
    uint16 MinHeight;
    uint16 MaxHeight;

    double MinSpeed;
    double MaxSpeed;

    double MinAngle;
    double MaxAngle;

    uint64 MinLifeTime;
    uint64 MaxLifeTime;

    SDL_Texture* Texture;

    uint8 MinColorR;
    uint8 MaxColorR;
    uint8 MinColorG;
    uint8 MaxColorG;
    uint8 MinColorB;
    uint8 MaxColorB;

    uint8 MinAlpha;
    uint8 MaxAlpha;
};

struct slayParticleStruct
{
    double X;
    double Y;

    uint16 Width;
    uint16 Height;

    double Speed;
    double Angle;

    uint64 LifeTime;

    uint8 ColorR;
    uint8 ColorG;
    uint8 ColorB;

    uint8 Alpha;
};

//Audio______________________________________________________________

#define slaySound Mix_Chunk

slaySound* slayLoadSound(char* Path);
#define slayUnloadSound Mix_FreeChunk

uint8 slayPlaySound(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops);
uint8 slayPlaySoundTicks(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops, uint32 Ticks);
#define slayStopSound Mix_HaltChannel

//Input______________________________________________________________

#define SDL_SCANCODE_LMB 513
#define SDL_SCANCODE_MMB 514
#define SDL_SCANCODE_RMB 515
#define SDL_SCANCODE_WHEELUP 516
#define SDL_SCANCODE_WHEELDOWN 517

logic slayKey(slayEngine* Engine, uint16 Key);

//Mouse______________________________________________________________

struct slayMouseStruct
{
    sint32 X;
    sint32 Y;
    sint32 MovementX;
    sint32 MovementY;
    logic LMB;
    logic MMB;
    logic RMB;
    sint8 Wheel;
};

#define slayMouseRelative SDL_SetRelativeMouseMode
uint8 slayMouseMovement(slayEngine* Engine);
uint8 slayMouseButtons(slayEngine* Engine);
logic slayCursorCollision(slayEngine* Engine, slayOverlapbox* Hitbox);
logic slayCursorCollisionCamera(slayEngine* Engine, slayOverlapbox* Overlapbox, double Distance);

//Vector_____________________________________________________________

uint8 slayVectorLength(double X1, double Y1, double X2, double Y2, double* Length);
uint8 slayVectorTranslate(double X1, double Y1, double* X2, double* Y2, double Length, double Angle);
uint8 slayVectorAngle(double X1, double Y1, double X2, double Y2, double* Angle);
logic slayVectorRayCastCoordinate(double SourceX, double SourceY, double TargetX, double TargetY, uint16 Size, double Precision, array OverlapLayer);
logic slayVectorRayCastOverlapbox(double SourceX, double SourceY, slayOverlapbox* Target, uint16 Size, double Precision, array OverlapLayer);

//Collision__________________________________________________________

typedef enum
{
    slayColl_NONE = 0,

    slayColl_TOP = 1,
    slayColl_BOTTOM = 2,
    slayColl_LEFT = 4,
    slayColl_RIGHT = 8,

    slayColl_TOP_LEFT = 16,
    slayColl_TOP_RIGHT = 32,
    slayColl_BOT_LEFT = 64,
    slayColl_BOT_RIGHT = 128
} slayCollision;

struct slayOverlapboxStruct
{
    void* Parent;
    uint64 ParentType;

    double* ObjectX;
    double* ObjectY;

    sint32 UpperLeftX;
    sint32 UpperLeftY;
    sint32 LowerRightX;
    sint32 LowerRightY;
};

struct slayHitboxStruct
{
    void* Parent;
    uint64 ParentType;

    double* ObjectX;
    double* ObjectY;
    double ObjectPrevX;
    double ObjectPrevY;

    sint32 UpperLeftX;
    sint32 UpperLeftY;
    sint32 LowerRightX;
    sint32 LowerRightY;

    uint16 Force;
    uint16 Resistance;
};

slayOverlapbox* slayNewOverlapbox(void* Parent, uint64 ParentType, double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY);
slayHitbox* slayNewHitbox(void* Parent, uint64 ParentType, double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY, uint16 Force, uint16 Resistance);

logic slayCheckOverlap(slayOverlapbox* Overlapbox1, slayOverlapbox* Overlapbox2);
logic slayCheckCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2);

slayCollision slayGetCollisionDirection(slayHitbox* Hitbox1, slayHitbox* Hitbox2);
uint8 slayResolveCollisionLayer(array CollisionLayer);

uint8 slayRenderOverlapbox(slayEngine* Engine, slayOverlapbox* Overlapbox, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint8 slayRenderOverlapboxCamera(slayEngine* Engine, slayOverlapbox* Overlapbox, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint8 slayRenderHitbox(slayEngine* Engine, slayHitbox* Hitbox, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint8 slayRenderHitboxCamera(slayEngine* Engine, slayHitbox* Hitbox, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);

//Camera_____________________________________________________________

struct slayCameraStruct
{
    double* OriginX;
    double* OriginY;
    double CenterX;
    double CenterY;
    double RelativeX;
    double RelativeY;
    double AbsoluteX;
    double AbsoluteY;

    double Zoom;
};

uint8 slaySetCamera(slayEngine* Engine, double* OriginX, double* OriginY, double CenterX, double CenterY, double RelativeX, double RelativeY, double Zoom);
uint8 slayApplyCamera(slayEngine* Engine, slayObject* Object, double X, double Y, uint16 Width, uint16 Height, double Distance);

//Thread_____________________________________________________________

uint8 slayThreadStart(slayEngine* Engine, uint64 ID, void* Function);
uint8 slayThreadWaitExit(slayEngine* Engine, uint64 ID);
uint8 slayThreadClearBuffer(slayEngine* Engine);

//Flipbook___________________________________________________________

struct flipbookStruct
{
    SDL_Texture* *Textures;

    uint64 Current;
    uint64 PrevTick;

    uint64 Delay;
    uint64 Count;
};

slayFlipbook* slayNewFlipbook(slayEngine* Engine, uint32 Delay, uint64 Count, char* Paths, ...);
uint8 slayResetFlipbook(slayFlipbook* Flipbook);
slayTexture* slayPlayFlipbook(slayFlipbook* Flipbook);
slayTexture* slayLoopFlipbook(slayFlipbook* Flipbook);
uint8 slayDestroyFlipbook(slayFlipbook* Flipbook);