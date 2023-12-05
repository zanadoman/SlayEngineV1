//Linux port
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

//Windows port
//#include "inc/SDL.h"
//#include "inc/SDL_image.h"
//#include "inc/SDL_ttf.h"
//#include "inc/SDL_mixer.h"

#include "NeoTypes/NeoTypes.h"
#include <pthread.h>

typedef struct slayEngineStruct slayEngine;
typedef struct slayDisplayStruct slayDisplay;
typedef struct slayMouseStruct slayMouse;
typedef struct slayHitboxStruct slayHitbox;
typedef struct slayCameraStruct slayCamera;
typedef struct flipbookStruct slayFlipbook;

//Common_____________________________________________________________

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

slayEngine* slayNewEngine(char* Title, uint16 Width, uint16 Height, uint64 Scenes, uint64 Threads, uint16 MaxFPS);
uint16 slayLogo();

//Control____________________________________________________________

#define slayGetTicks SDL_GetTicks
logic slayEvent(slayEngine* Engine);
uint16 slayUpdateDeltaTime(slayEngine* Engine);
uint16 slayCapFPS(slayEngine* Engine);
sint64 slayRandom(uint64 Min, uint64 Max, double Seed);

//Render_____________________________________________________________

#define slayTexture SDL_Texture
#define slayFont TTF_Font
#define slayObject SDL_Rect

#define slayFlipNONE SDL_FLIP_NONE
#define slayFlipHORIZONTAL SDL_FLIP_HORIZONTAL
#define slayFlipVERTICAL SDL_FLIP_VERTICAL

slayTexture* slayLoadTexture(slayEngine* Engine, char* Path);
#define slayUnloadTexture SDL_DestroyTexture
slayFont* slayLoadFont(char* Path, int Size);
#define slayUnloadFont TTF_CloseFont

uint16 slayRenderStart(slayEngine* Engine);
uint16 slayRenderEnd(slayEngine* Engine);

uint16 slayRenderColor(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint16 slayRenderColorCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint16 slayRender3DColorCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);

uint16 slayRenderTexture(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, slayTexture* Texture, uint8 Alpha);
uint16 slayRenderTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double Distance, slayTexture* Texture, uint8 Alpha);
uint16 slayRender3DTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, slayTexture* Texture, uint8 Alpha);

uint16 slayRenderText(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, double Size, double Angle, uint8 Flip, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint16 slayRenderTextCamera(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, double Size, double Angle, uint8 Flip, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint16 slayRender3DTextCamera(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, double Size, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);

//Audio______________________________________________________________

#define slaySound Mix_Chunk
#define slayStopSound Mix_HaltChannel
slaySound* slayLoadSound(char* Path);
#define slayUnloadSound Mix_FreeChunk
uint16 slayPlaySound(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops);
uint16 slayPlaySoundTicks(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops, uint64 Ticks);

//Inputs_____________________________________________________________

#define SDL_SCANCODE_LMB 513
#define SDL_SCANCODE_MMB 514
#define SDL_SCANCODE_RMB 515
uint8 slayKey(slayEngine* Engine, uint64 Key);

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
uint16 slayMouseMovement(slayEngine* Engine);
uint16 slayMouseButtons(slayEngine* Engine);
logic slayCursorCollision(slayEngine* Engine, slayHitbox* Hitbox);
logic slayCursorCollisionCamera(slayEngine* Engine, slayHitbox* Hitbox, double Distance);

//Vector_____________________________________________________________

#define PI 3.141592653589793
uint16 slayVectorLength(double X1, double Y1, double X2, double Y2, double* Length);
uint16 slayVectorTranslate(double X1, double Y1, double* X2, double* Y2, double Length, double Angle);
uint16 slayVectorAngle(double X1, double Y1, double X2, double Y2, double* Angle);

//Hitbox_____________________________________________________________

struct slayHitboxStruct
{
    double* ObjectX;
    double* ObjectY;
    sint32 UpperLeftX;
    sint32 UpperLeftY;
    sint32 LowerRightX;
    sint32 LowerRightY;
};

#define slayCollTOP 3
#define slayCollRIGHT 10
#define slayCollBOTTOM 12
#define slayCollLEFT 5
#define slayCollTOPLEFT 1
#define slayCollTOPRIGHT 2
#define slayCollBOTTOMLEFT 4
#define slayCollBOTTOMRIGHT 8
#define slayCollALL 15

slayHitbox* slayNewHitbox(double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY);
uint8 slayCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2);

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

uint16 slaySetCamera(slayEngine* Engine, double* OriginX, double* OriginY, double CenterX, double CenterY, double RelativeX, double RelativeY, double Zoom);
uint16 slayApplyCamera(slayEngine* Engine, slayObject* Object, double X, double Y, uint16 Width, uint16 Height, double Distance);

//Thread_____________________________________________________________

#define slayThreadExit pthread_exit(NULL)
uint16 slayThreadStart(slayEngine* Engine, uint64 ID, void* Function);
uint16 slayThreadWaitExit(slayEngine* Engine, uint64 ID);

//Flipbook___________________________________________________________

struct flipbookStruct
{
    SDL_Texture* *Textures;

    uint64 Current;
    uint64 PrevTick;

    uint64 Delay;
    uint64 Count;
};

slayFlipbook* slayNewFlipbook(slayEngine* Engine, uint64 Delay, uint64 Count, char* Paths, ...);
uint16 slayApplyFlipbook(slayEngine* Engine, slayFlipbook* Flipbook, slayTexture** Target);
uint16 slayPurgeFlipbook(slayFlipbook* Flipbook);