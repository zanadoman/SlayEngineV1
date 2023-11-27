#include "SlayEngineV1.h"

slayDisplay* slayNew(char* Title, int Width, int Height)
{
    slayDisplay* result;

    SDL_Init(SDL_INIT_VIDEO);
    result = malloc(sizeof(slayDisplay));
    result->Width = Width;
    result->Height = Height;
    result->Window = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, result->Width, result->Height, 0);
    result->Renderer = SDL_CreateRenderer(result->Window, -1, SDL_RENDERER_ACCELERATED);

    return result;
}

uint16 slayRender(slayDisplay* Display, double X, double Y, uint16 Width, uint16 Height, SDL_Texture* Texture, slayCamera* Camera)
{
    SDL_Rect Object;

    slayApplyCamera(&Object, Camera, X, Y);
    Object.w = Width;
    Object.h = Height;
    SDL_RenderCopy(Display->Renderer, Texture, NULL, &Object);

    return 0;
}