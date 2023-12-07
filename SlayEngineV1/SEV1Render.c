#include "SlayEngineV1.h"

slayTexture* slayLoadTexture(slayEngine* Engine, char* Path)
{
    SDL_Texture* result;

    SDL_Surface* surface;

    surface = IMG_Load(Path);
    if (surface == NULL)
    {
        printf("ERROR Unable to load texture: %s\n", Path);
        exit(1);
    }
    result = SDL_CreateTextureFromSurface(Engine->Display->Renderer, surface);
    
    SDL_FreeSurface(surface);

    return result;
}

slayFont* slayLoadFont(char* Path, uint8 Size)
{
    TTF_Font* result;

    result = TTF_OpenFont(Path, Size);
    if (result == NULL)
    {
        printf("ERROR Unable to load font: %s\n", Path);
        exit(1);
    }

    return result;
}

uint8 slayRenderStart(slayEngine* Engine)
{
    SDL_SetRenderDrawColor(Engine->Display->Renderer, 0, 0, 0, 255);
    SDL_RenderClear(Engine->Display->Renderer);

    return 0;
}

uint8 slayRenderEnd(slayEngine* Engine)
{
    SDL_RenderPresent(Engine->Display->Renderer);

    return 0;
}

uint8 slayRenderColor(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    SDL_Rect Object;

    Object.x = X;
    Object.y = Y;
    Object.w = Width;
    Object.h = Height;
    
    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        SDL_SetRenderDrawColor(Engine->Display->Renderer, ColorR, ColorG, ColorB, ColorA);
        SDL_RenderFillRect(Engine->Display->Renderer, &Object);
    }

    return 0;
}

uint8 slayRenderColorCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    SDL_Rect Object;

    slayApplyCamera(Engine, &Object, X, Y, Width, Height, Distance);

    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        SDL_SetRenderDrawColor(Engine->Display->Renderer, ColorR, ColorG, ColorB, ColorA);
        SDL_RenderFillRect(Engine->Display->Renderer, &Object);
    }

    return 0;
}

uint8 slayRender3DColorCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    for (double i = FirstLayer - Depth; i <= FirstLayer; i += Quality)
    {
        slayRenderColorCamera(Engine, X, Y, Width, Height, i, ColorR, ColorG, ColorB, ColorA);
    }

    return 0;
}

uint8 slayRenderTexture(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, slayTexture* Texture, uint8 Alpha)
{
    SDL_Rect Object;

    Object.x = X;
    Object.y = Y;
    Object.w = Width;
    Object.h = Height;
    
    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        SDL_SetTextureAlphaMod(Texture, Alpha);
        SDL_RenderCopyEx(Engine->Display->Renderer, Texture, NULL, &Object, Angle, NULL, Flip);
    }

    return 0;
}

uint8 slayRenderTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double Distance, slayTexture* Texture, uint8 Alpha)
{
    SDL_Rect Object;

    slayApplyCamera(Engine, &Object, X, Y, Width, Height, Distance);

    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        SDL_SetTextureAlphaMod(Texture, Alpha);
        SDL_RenderCopyEx(Engine->Display->Renderer, Texture, NULL, &Object, Angle, NULL, Flip);
    }

    return 0;
}

uint8 slayRender3DTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, slayTexture* Texture, uint8 Alpha)
{
    for (double i = FirstLayer - Depth; i <= FirstLayer; i += Quality)
    {
        slayRenderTextureCamera(Engine, X, Y, Width, Height, Angle, Flip, i, Texture, Alpha);
    }

    return 0;
}

uint8 slayRenderText(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, double Size, double Angle, uint8 Flip, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
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
    texture = SDL_CreateTextureFromSurface(Engine->Display->Renderer, surface);

    Object.x = X;
    Object.y = Y;
    Object.w = surface->w * Size;
    Object.h = surface->h * Size;
    
    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        SDL_RenderCopyEx(Engine->Display->Renderer, texture, NULL, &Object, Angle, NULL, Flip);
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    return 0;
}

uint8 slayRenderTextCamera(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, double Size, double Angle, uint8 Flip, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
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
    texture = SDL_CreateTextureFromSurface(Engine->Display->Renderer, surface);

    slayApplyCamera(Engine, &Object, X, Y, surface->w * Size, surface->h * Size, Distance);
    
    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        SDL_RenderCopyEx(Engine->Display->Renderer, texture, NULL, &Object, Angle, NULL, Flip);
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    return 0;
}

uint8 slayRender3DTextCamera(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, double Size, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    for (double i = FirstLayer - Depth; i <= FirstLayer; i += Quality)
    {
        slayRenderTextCamera(Engine, Font, Characters, X, Y, Size, Angle, Flip, i, ColorR, ColorG, ColorB, ColorA);
    }

    return 0;
}