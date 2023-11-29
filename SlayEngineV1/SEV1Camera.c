#include "SlayEngineV1.h"

slayCamera* slayNewCamera(double* OriginX, double* OriginY, double CenterX, double CenterY, double RelativeX, double RelativeY, double Zoom)
{
    slayCamera* result;

    result = malloc(sizeof(slayCamera));

    result->OriginX = OriginX;
    result->OriginY = OriginY;
    result->CenterX = CenterX;
    result->CenterY = CenterY;
    result->RelativeX = RelativeX;
    result->RelativeY = RelativeY;
    result->AbsoluteX = *OriginX + RelativeX;
    result->AbsoluteY = *OriginY + RelativeY;

    result->Zoom = Zoom;

    return result;
}

uint16 slayUpdateCamera(slayCamera* Camera)
{
    Camera->AbsoluteX = *Camera->OriginX + Camera->CenterX + (Camera->RelativeX / Camera->Zoom);
    Camera->AbsoluteY = *Camera->OriginY + Camera->CenterY + (Camera->RelativeY / Camera->Zoom);

    return 0;
}

uint16 slayApplyCamera(SDL_Rect* Object, slayCamera* Camera, double X, double Y, uint16 Width, uint16 Height, double Distance)
{
    Object->x = (sint32)round((X - (*Camera->OriginX + Camera->CenterX + (Camera->RelativeX / (Camera->Zoom * Distance)))) * (Camera->Zoom * Distance));
    Object->y = (sint32)round((Y - (*Camera->OriginY + Camera->CenterY + (Camera->RelativeY / (Camera->Zoom * Distance)))) * (Camera->Zoom * Distance));
    Object->w = Width * (Camera->Zoom * Distance);
    Object->h = Height * (Camera->Zoom * Distance);

    return 0;
}