#include "SlayEngineV1.h"

slayCamera* slayNewCamera(double* OriginX, double* OriginY, double RelativeX, double RelativeY)
{
    slayCamera* result;

    result = malloc(sizeof(slayCamera));
    result->OriginX = OriginX;
    result->OriginY = OriginY;
    result->RelativeX = RelativeX;
    result->RelativeY = RelativeY;
    result->AbsoluteX = *OriginX + RelativeX;
    result->AbsoluteY = *OriginY + RelativeY;

    return result;
}

uint16 slayUpdateCamera(slayCamera* Camera)
{
    Camera->AbsoluteX = *Camera->OriginX + Camera->RelativeX;
    Camera->AbsoluteY = *Camera->OriginY + Camera->RelativeY;

    return 0;
}

uint16 slayApplyCamera(SDL_Rect* Object, slayCamera* Camera, double X, double Y)
{
    Object->x = (sint32)round(X - Camera->AbsoluteX);
    Object->y = (sint32)round(Y - Camera->AbsoluteY);
    Object->w = Object->w;
    Object->h = Object->h;

    return 0;
}