#include "SlayEngineV1.h"

//Creates a window with the specified title and size
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

SDL_Texture* slayLoadTexture(slayDisplay* Display, char* Path)
{
    SDL_Texture* result;

    SDL_Surface* surface;

    surface = IMG_Load(Path);
    if (surface == NULL)
    {
        printf("ERROR Unable to load texture: %s\n", Path);
        exit(1);
    }
    result = SDL_CreateTextureFromSurface(Display->Renderer, surface);
    SDL_FreeSurface(surface);

    return result;
}