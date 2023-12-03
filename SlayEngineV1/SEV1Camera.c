#include "SlayEngineV1.h"

uint16 slaySetCamera(slayEngine* Engine, double* OriginX, double* OriginY, double CenterX, double CenterY, double RelativeX, double RelativeY, double Zoom)
{
    Engine->Camera->OriginX = OriginX;
    Engine->Camera->OriginY = OriginY;
    Engine->Camera->CenterX = CenterX;
    Engine->Camera->CenterY = CenterY;
    Engine->Camera->RelativeX = RelativeX;
    Engine->Camera->RelativeY = RelativeY;
    Engine->Camera->AbsoluteX = *OriginX + RelativeX;
    Engine->Camera->AbsoluteY = *OriginY + RelativeY;
    Engine->Camera->Zoom = Zoom;

    return 0;
}

uint16 slayApplyCamera(slayEngine* Engine, SDL_Rect* Object, double X, double Y, uint16 Width, uint16 Height, double Distance)
{
    Object->x = (sint32)round((X - (*Engine->Camera->OriginX + Engine->Camera->CenterX + (Engine->Camera->RelativeX / (Engine->Camera->Zoom * Distance)))) * (Engine->Camera->Zoom * Distance));
    Object->y = (sint32)round((Y - (*Engine->Camera->OriginY + Engine->Camera->CenterY + (Engine->Camera->RelativeY / (Engine->Camera->Zoom * Distance)))) * (Engine->Camera->Zoom * Distance));
    Object->w = Width * (Engine->Camera->Zoom * Distance);
    Object->h = Height * (Engine->Camera->Zoom * Distance);

    return 0;
}