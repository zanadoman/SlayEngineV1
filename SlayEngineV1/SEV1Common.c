#include "SlayEngineV1.h"

slayDisplay* slayNew(char* Title, int Width, int Height)
{
    slayDisplay* result;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    result = malloc(sizeof(slayDisplay));
    result->Width = Width;
    result->Height = Height;
    result->Window = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, result->Width, result->Height, 0);
    result->Renderer = SDL_CreateRenderer(result->Window, -1, SDL_RENDERER_ACCELERATED);

    return result;
}