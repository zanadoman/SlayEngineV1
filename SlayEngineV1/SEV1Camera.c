#include "SlayEngineV1.h"

//Creates a new camera
slayCamera* slayNewCamera(double* OriginX, double* OriginY, double RelativeX, double RelativeY)
{
    slayCamera* result;

    result = malloc(sizeof(slayCamera));
    result->OriginX = OriginX;
    result->OriginY = OriginY;
    result->RelativeX = RelativeX;
    result->RelativeY = RelativeY;
    result->CurrentX = *OriginX + RelativeX;
    result->CurrentY = *OriginY + RelativeY;

    return result;
}
//Updates the camera position
uint16 slayUpdateCamera(slayCamera* Camera)
{
    Camera->CurrentX = *Camera->OriginX + Camera->RelativeX;
    Camera->CurrentY = *Camera->OriginY + Camera->RelativeY;

    return 0;
}
//Calculates the position of the elements for the renderer relative to the camera
uint16 slayApplyCamera(SDL_Rect* Object, slayCamera* Camera, double X, double Y)
{
    Object->x = (sint32)round(X - Camera->CurrentX);
    Object->y = (sint32)round(Y - Camera->CurrentY);
    Object->w = Object->w;
    Object->h = Object->h;

    return 0;
}