#include "SlayEngineV1.h"

slayCamera* slayNewCamera(double* OriginX, double* OriginY, double RelativeX, double RelativeY, double Zoom)
{
    slayCamera* result;

    result = malloc(sizeof(slayCamera));

    result->OriginX = OriginX;
    result->OriginY = OriginY;
    result->RelativeX = RelativeX;
    result->RelativeY = RelativeY;
    result->AbsoluteX = *OriginX + RelativeX;
    result->AbsoluteY = *OriginY + RelativeY;

    result->Zoom = Zoom;

    return result;
}

uint16 slayUpdateCamera(slayCamera* Camera)
{
    Camera->AbsoluteX = *Camera->OriginX + Camera->RelativeX / Camera->Zoom;
    Camera->AbsoluteY = *Camera->OriginY + Camera->RelativeY / Camera->Zoom;

    return 0;
}

uint16 slayApplyCamera(SDL_Rect* Object, slayCamera* Camera, double X, double Y, uint16 Width, uint16 Height)
{
    Object->x = (sint32)round((X - Camera->AbsoluteX) * Camera->Zoom);
    Object->y = (sint32)round((Y - Camera->AbsoluteY) * Camera->Zoom);
    Object->w = Width * Camera->Zoom;
    Object->h = Height * Camera->Zoom;

    return 0;
}