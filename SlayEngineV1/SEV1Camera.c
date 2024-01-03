#include "SlayEngineV1.h"

uint8 slaySetCamera(slayEngine* Engine, double* OriginX, double* OriginY, double CenterX, double CenterY, double RelativeX, double RelativeY, double Zoom)
{
    if (Engine == NULL)
    {
        printf("slaySetCamera(): Engine must not be NULL\nParams: Engine: %p, OriginX: %p, OriginY: %p, CenterX: %lf, CenterY: %lf, RelativeX: %lf, RelativeY: %lf, Zoom: %lf\n", Engine, OriginX, OriginY, CenterX, CenterY, RelativeX, RelativeY, Zoom);
        return 1;
    }
    if (OriginX == NULL)
    {
        printf("slaySetCamera(): OriginX must not be NULL\nParams: Engine: %p, OriginX: %p, OriginY: %p, CenterX: %lf, CenterY: %lf, RelativeX: %lf, RelativeY: %lf, Zoom: %lf\n", Engine, OriginX, OriginY, CenterX, CenterY, RelativeX, RelativeY, Zoom);
        return 1;
    }
    if (OriginY == NULL)
    {
        printf("slaySetCamera(): OriginY must not be NULL\nParams: Engine: %p, OriginX: %lf, OriginY: %p, CenterX: %lf, CenterY: %lf, RelativeX: %lf, RelativeY: %lf, Zoom: %lf\n", Engine, *OriginX, OriginY, CenterX, CenterY, RelativeX, RelativeY, Zoom);
        return 1;
    }
    if (Zoom <= 0)
    {
        printf("slaySetCamera(): Zoom must not be less than or equal to 0\nParams: Engine: %p, OriginX: %lf, OriginY: %lf, CenterX: %lf, CenterY: %lf, RelativeX: %lf, RelativeY: %lf, Zoom: %lf\n", Engine, *OriginX, *OriginY, CenterX, CenterY, RelativeX, RelativeY, Zoom);
        return 1;
    }

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

    if (Engine == NULL)
    {
        printf("slayApplyCamera(): Engine must not be NULL\nParams: Engine: %p, Object: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Distance: %lf\n", Engine, Object, X, Y, Width, Height, Distance);
        return 1;
    }
    if (Engine->Camera->OriginX == NULL)
    {
        printf("slayApplyCamera(): Engine->Camera->OriginX must not be NULL\nParams: Engine: %p, Object: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Distance: %lf\n", Engine, Object, X, Y, Width, Height, Distance);
        return 1;
    }
    if (Engine->Camera->OriginY == NULL)
    {
        printf("slayApplyCamera(): Engine->Camera->OriginY must not be NULL\nParams: Engine: %p, Object: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Distance: %lf\n", Engine, Object, X, Y, Width, Height, Distance);
        return 1;
    }
    if (Object == NULL)
    {
        printf("slayApplyCamera(): Object must not be NULL\nParams: Engine: %p, Object: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Distance: %lf\n", Engine, Object, X, Y, Width, Height, Distance);
        return 1;
    }
    if (Distance <= 0)
    {
        printf("slayApplyCamera(): Distance must not be less than or equal to 0\nParams: Engine: %p, Object: %p, X: %lf, Y: %lf, Width: %d, Height: %d, Distance: %lf\n", Engine, Object, X, Y, Width, Height, Distance);
        return 1;
    }

    cache = Engine->Camera->Zoom * Distance;
    Object->x = (sint32)round((X - (*Engine->Camera->OriginX + Engine->Camera->CenterX + (Engine->Camera->RelativeX / cache))) * cache);
    Object->y = (sint32)round((Y - (*Engine->Camera->OriginY + Engine->Camera->CenterY + (Engine->Camera->RelativeY / cache))) * cache);
    Object->w = Width * cache;
    Object->h = Height * cache;

    return 0;
}