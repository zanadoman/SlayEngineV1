#include "SlayEngineV1.h"

slayTexture* slayLoadTexture(slayEngine* Engine, char* Path)
{
    SDL_Texture* result;

    SDL_Surface* surface;

    surface = IMG_Load(Path);
    if (surface == NULL)
    {
        printf("ERROR Unable to load TEXTURE: %s\n", Path);
        exit(1);
    }
    result = SDL_CreateTextureFromSurface(Engine->Display->Renderer, surface);
    if (result == NULL)
    {
        printf("ERROR Unable to process TEXTURE (%s)\n", Path);
        exit(1);
    }
    
    SDL_FreeSurface(surface);

    return result;
}

slayFont* slayLoadFont(char* Path, uint8 Size)
{
    TTF_Font* result;

    result = TTF_OpenFont(Path, Size);
    if (result == NULL)
    {
        printf("ERROR Unable to load FONT: %s\n", Path);
        exit(1);
    }

    return result;
}

uint8 slayRenderStart(slayEngine* Engine)
{
    if (SDL_SetRenderDrawColor(Engine->Display->Renderer, 0, 0, 0, 255) != 0)
    {
        printf("ERROR Unable to set RENDERER_COLOR\n");
        exit(1);
    }
    if (SDL_RenderClear(Engine->Display->Renderer) != 0)
    {
        printf("ERROR Unable to clear RENDERER\n");
        exit(1);
    }

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
        if (SDL_SetRenderDrawColor(Engine->Display->Renderer, ColorR, ColorG, ColorB, ColorA) != 0)
        {
            printf("ERROR Unable to set RENDERER_COLOR (%d, %d, %d, %d)\n", ColorR, ColorG, ColorB, ColorA);
            exit(1);
        }
        if (SDL_RenderFillRect(Engine->Display->Renderer, &Object) != 0)
        {
            printf("ERROR Unable to draw RECTANGLE (%d, %d, %d, %d)\n", ColorR, ColorG, ColorB, ColorA);
            exit(1);
        }
    }

    return 0;
}

uint8 slayRenderColorCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    SDL_Rect Object;

    slayApplyCamera(Engine, &Object, X, Y, Width, Height, Distance);

    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        if (SDL_SetRenderDrawColor(Engine->Display->Renderer, ColorR, ColorG, ColorB, ColorA) != 0)
        {
            printf("ERROR Unable to set RENDERER_COLOR (%d, %d, %d, %d)\n", ColorR, ColorG, ColorB, ColorA);
            exit(1);
        }
        if (SDL_RenderFillRect(Engine->Display->Renderer, &Object) != 0)
        {
            printf("ERROR Unable to draw RECTANGLE (%d, %d, %d, %d)\n", ColorR, ColorG, ColorB, ColorA);
            exit(1);
        }
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

    if (Texture == NULL)
    {
        return 1;
    }

    Object.x = X;
    Object.y = Y;
    Object.w = Width;
    Object.h = Height;
    
    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        if (SDL_SetTextureAlphaMod(Texture, Alpha) != 0)
        {
            printf("ERROR Unable to set TEXTURE_ALPHA_MOD\n");
            exit(1);
        }
        if (SDL_RenderCopyEx(Engine->Display->Renderer, Texture, NULL, &Object, Angle, NULL, Flip) != 0)
        {
            printf("ERROR Unable to draw TEXTURE\n");
            exit(1);
        }
    }

    return 0;
}

uint8 slayRenderTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double Distance, slayTexture* Texture, uint8 Alpha)
{
    SDL_Rect Object;

    if (Texture == NULL)
    {
        return 1;
    }

    slayApplyCamera(Engine, &Object, X, Y, Width, Height, Distance);

    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        if (SDL_SetTextureAlphaMod(Texture, Alpha) != 0)
        {
            printf("ERROR Unable to set TEXTURE_ALPHA_MOD\n");
            exit(1);
        }
        if (SDL_RenderCopyEx(Engine->Display->Renderer, Texture, NULL, &Object, Angle, NULL, Flip) != 0)
        {
            printf("ERROR Unable to draw TEXTURE\n");
            exit(1);
        }
    }

    return 0;
}

uint8 slayRender3DTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, slayTexture* Texture, uint8 Alpha)
{
    if (Texture == NULL)
    {
        return 1;
    }

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

    if (Characters[0] == '\0')
    {
        return 1;
    }

    color.r = ColorR;
    color.g = ColorG;
    color.b = ColorB;
    color.a = ColorA;

    surface = TTF_RenderText_Blended(Font, Characters, color);
    if (surface == NULL)
    {
        printf("ERROR Unable to process TEXT_SURFACE (%s)\n", Characters);
        exit(1);
    }
    texture = SDL_CreateTextureFromSurface(Engine->Display->Renderer, surface);
    if (texture == NULL)
    {
        printf("ERROR Unable to process TEXT_TEXTURE (%s)\n", Characters);
        exit(1);
    }

    Object.x = X;
    Object.y = Y;
    Object.w = surface->w * Size;
    Object.h = surface->h * Size;
    
    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        if (SDL_RenderCopyEx(Engine->Display->Renderer, texture, NULL, &Object, Angle, NULL, Flip) != 0)
        {
            printf("ERROR Unable to draw TEXT (%s)\n", Characters);
            exit(1);
        }
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

    if (Characters[0] == '\0')
    {
        return 1;
    }

    color.r = ColorR;
    color.g = ColorG;
    color.b = ColorB;
    color.a = ColorA;

    surface = TTF_RenderText_Blended(Font, Characters, color);
    if (surface == NULL)
    {
        printf("ERROR Unable to process TEXT_SURFACE (%s)\n", Characters);
        exit(1);
    }
    texture = SDL_CreateTextureFromSurface(Engine->Display->Renderer, surface);
    if (texture == NULL)
    {
        printf("ERROR Unable to process TEXT_TEXTURE (%s)\n", Characters);
        exit(1);
    }

    slayApplyCamera(Engine, &Object, X, Y, surface->w * Size, surface->h * Size, Distance);
    
    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        if (SDL_RenderCopyEx(Engine->Display->Renderer, texture, NULL, &Object, Angle, NULL, Flip) != 0)
        {
            printf("ERROR Unable to draw TEXT (%s)\n", Characters);
            exit(1);
        }
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    return 0;
}

uint8 slayRender3DTextCamera(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, double Size, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    if (Characters[0] == '\0')
    {
        return 1;
    }

    for (double i = FirstLayer - Depth; i <= FirstLayer; i += Quality)
    {
        slayRenderTextCamera(Engine, Font, Characters, X, Y, Size, Angle, Flip, i, ColorR, ColorG, ColorB, ColorA);
    }

    return 0;
}