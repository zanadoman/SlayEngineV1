#include "SlayEngineV1.h"

uint8 slayMouseMovement(slayEngine* Engine)
{
    if (Engine == NULL)
    {
        printf("slayMouseMovement(): Engine must not be NULL\nParams: Engine: %p\n", Engine);
        exit(1);
    }

    SDL_GetRelativeMouseState(&Engine->Mouse->MovementX, &Engine->Mouse->MovementY);

    return 0;
}

uint8 slayMouseButtons(slayEngine* Engine)
{
    uint32 MouseState;

    if (Engine == NULL)
    {
        printf("slayMouseButtons(): Engine must not be NULL\nParams: Engine: %p\n", Engine);
        exit(1);
    }

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

logic slayCursorCollision(slayEngine* Engine, slayOverlapbox* Overlapbox)
{
    SDL_Rect object;

    if (Engine == NULL)
    {
        printf("slayCursorCollision(): Engine must not be NULL\nParams: Engine: %p, Overlapbox: %p\n", Engine, Overlapbox);
        exit(1);
    }
    if (Overlapbox == NULL)
    {
        printf("slayCursorCollision(): Overlapbox must not be NULL\nParams: Engine: %p, Overlapbox: %p\n", Engine, Overlapbox);
        exit(1);
    }

    object.x = (sint32)round(*Overlapbox->ObjectX + Overlapbox->UpperLeftX);
    object.y = (sint32)round(*Overlapbox->ObjectY + Overlapbox->UpperLeftY);
    object.w = (sint32)round(*Overlapbox->ObjectX + Overlapbox->LowerRightX) - object.x;
    object.h = (sint32)round(*Overlapbox->ObjectY + Overlapbox->LowerRightY) - object.y;

    if ((object.x <= Engine->Mouse->X && Engine->Mouse->X <= object.x + object.w) && (object.y <= Engine->Mouse->Y && Engine->Mouse->Y <= object.y + object.h))
    {
        return true;
    }

    return false;
}

logic slayCursorCollisionCamera(slayEngine* Engine, slayOverlapbox* Overlapbox, double Distance)
{
    SDL_Rect object;

    if (Engine == NULL)
    {
        printf("slayCursorCollisionCamera(): Engine must not be NULL\nParams: Engine: %p, Overlapbox: %p, Distance: %lf\n", Engine, Overlapbox, Distance);
        exit(1);
    }
    if (Overlapbox == NULL)
    {
        printf("slayCursorCollisionCamera(): Overlapbox must not be NULL\nParams: Engine: %p, Overlapbox: %p, Distance: %lf\n", Engine, Overlapbox, Distance);
        exit(1);
    }
    if (Distance <= 0)
    {
        printf("slayCursorCollisionCamera(): Distance must not be less than or equal to 0\nParams: Engine: %p, Overlapbox: %p, Distance: %lf\n", Engine, Overlapbox, Distance);
        exit(1);
    }

    slayApplyCamera(Engine, &object, (sint32)round(*Overlapbox->ObjectX + Overlapbox->UpperLeftX), (sint32)round(*Overlapbox->ObjectY + Overlapbox->UpperLeftY), (sint32)round(*Overlapbox->ObjectX + Overlapbox->LowerRightX) - (sint32)round(*Overlapbox->ObjectX + Overlapbox->UpperLeftX), (sint32)round(*Overlapbox->ObjectY + Overlapbox->LowerRightY) - (sint32)round(*Overlapbox->ObjectY + Overlapbox->UpperLeftY), Distance);

    if ((object.x <= Engine->Mouse->X && Engine->Mouse->X <= object.x + object.w) && (object.y <= Engine->Mouse->Y && Engine->Mouse->Y <= object.y + object.h))
    {
        return true;
    }

    return false;
}