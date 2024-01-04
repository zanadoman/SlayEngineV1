#include "SlayEngineV1.h"

slayTexture* slayLoadTexture(slayEngine* Engine, char* Path)
{
    SDL_Texture* result;

    SDL_Surface* surface;

    if (Engine == NULL)
    {
        printf("slayLoadTexture(): Engine must not be NULL\nParams: Engine: %p, Path: %p\n", Engine, Path);
        exit(1);
    }
    if (Path == NULL)
    {
        printf("slayLoadTexture(): Path must not be NULL\nParams: Engine: %p, Path: %p\n", Engine, Path);
        exit(1);
    }

    surface = IMG_Load(Path);
    if (surface == NULL)
    {
        printf("slayLoadTexture(): IMG_Load failed\nParams: Engine: %p, Path: %s\n", Engine, Path);
        exit(1);
    }
    result = SDL_CreateTextureFromSurface(Engine->Display->Renderer, surface);
    if (result == NULL)
    {
        printf("slayLoadTexture(): SDL_CreateTextureFromSurface failed\nParams: Engine: %p, Path: %s\n", Engine, Path);
        exit(1);
    }
    
    SDL_FreeSurface(surface);

    return result;
}

slayFont* slayLoadFont(char* Path, uint8 Size)
{
    TTF_Font* result;

    if (Path == NULL)
    {
        printf("slayLoadFont(): Path must not be NULL\nParams: Path: %p, Size: %d\n", Path, Size);
        exit(1);
    }

    result = TTF_OpenFont(Path, Size);
    if (result == NULL)
    {
        printf("slayLoadFont(): TTF_OpenFont failed\nParams: Path: %s, Size: %d\n", Path, Size);
        exit(1);
    }

    return result;
}

uint8 slayRenderStart(slayEngine* Engine)
{
    if (Engine == NULL)
    {
        printf("slayRenderStart(): Engine must not be NULL\nParams: Engine: %p\n", Engine);
        exit(1);
    }

    if (SDL_SetRenderDrawColor(Engine->Display->Renderer, 0, 0, 0, 255) != 0)
    {
        printf("slayRenderStart(): SDL_SetRenderDrawColor failed\nParams: Engine: %p\n", Engine);
        exit(1);
    }
    if (SDL_RenderClear(Engine->Display->Renderer) != 0)
    {
        printf("slayRenderStart(): SDL_RenderClear failed\nParams: Engine: %p\n", Engine);
        exit(1);
    }

    return 0;
}

uint8 slayRenderEnd(slayEngine* Engine)
{
    if (Engine == NULL)
    {
        printf("slayRenderEnd(): Engine must not be NULL\nParams: Engine: %p\n", Engine);
        exit(1);
    }

    SDL_RenderPresent(Engine->Display->Renderer);

    return 0;
}

uint8 slayRenderColor(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    SDL_Rect Object;

    if (Engine == NULL)
    {
        printf("slayRenderColor(): Engine must not be NULL\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, ColorR: %d, ColorG: %d, ColorB: %d, ColorA: %d\n", Engine, X, Y, Width, Height, ColorR, ColorG, ColorB, ColorA);
        exit(1);
    }

    Object.x = X;
    Object.y = Y;
    Object.w = Width;
    Object.h = Height;
    
    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        if (SDL_SetRenderDrawColor(Engine->Display->Renderer, ColorR, ColorG, ColorB, ColorA) != 0)
        {
            printf("slayRenderColor(): SDL_SetRenderDrawColor failed\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, ColorR: %d, ColorG: %d, ColorB: %d, ColorA: %d\n", Engine, X, Y, Width, Height, ColorR, ColorG, ColorB, ColorA);
            exit(1);
        }
        if (SDL_RenderFillRect(Engine->Display->Renderer, &Object) != 0)
        {
            printf("slayRenderColor(): SDL_RenderFillRect failed\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, ColorR: %d, ColorG: %d, ColorB: %d, ColorA: %d\n", Engine, X, Y, Width, Height, ColorR, ColorG, ColorB, ColorA);
            exit(1);
        }
    }

    return 0;
}

