#include <SDL2/SDL.h> //UNIX PORT
#include <SDL2/SDL_image.h> //UNIX PORT
#include <SDL2/SDL_ttf.h> //UNIX PORT
//#include "inc/SDL.h" //WINDOWS PORT
//#include "inc/SDL_image.h" //WINDOWS PORT
//#include "inc/SDL_ttf.h" //WINDOWS PORT
#include <pthread.h>
#include "NeoTypes/NeoTypes.h"

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
    double RelativeX;
    double RelativeY;
    double AbsoluteX;
    double AbsoluteY;
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

//Common_____________________________________________________________

slayDisplay* slayNew(char* Title, int Width, int Height);

//Control____________________________________________________________

sint64 slayEvent(slayDisplay* Display);
uint64 slayDeltaTime(uint64 *DisplayPrevTick);
uint16 slayFPS(uint64 FPS, uint64 DisplayPrevTick);
uint64 slayRandom(uint64 Min, uint64 Max, double Seed);

//Render_____________________________________________________________

SDL_Texture* slayLoadTexture(slayDisplay* Display, char* Path);
TTF_Font* slayLoadFont(char* Path, int Size);
uint16 slayRenderStart(slayDisplay* Display, uint8 ColorR, uint8 ColorG, uint8 ColorB);
uint16 slayRenderEnd(slayDisplay* Display);
uint16 slayRenderColor(slayDisplay* Display, double X, double Y, uint16 Width, uint16 Height, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);
uint16 slayRenderColorCamera(slayDisplay* Display, double X, double Y, uint16 Width, uint16 Height, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA, slayCamera* Camera);
uint16 slayRenderTexture(slayDisplay* Display, double X, double Y, uint16 Width, uint16 Height, SDL_Texture* Texture);
uint16 slayRenderTextureCamera(slayDisplay* Display, double X, double Y, uint16 Width, uint16 Height, SDL_Texture* Texture, slayCamera* Camera);
SDL_Texture* slayTextTexture(slayDisplay* Display, TTF_Font* Font, char* Characters, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA);

//Inputs_____________________________________________________________

uint8 slayKey(slayDisplay* Display, uint64 Key);

//Hitbox_____________________________________________________________

slayHitbox* slayNewHitbox(double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY);
uint8 slayCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2);

//Camera_____________________________________________________________

slayCamera* slayNewCamera(double* OriginX, double* OriginY, double RelativeX, double RelativeY);
uint16 slayUpdateCamera(slayCamera* Camera);
uint16 slayApplyCamera(SDL_Rect* Object, slayCamera* Camera, double X, double Y);