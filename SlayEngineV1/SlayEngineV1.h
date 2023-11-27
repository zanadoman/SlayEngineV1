#include <SDL2/SDL.h> //UNIX PORT
#include <SDL2/SDL_image.h> //UNIX PORT
//#include "inc/SDL.h" //WINDOWS PORT
//#include "inc/SDL_image.h" //WINDOWS PORT
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
} display;

typedef struct
{
    double* ObjectX;
    double* ObjectY;
    sint32 UpperLeftX;
    sint32 UpperLeftY;
    sint32 LowerRightX;
    sint32 LowerRightY;
} slayHitbox;

display* slayNew(char* Title, int Width, int Height);
sint64 slayEvent(display* Display);
uint8 slayKey(display* Display, uint64 Key);
uint64 slayDeltaTime(uint64 *DisplayPrevTick);
uint16 slayFPS(uint64 FPS, uint64 DisplayPrevTick);
uint8 slayCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2);
slayHitbox* slayNewHitbox(double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY);
uint64 slayRandom(uint64 Min, uint64 Max, double Seed);