uint8 slayRenderColorCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    SDL_Rect Object;

    if (Engine == NULL)
    {
        printf("slayRenderColorCamera(): Engine must not be NULL\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Distance: %lf, ColorR: %d, ColorG: %d, ColorB: %d, ColorA: %d\n", Engine, X, Y, Width, Height, Distance, ColorR, ColorG, ColorB, ColorA);
        exit(1);
    }
    if (Distance <= 0)
    {
        printf("slayRenderColorCamera(): Distance must not be less than or equal to 0\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Distance: %lf, ColorR: %d, ColorG: %d, ColorB: %d, ColorA: %d\n", Engine, X, Y, Width, Height, Distance, ColorR, ColorG, ColorB, ColorA);
        exit(1);
    }

    slayApplyCamera(Engine, &Object, X, Y, Width, Height, Distance);

    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        if (SDL_SetRenderDrawColor(Engine->Display->Renderer, ColorR, ColorG, ColorB, ColorA) != 0)
        {
            printf("slayRenderColorCamera(): SDL_SetRenderDrawColor failed\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Distance: %lf, ColorR: %d, ColorG: %d, ColorB: %d, ColorA: %d\n", Engine, X, Y, Width, Height, Distance, ColorR, ColorG, ColorB, ColorA);
            exit(1);
        }
        if (SDL_RenderFillRect(Engine->Display->Renderer, &Object) != 0)
        {
            printf("slayRenderColorCamera(): SDL_RenderFillRect failed\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Distance: %lf, ColorR: %d, ColorG: %d, ColorB: %d, ColorA: %d\n", Engine, X, Y, Width, Height, Distance, ColorR, ColorG, ColorB, ColorA);
            exit(1);
        }
    }

    return 0;
}

uint8 slayRender3DColorCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    if (Engine == NULL)
    {
        printf("slayRender3DColorCamera(): Engine must not be NULL\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, FirstLayer: %lf, Depth: %lf, Quality: %lf, ColorR: %d, ColorG: %d, ColorB: %d, ColorA: %d\n", Engine, X, Y, Width, Height, FirstLayer, Depth, Quality, ColorR, ColorG, ColorB, ColorA);
        exit(1);
    }
    if (FirstLayer <= 0)
    {
        printf("slayRender3DColorCamera(): FirstLayer must not be less than or equal to 0\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, FirstLayer: %lf, Depth: %lf, Quality: %lf, ColorR: %d, ColorG: %d, ColorB: %d, ColorA: %d\n", Engine, X, Y, Width, Height, FirstLayer, Depth, Quality, ColorR, ColorG, ColorB, ColorA);
        exit(1);
    }
    if (FirstLayer <= Depth)
    {
        printf("slayRender3DColorCamera(): Depth must not be more than or equal to FirstLayer\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, FirstLayer: %lf, Depth: %lf, Quality: %lf, ColorR: %d, ColorG: %d, ColorB: %d, ColorA: %d\n", Engine, X, Y, Width, Height, FirstLayer, Depth, Quality, ColorR, ColorG, ColorB, ColorA);
    }
    if (Quality <= 0)
    {
        printf("slayRender3DColorCamera(): Quality must not be less than or equal to 0\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, FirstLayer: %lf, Depth: %lf, Quality: %lf, ColorR: %d, ColorG: %d, ColorB: %d, ColorA: %d\n", Engine, X, Y, Width, Height, FirstLayer, Depth, Quality, ColorR, ColorG, ColorB, ColorA);
        exit(1);
    }

    for (double i = FirstLayer - Depth; i <= FirstLayer; i += Quality)
    {
        slayRenderColorCamera(Engine, X, Y, Width, Height, i, ColorR, ColorG, ColorB, ColorA);
    }

    return 0;
}

