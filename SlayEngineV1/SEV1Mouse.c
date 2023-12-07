#include "SlayEngineV1.h"

uint8 slayMouseMovement(slayEngine* Engine)
{
    SDL_GetRelativeMouseState(&Engine->Mouse->MovementX, &Engine->Mouse->MovementY);

    return 0;
}

uint8 slayMouseButtons(slayEngine* Engine)
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
    SDL_Rect object;

    object.x = (sint32)round(*Hitbox->ObjectX + Hitbox->UpperLeftX);
    object.y = (sint32)round(*Hitbox->ObjectY + Hitbox->UpperLeftY);
    object.w = (sint32)round(*Hitbox->ObjectX + Hitbox->LowerRightX) - object.x;
    object.h = (sint32)round(*Hitbox->ObjectY + Hitbox->LowerRightY) - object.y;

    if ((object.x <= Engine->Mouse->X && Engine->Mouse->X <= object.x + object.w) && (object.y <= Engine->Mouse->Y && Engine->Mouse->Y <= object.y + object.h))
    {
        return true;
    }

    return false;
}

logic slayCursorCollisionCamera(slayEngine* Engine, slayHitbox* Hitbox, double Distance)
{
    SDL_Rect object;

    slayApplyCamera(Engine, &object, (sint32)round(*Hitbox->ObjectX + Hitbox->UpperLeftX), (sint32)round(*Hitbox->ObjectY + Hitbox->UpperLeftY), (sint32)round(*Hitbox->ObjectX + Hitbox->LowerRightX) - (sint32)round(*Hitbox->ObjectX + Hitbox->UpperLeftX), (sint32)round(*Hitbox->ObjectY + Hitbox->LowerRightY) - (sint32)round(*Hitbox->ObjectY + Hitbox->UpperLeftY), Distance);

    if ((object.x <= Engine->Mouse->X && Engine->Mouse->X <= object.x + object.w) && (object.y <= Engine->Mouse->Y && Engine->Mouse->Y <= object.y + object.h))
    {
        return true;
    }

    return false;
}