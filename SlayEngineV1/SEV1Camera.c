#include "SlayEngineV1.h"

uint8 slaySetCamera(slayEngine* Engine, double* OriginX, double* OriginY, double CenterX, double CenterY, double RelativeX, double RelativeY, double Zoom)
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

uint8 slayApplyCamera(slayEngine* Engine, slayObject* Object, double X, double Y, uint16 Width, uint16 Height, double Distance)
{
    double cache;

    cache = Engine->Camera->Zoom * Distance;
    Object->x = (sint32)round((X - (*Engine->Camera->OriginX + Engine->Camera->CenterX + (Engine->Camera->RelativeX / cache))) * cache);
    Object->y = (sint32)round((Y - (*Engine->Camera->OriginY + Engine->Camera->CenterY + (Engine->Camera->RelativeY / cache))) * cache);
    Object->w = Width * cache;
    Object->h = Height * cache;

    return 0;
}