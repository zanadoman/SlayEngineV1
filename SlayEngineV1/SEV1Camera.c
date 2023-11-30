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

uint16 slayApplyCamera(slayEngine* Engine, SDL_Rect* Object, double X, double Y, uint16 Width, uint16 Height, double Distance)
{
    Object->x = (sint32)round((X - (*Engine->Camera->OriginX + Engine->Camera->CenterX + (Engine->Camera->RelativeX / (Engine->Camera->Zoom * Distance)))) * (Engine->Camera->Zoom * Distance));
    Object->y = (sint32)round((Y - (*Engine->Camera->OriginY + Engine->Camera->CenterY + (Engine->Camera->RelativeY / (Engine->Camera->Zoom * Distance)))) * (Engine->Camera->Zoom * Distance));
    Object->w = Width * (Engine->Camera->Zoom * Distance);
    Object->h = Height * (Engine->Camera->Zoom * Distance);

    return 0;
}