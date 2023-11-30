#include "inc/SDL.h"
#include "inc/SDL_image.h"
#include "inc/SDL_ttf.h"
#include "inc/SDL_mixer.h"
#include "NeoTypes/NeoTypes.h"
#include <pthread.h>

#define slayGetTicks SDL_GetTicks
#define slayMouseRelative SDL_SetRelativeMouseMode

#define TOP 3
#define RIGHT 10
#define BOTTOM 12
#define LEFT 5
#define TOPLEFT 1
#define TOPRIGHT 2
#define BOTTOMLEFT 4
#define BOTTOMRIGHT 8
#define ALL 15

typedef struct
{
    uint16 Width;
    uint16 Height;
    SDL_Window *Window;
    SDL_Renderer *Renderer;
    SDL_Event Event;
} slayDisplay;

typedef struct
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
} slayCamera;

typedef struct
{
    double* ObjectX;
    double* ObjectY;
    sint32 UpperLeftX;
    sint32 UpperLeftY;
    sint32 LowerRightX;
    sint32 LowerRightY;
} slayHitbox;

typedef struct
{
    sint32 X;
    sint32 Y;
    sint32 MovementX;
    sint32 MovementY;
    logic LMB;
    logic MMB;
    logic RMB;
    sint8 Wheel;
} slayMouse;

typedef struct
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
} slayEngine;


//Common_____________________________________________________________

slayEngine* slayNewEngine(char* Title, uint16 Width, uint16 Height, uint64 Scenes, uint64 Threads, uint16 MaxFPS);

//Control____________________________________________________________

logic slayEvent(slayEngine* Engine);
uint16 slayUpdateDeltaTime(slayEngine* Engine);
uint16 slayCapFPS(slayEngine* Engine);
uint64 slayRandom(uint64 Min, uint64 Max, double Seed);

//Render_____________________________________________________________

SDL_Texture* slayLoadTexture(slayEngine* Engine, char* Path);
TTF_Font* slayLoadFont(char* Path, int Size);

uint16 slayRenderStart(slayEngine* Engine);
uint16 slayRenderEnd(slayEngine* Engine);

uint16 slayRenderColor(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint16 slayRenderColorCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint16 slayRender3DColorCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);

uint16 slayRenderTexture(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, SDL_Texture* Texture);
uint16 slayRenderTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Distance, SDL_Texture* Texture);
uint16 slayRender3DTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double FirstLayer, double Depth, double Quality, SDL_Texture* Texture);

uint16 slayRenderText(slayEngine* Engine, TTF_Font* Font, char* Characters, double X, double Y, double Size, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint16 slayRenderTextCamera(slayEngine* Engine, TTF_Font* Font, char* Characters, double X, double Y, double Size, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint16 slayRender3DTextCamera(slayEngine* Engine, TTF_Font* Font, char* Characters, double X, double Y, double Size, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);

//Audio______________________________________________________________

Mix_Chunk* slayLoadSound(char* Path);
uint16 slayPlaySound(Mix_Chunk* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops);
uint16 slayPlaySoundTicks(Mix_Chunk* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops, uint64 Ticks);
uint16 slayStopSound(sint16 Channel);

//Inputs_____________________________________________________________

uint8 slayKey(uint64 Key);

//Mouse______________________________________________________________

uint16 slayMouseMovement(slayEngine* Engine);
uint16 slayMouseButtons(slayEngine* Engine);
logic slayCursorCollision(slayEngine* Engine, slayHitbox* Hitbox);
logic slayCursorCollisionCamera(slayEngine* Engine, slayHitbox* Hitbox, double Distance);

//Hitbox_____________________________________________________________

slayHitbox* slayNewHitbox(double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY);
uint8 slayCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2);

//Camera_____________________________________________________________

slayCamera* slayNewCamera(double* OriginX, double* OriginY, double CenterX, double CenterY, double RelativeX, double RelativeY, double Zoom);
uint16 slayApplyCamera(slayEngine* Engine, SDL_Rect* Object, double X, double Y, uint16 Width, uint16 Height, double Distance);