uint8 slayRenderTexture(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, slayTexture* Texture, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 Alpha)
{
    SDL_Rect Object;

    if (Engine == NULL)
    {
        printf("slayRenderTexture(): Engine must not be NULL\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, Texture: %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, Texture, ColorR, ColorG, ColorB, Alpha);
        exit(1);
    }

    if (Texture == NULL)
    {
        return 0;
    }

    Object.x = X;
    Object.y = Y;
    Object.w = Width;
    Object.h = Height;
    
    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        if (SDL_SetTextureColorMod(Texture, ColorR, ColorG, ColorB) != 0)
        {
            printf("slayRenderTexture(): SDL_SetTextureColorMod failed\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, Texture: %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, Texture, ColorR, ColorG, ColorB, Alpha);
            exit(1);
        }
        if (SDL_SetTextureAlphaMod(Texture, Alpha) != 0)
        {
            printf("slayRenderTexture(): SDL_SetTextureAlphaMod failed\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, Texture: %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, Texture, ColorR, ColorG, ColorB, Alpha);
            exit(1);
        }
        if (SDL_RenderCopyEx(Engine->Display->Renderer, Texture, NULL, &Object, Angle, NULL, Flip) != 0)
        {
            printf("slayRenderTexture(): SDL_RenderCopyEx failed\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, Texture: %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, Texture, ColorR, ColorG, ColorB, Alpha);
            exit(1);
        }
    }

    return 0;
}

uint8 slayRenderTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double Distance, slayTexture* Texture, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 Alpha)
{
    SDL_Rect Object;

    if (Engine == NULL)
    {
        printf("slayRenderTextureCamera(): Engine must not be NULL\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, Distance: %lf, Texture: %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, Distance, Texture, ColorR, ColorG, ColorB, Alpha);
        exit(1);
    }
    if (Distance <= 0)
    {
        printf("slayRenderTextureCamera(): Distance must not be less than or equal to 0\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, Distance: %lf, Texture: %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, Distance, Texture, ColorR, ColorG, ColorB, Alpha);
        exit(1);
    }

    if (Texture == NULL)
    {
        return 0;
    }

    slayApplyCamera(Engine, &Object, X, Y, Width, Height, Distance);

    if ((-Object.w <= Object.x && Object.x <= Engine->Display->Width) && (-Object.h <= Object.y && Object.y <= Engine->Display->Height))
    {
        if (SDL_SetTextureColorMod(Texture, ColorR, ColorG, ColorB) != 0)
        {
            printf("slayRenderTextureCamera(): SDL_SetTextureColorMod failed\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, Distance: %lf, Texture: %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, Distance, Texture, ColorR, ColorG, ColorB, Alpha);
            exit(1);
        }
        if (SDL_SetTextureAlphaMod(Texture, Alpha) != 0)
        {
            printf("slayRenderTextureCamera(): SDL_SetTextureAlphaMod failed\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, Distance: %lf, Texture: %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, Distance, Texture, ColorR, ColorG, ColorB, Alpha);
            exit(1);
        }
        if (SDL_RenderCopyEx(Engine->Display->Renderer, Texture, NULL, &Object, Angle, NULL, Flip) != 0)
        {
            printf("slayRenderTextureCamera(): SDL_RenderCopyEx failed\nParams: Engine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, Distance: %lf, Texture: %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, Distance, Texture, ColorR, ColorG, ColorB, Alpha);
            exit(1);
        }
    }

    return 0;
}

uint8 slayRender3DTextureCamera(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, slayTexture* Texture, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 Alpha)
{
    if (Engine == NULL)
    {
        printf("slayRender3DTextureCamera(): Engine must not be NULL\nEngine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, FirstLayer: %lf, Depth: %lf, Quality: %lf, Texture %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, FirstLayer, Depth, Quality, Texture, ColorR, ColorG, ColorB, Alpha);
        exit(1);
    }
    if (FirstLayer <= 0)
    {
        printf("slayRender3DTextureCamera(): FirstLayer must not be less than or equal to 0\nEngine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, FirstLayer: %lf, Depth: %lf, Quality: %lf, Texture %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, FirstLayer, Depth, Quality, Texture, ColorR, ColorG, ColorB, Alpha);
        exit(1);
    }
    if (FirstLayer <= Depth)
    {
        printf("slayRender3DTextureCamera(): Depth must not be more than or equal to FirstLayer\nEngine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, FirstLayer: %lf, Depth: %lf, Quality: %lf, Texture %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, FirstLayer, Depth, Quality, Texture, ColorR, ColorG, ColorB, Alpha);
        exit(1);
    }
    if (Quality <= 0)
    {
        printf("slayRender3DTextureCamera(): Quality must not be less than or equal to 0\nEngine: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Angle: %lf, Flip: %d, FirstLayer: %lf, Depth: %lf, Quality: %lf, Texture %p, ColorR: %d, ColorG: %d, ColorB: %d, Alpha: %d\n", Engine, X, Y, Width, Height, Angle, Flip, FirstLayer, Depth, Quality, Texture, ColorR, ColorG, ColorB, Alpha);
        exit(1);
    }

    if (Texture == NULL)
    {
        return 0;
    }

    for (double i = FirstLayer - Depth; i <= FirstLayer; i += Quality)
    {
        slayRenderTextureCamera(Engine, X, Y, Width, Height, Angle, Flip, i, Texture, ColorR, ColorG, ColorB, Alpha);
    }

    return 0;
}

uint8 slayRenderText(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, uint16 Size, double Angle, uint8 Flip, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    SDL_Rect Object;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Color color;
    double cache;

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

    cache = (double)Size / (double)surface->h;
    Object.x = X;
    Object.y = Y;
    Object.w = surface->w * cache;
    Object.h = surface->h * cache;
    
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

uint8 slayRenderTextCamera(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, uint16 Size, double Angle, uint8 Flip, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    SDL_Rect Object;
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Color color;
    double cache;

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

    cache = (double)Size / (double)surface->h;
    slayApplyCamera(Engine, &Object, X, Y, surface->w * cache, surface->h * cache, Distance);
    
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

uint8 slayRender3DTextCamera(slayEngine* Engine, slayFont* Font, char* Characters, double X, double Y, uint16 Size, double Angle, uint8 Flip, double FirstLayer, double Depth, double Quality, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
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