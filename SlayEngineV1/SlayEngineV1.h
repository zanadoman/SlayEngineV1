#include "inc/SDL.h"
#include "inc/SDL_image.h"
#include "inc/SDL_ttf.h"
#include "inc/SDL_mixer.h"

#include "NeoTypes/NeoTypes.h"
#include "cJSON/cJSON.h"
#include <pthread.h>

typedef struct slayEngineStruct slayEngine;
typedef struct slayDisplayStruct slayDisplay;
typedef struct slayMouseStruct slayMouse;
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

slayEngine* slayNewEngine(char* Title, uint16 Width, uint16 Height, uint64 Scenes, uint64 Threads, uint16 MaxFPS, char* IconPath);

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

uint8 slayRenderTexture(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, slayTexture* Texture, uint8 Alpha);
uint8 slayRenderTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double Distance, slayTexture* Texture, uint8 Alpha);
uint8 slayRender3DTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, slayTexture* Texture, uint8 Alpha);

uint8 slayRenderText(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, double Size, double Angle, uint8 Flip, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint8 slayRenderTextCamera(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, double Size, double Angle, uint8 Flip, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint8 slayRender3DTextCamera(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, double Size, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);

//Audio______________________________________________________________

#define slaySound Mix_Chunk

slaySound* slayLoadSound(char* Path);
#define slayUnloadSound Mix_FreeChunk

uint8 slayPlaySound(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops);
uint8 slayPlaySoundTicks(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops, uint32 Ticks);
#define slayStopSound Mix_HaltChannel

//Inputs_____________________________________________________________

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
logic slayCursorCollision(slayEngine* Engine, slayHitbox* Hitbox);
logic slayCursorCollisionCamera(slayEngine* Engine, slayHitbox* Hitbox, double Distance);

//Vector_____________________________________________________________

#define PI 3.141592653589793
uint8 slayVectorLength(double X1, double Y1, double X2, double Y2, double* Length);
uint8 slayVectorTranslate(double X1, double Y1, double* X2, double* Y2, double Length, double Angle);
uint8 slayVectorAngle(double X1, double Y1, double X2, double Y2, double* Angle);
logic slayVectorRayCast(double SourceX, double SourceY, double TargetX, double TargetY, slayHitbox* Obstacle);

//Hitbox_____________________________________________________________

typedef enum
{
    slayCollNONE = 0,
    slayCollTOP = 3,
    slayCollRIGHT = 10,
    slayCollBOTTOM = 12,
    slayCollLEFT = 5,
    slayCollTOPLEFT = 1,
    slayCollTOPRIGHT = 2,
    slayCollBOTTOMLEFT = 4,
    slayCollBOTTOMRIGHT = 8,
    slayCollALL = 15
} slayColls;

struct slayHitboxStruct
{
    double* ObjectX;
    double* ObjectY;
    sint32 UpperLeftX;
    sint32 UpperLeftY;
    sint32 LowerRightX;
    sint32 LowerRightY;
};

slayHitbox* slayNewHitbox(double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY);
slayColls slayCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2);

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
#define slayThreadExit pthread_exit(NULL)

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

//Save_______________________________________________________________

#define slayJSON cJSON

#define slayAddJSONKeyNumber cJSON_AddNumberToObject
#define slayAddJSONKeyString cJSON_AddStringToObject
#define slayGetJSONKey cJSON_GetObjectItem

#define slayNewJSON cJSON_CreateObject
slayJSON* slayLoadJSON(char* Path);
uint8 slaySaveJSON(cJSON* JSON, char* Path);
#define slayUnloadJSON cJSON_Delete