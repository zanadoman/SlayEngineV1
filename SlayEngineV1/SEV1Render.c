#include "SlayEngineV1.h"

SDL_Texture* slayLoadTexture(slayDisplay* Display, char* Path)
{
    SDL_Texture* result;

    SDL_Surface* surface;

    surface = IMG_Load(Path);
    if (surface == NULL)
    {
        printf("ERROR Unable to load texture: %s\n", Path);
        SDL_Quit();
        TTF_Quit();
        exit(1);
    }
    result = SDL_CreateTextureFromSurface(Display->Renderer, surface);
    SDL_FreeSurface(surface);

    return result;
}

TTF_Font* slayLoadFont(char* Path, int Size)
{
    TTF_Font* result;

    result = TTF_OpenFont(Path, Size);
    if (result == NULL)
    {
        printf("ERROR Unable to load font: %s\n", Path);
        SDL_Quit();
        TTF_Quit();
        exit(1);
    }

    return result;
}

uint16 slayRenderStart(slayDisplay* Display, uint8 ColorR, uint8 ColorG, uint8 ColorB)
{
    SDL_SetRenderDrawColor(Display->Renderer, ColorR, ColorG, ColorB, 255);
    SDL_RenderClear(Display->Renderer);

    return 0;
}

uint16 slayRenderEnd(slayDisplay* Display)
{
    SDL_RenderPresent(Display->Renderer);

    return 0;
}

uint16 slayRenderColor(slayDisplay* Display, double X, double Y, uint16 Width, uint16 Height, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    SDL_Rect Object;

    Object.x = X;
    Object.y = Y;
    Object.w = Width;
    Object.h = Height;
    SDL_SetRenderDrawColor(Display->Renderer, ColorR, ColorG, ColorB, ColorA);
    SDL_RenderFillRect(Display->Renderer, &Object);

    return 0;
}

uint16 slayRenderColorCamera(slayDisplay* Display, double X, double Y, uint16 Width, uint16 Height, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA, slayCamera* Camera)
{
    SDL_Rect Object;

    slayApplyCamera(&Object, Camera, X, Y);
    Object.w = Width;
    Object.h = Height;
    SDL_SetRenderDrawColor(Display->Renderer, ColorR, ColorG, ColorB, ColorA);
    SDL_RenderFillRect(Display->Renderer, &Object);

    return 0;
}

uint16 slayRenderTexture(slayDisplay* Display, double X, double Y, uint16 Width, uint16 Height, SDL_Texture* Texture)
{
    SDL_Rect Object;

    Object.x = X;
    Object.y = Y;
    Object.w = Width;
    Object.h = Height;
    SDL_RenderCopy(Display->Renderer, Texture, NULL, &Object);

    return 0;
}

uint16 slayRenderTextureCamera(slayDisplay* Display, double X, double Y, uint16 Width, uint16 Height, SDL_Texture* Texture, slayCamera* Camera)
{
    SDL_Rect Object;

    slayApplyCamera(&Object, Camera, X, Y);
    Object.w = Width;
    Object.h = Height;
    SDL_RenderCopy(Display->Renderer, Texture, NULL, &Object);

    return 0;
}

uint16 slayRenderText(slayDisplay* Display, TTF_Font* Font, char* Characters, double X, double Y,double Size, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    SDL_Rect Object;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Color color;

    color.r = ColorR;
    color.g = ColorG;
    color.b = ColorB;
    color.a = ColorA;

    surface = TTF_RenderText_Blended(Font, Characters, color);
    texture = SDL_CreateTextureFromSurface(Display->Renderer, surface);

    Object.x = X;
    Object.y = Y;
    Object.w = surface->w * Size;
    Object.h = surface->h * Size;
    SDL_RenderCopy(Display->Renderer, texture, NULL, &Object);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    return 0;
}

uint16 slayRenderTextCamera(slayDisplay* Display, TTF_Font* Font, char* Characters, double X, double Y,double Size, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA, slayCamera* Camera)
{
    SDL_Rect Object;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Color color;

    color.r = ColorR;
    color.g = ColorG;
    color.b = ColorB;
    color.a = ColorA;

    surface = TTF_RenderText_Blended(Font, Characters, color);
    texture = SDL_CreateTextureFromSurface(Display->Renderer, surface);

    slayApplyCamera(&Object, Camera, X, Y);
    Object.w = surface->w * Size;
    Object.h = surface->h * Size;
    SDL_RenderCopy(Display->Renderer, texture, NULL, &Object);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    return 0;
}