#include "SlayEngineV1.h"

slayMouse* slayNewMouse()
{
    return malloc(sizeof(slayMouse));
}

uint16 slayMouseMovement(slayMouse* Mouse)
{
    SDL_GetRelativeMouseState(&Mouse->MovementX, &Mouse->MovementY);

    return 0;
}

uint16 slayMouseButtons(slayMouse* Mouse)
{
    uint32 MouseState;

    MouseState = SDL_GetMouseState(NULL, NULL);
    if (MouseState & 1)
    {
        Mouse->LMB = true;
    }
    else
    {
        Mouse->LMB = false;
    }
    if (MouseState & 2)
    {
        Mouse->MMB = true;
    }
    else
    {
        Mouse->MMB = false;
    }
    if (MouseState & 4)
    {
        Mouse->RMB = true;
    }
    else
    {
        Mouse->RMB = false;
    }

    return 0;
}

uint16 slayCursorVisibility(logic Visibility)
{
    SDL_ShowCursor(Visibility);
    
    return 0;
}

logic slayCursorCollision(slayMouse* Mouse, slayHitbox* Hitbox)
{
    sint32 x, y;
    uint16 width, height;

    x = (sint32)round(*Hitbox->ObjectX + Hitbox->UpperLeftX);
    y = (sint32)round(*Hitbox->ObjectY + Hitbox->UpperLeftY);
    width = (sint32)round(*Hitbox->ObjectX + Hitbox->LowerRightX) - x;
    height = (sint32)round(*Hitbox->ObjectY + Hitbox->LowerRightY) - y;

    if ((x <= Mouse->X && Mouse->X <= x + width) && (y <= Mouse->Y && Mouse->Y <= y + height))
    {
        return true;
    }

    return false;
}

logic slayCursorCollisionCamera(slayMouse* Mouse, slayHitbox* Hitbox, double Distance, slayCamera* Camera)
{
    sint32 x, y;
    uint16 width, height;

    x = (sint32)round(*Hitbox->ObjectX + Hitbox->UpperLeftX);
    y = (sint32)round(*Hitbox->ObjectY + Hitbox->UpperLeftY);
    width = (sint32)round(*Hitbox->ObjectX + Hitbox->LowerRightX) - x;
    height = (sint32)round(*Hitbox->ObjectY + Hitbox->LowerRightY) - y;

    x = (sint32)round((x - (*Camera->OriginX + Camera->CenterX + (Camera->RelativeX / (Camera->Zoom * Distance)))) * (Camera->Zoom * Distance));
    y = (sint32)round((y - (*Camera->OriginY + Camera->CenterY + (Camera->RelativeY / (Camera->Zoom * Distance)))) * (Camera->Zoom * Distance));
    width = width * (Camera->Zoom * Distance);
    height = height * (Camera->Zoom * Distance);

    if ((x <= Mouse->X && Mouse->X <= x + width) && (y <= Mouse->Y && Mouse->Y <= y + height))
    {
        return true;
    }

    return false;
}