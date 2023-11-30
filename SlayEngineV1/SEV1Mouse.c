#include "SlayEngineV1.h"

uint16 slayMouseMovement(slayEngine* Engine)
{
    SDL_GetRelativeMouseState(&Engine->Mouse->MovementX, &Engine->Mouse->MovementY);

    return 0;
}

uint16 slayMouseButtons(slayEngine* Engine)
{
    uint32 MouseState;

    MouseState = SDL_GetMouseState(NULL, NULL);
    if (MouseState & 1)
    {
        Engine->Mouse->LMB = true;
    }
    else
    {
        Engine->Mouse->LMB = false;
    }
    if (MouseState & 2)
    {
        Engine->Mouse->MMB = true;
    }
    else
    {
        Engine->Mouse->MMB = false;
    }
    if (MouseState & 4)
    {
        Engine->Mouse->RMB = true;
    }
    else
    {
        Engine->Mouse->RMB = false;
    }

    return 0;
}

logic slayCursorCollision(slayEngine* Engine, slayHitbox* Hitbox)
{
    sint32 x, y;
    uint16 width, height;

    x = (sint32)round(*Hitbox->ObjectX + Hitbox->UpperLeftX);
    y = (sint32)round(*Hitbox->ObjectY + Hitbox->UpperLeftY);
    width = (sint32)round(*Hitbox->ObjectX + Hitbox->LowerRightX) - x;
    height = (sint32)round(*Hitbox->ObjectY + Hitbox->LowerRightY) - y;

    if ((x <= Engine->Mouse->X && Engine->Mouse->X <= x + width) && (y <= Engine->Mouse->Y && Engine->Mouse->Y <= y + height))
    {
        return true;
    }

    return false;
}

logic slayCursorCollisionCamera(slayEngine* Engine, slayHitbox* Hitbox, double Distance)
{
    sint32 x, y;
    uint16 width, height;

    x = (sint32)round(*Hitbox->ObjectX + Hitbox->UpperLeftX);
    y = (sint32)round(*Hitbox->ObjectY + Hitbox->UpperLeftY);
    width = (sint32)round(*Hitbox->ObjectX + Hitbox->LowerRightX) - x;
    height = (sint32)round(*Hitbox->ObjectY + Hitbox->LowerRightY) - y;

    x = (sint32)round((x - (*Engine->Camera->OriginX + Engine->Camera->CenterX + (Engine->Camera->RelativeX / (Engine->Camera->Zoom * Distance)))) * (Engine->Camera->Zoom * Distance));
    y = (sint32)round((y - (*Engine->Camera->OriginY + Engine->Camera->CenterY + (Engine->Camera->RelativeY / (Engine->Camera->Zoom * Distance)))) * (Engine->Camera->Zoom * Distance));
    width = width * (Engine->Camera->Zoom * Distance);
    height = height * (Engine->Camera->Zoom * Distance);

    if ((x <= Engine->Mouse->X && Engine->Mouse->X <= x + width) && (y <= Engine->Mouse->Y && Engine->Mouse->Y <= y + height))
    {
        return true;
    }

    return false;
}