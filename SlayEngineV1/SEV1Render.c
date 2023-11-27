#include "SlayEngineV1.h"

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