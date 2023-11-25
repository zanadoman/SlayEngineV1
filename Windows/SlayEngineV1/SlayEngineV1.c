#include "SlayEngineV1.h"

display* slayNew(char* Title, int X, int Y)
{
    display* result;

    SDL_Init(SDL_INIT_VIDEO);
    result = malloc(sizeof(display));
    result->X = X;
    result->Y = Y;
    result->Window = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, result->X, result->Y, 0);
    result->Renderer = SDL_CreateRenderer(result->Window, -1, SDL_RENDERER_ACCELERATED);

    return result;
}

sint64 slayEvent(display* Display)
{
    while (SDL_PollEvent(&Display->Event) != 0)
    {
        switch (Display->Event.type)
        {
            case SDL_QUIT:
                SDL_Quit();
                return 0;
        }
    }

    return -1;
}

uint8 slayKey(display* Display, uint64 Key)
{
    SDL_PollEvent(&Display->Event);
    const uint8 *state = SDL_GetKeyboardState(NULL);

    return state[Key];
}

uint64 slayDeltaTime(uint64* DisplayPrevTick)
{
    uint64 DeltaTime;
    
    DeltaTime = SDL_GetTicks() - *DisplayPrevTick;
    *DisplayPrevTick = SDL_GetTicks();

    return DeltaTime;
}

uint16 slayFPS(uint64 FPS, uint64 DisplayPrevTick)
{
    sint64 delay;

    delay = (sint64)round((DisplayPrevTick + 1000.0 / FPS) - SDL_GetTicks());
    if (delay > 0)
    {
        SDL_Delay(delay);
    }

    return 0;
}

uint8 slayCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2)
{
    uint8 result;

    uint64 Hitbox1UpperLeftX;
    uint64 Hitbox1UpperLeftY;
    uint64 Hitbox1LowerRightX;
    uint64 Hitbox1LowerRightY;

    uint64 Hitbox2UpperLeftX;
    uint64 Hitbox2UpperLeftY;
    uint64 Hitbox2LowerRightX;
    uint64 Hitbox2LowerRightY;

    Hitbox1UpperLeftX = Hitbox1->UpperLeftX + (sint32)round(*Hitbox1->ObjectX);
    Hitbox1UpperLeftY = Hitbox1->UpperLeftY + (sint32)round(*Hitbox1->ObjectY);
    Hitbox1LowerRightX = Hitbox1->LowerRightX + (sint32)round(*Hitbox1->ObjectX);
    Hitbox1LowerRightY = Hitbox1->LowerRightY + (sint32)round(*Hitbox1->ObjectY);

    Hitbox2UpperLeftX = Hitbox2->UpperLeftX + (sint32)round(*Hitbox2->ObjectX);
    Hitbox2UpperLeftY = Hitbox2->UpperLeftY + (sint32)round(*Hitbox2->ObjectY);
    Hitbox2LowerRightX = Hitbox2->LowerRightX + (sint32)round(*Hitbox2->ObjectX);
    Hitbox2LowerRightY = Hitbox2->LowerRightY + (sint32)round(*Hitbox2->ObjectY);

    result = 0;
    if (((Hitbox1UpperLeftX <= Hitbox2LowerRightX && Hitbox2LowerRightX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2LowerRightY && Hitbox2LowerRightY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1UpperLeftX && Hitbox1UpperLeftX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1UpperLeftY && Hitbox1UpperLeftY <= Hitbox2LowerRightY)))
    {
        result = result | 1;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2UpperLeftX && Hitbox2UpperLeftX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2LowerRightY && Hitbox2LowerRightY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1LowerRightX && Hitbox1LowerRightX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1UpperLeftY && Hitbox1UpperLeftY <= Hitbox2LowerRightY)))
    {
        result = result | 2;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2LowerRightX && Hitbox2LowerRightX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2UpperLeftY && Hitbox2UpperLeftY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1UpperLeftX && Hitbox1UpperLeftX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1LowerRightY && Hitbox1LowerRightY <= Hitbox2LowerRightY)))
    {
        result = result | 4;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2UpperLeftX && Hitbox2UpperLeftX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2UpperLeftY && Hitbox2UpperLeftY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1LowerRightX && Hitbox1LowerRightX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1LowerRightY && Hitbox1LowerRightY <= Hitbox2LowerRightY)))
    {
        result = result | 8;
    }

    return result;
}

slayHitbox* slayNewHitbox(double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY)
{
    slayHitbox* result;

    result = malloc(sizeof(slayHitbox));

    result->ObjectX = ObjectX;
    result->ObjectY = ObjectY;
    result->UpperLeftX = UpperLeftX;
    result->UpperLeftY = UpperLeftY;
    result->LowerRightX = LowerRightX;
    result->LowerRightY = LowerRightY;

    return result;
}

uint64 slayRandom(uint64 Min, uint64 Max, double Seed)
{
    return (uint64)round(SDL_GetTicks64() / Seed) % (Max - Min) + Min;
}