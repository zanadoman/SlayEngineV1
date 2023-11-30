#include "SlayEngineV1.h"

slayHitbox* slayNewHitbox(double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY)
{
    slayHitbox* result;

    result = malloc(sizeof(slayHitbox));

    result->ObjectX = ObjectX;
    result->ObjectY = ObjectY;
    result->UpperLeftX = UpperLeftX;
    result->UpperLeftY = UpperLeftY;
    result->LowerRightX = LowerRightX;
    result->LowerRightY = LowerRightY;

    return result;
}

uint8 slayCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2)
{
    uint8 result;

    double Hitbox1UpperLeftX;
    double Hitbox1UpperLeftY;
    double Hitbox1LowerRightX;
    double Hitbox1LowerRightY;

    double Hitbox2UpperLeftX;
    double Hitbox2UpperLeftY;
    double Hitbox2LowerRightX;
    double Hitbox2LowerRightY;

    Hitbox1UpperLeftX = Hitbox1->UpperLeftX + *Hitbox1->ObjectX;
    Hitbox1UpperLeftY = Hitbox1->UpperLeftY + *Hitbox1->ObjectY;
    Hitbox1LowerRightX = Hitbox1->LowerRightX + *Hitbox1->ObjectX;
    Hitbox1LowerRightY = Hitbox1->LowerRightY + *Hitbox1->ObjectY;

    Hitbox2UpperLeftX = Hitbox2->UpperLeftX + (sint32)round(*Hitbox2->ObjectX);
    Hitbox2UpperLeftY = Hitbox2->UpperLeftY + (sint32)round(*Hitbox2->ObjectY);
    Hitbox2LowerRightX = Hitbox2->LowerRightX + (sint32)round(*Hitbox2->ObjectX);
    Hitbox2LowerRightY = Hitbox2->LowerRightY + (sint32)round(*Hitbox2->ObjectY);

    result = 0;
    if (((Hitbox1UpperLeftX <= Hitbox2LowerRightX && Hitbox2LowerRightX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2LowerRightY && Hitbox2LowerRightY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1UpperLeftX && Hitbox1UpperLeftX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1UpperLeftY && Hitbox1UpperLeftY <= Hitbox2LowerRightY)))
    {
        result = result | 1;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2UpperLeftX && Hitbox2UpperLeftX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2LowerRightY && Hitbox2LowerRightY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1LowerRightX && Hitbox1LowerRightX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1UpperLeftY && Hitbox1UpperLeftY <= Hitbox2LowerRightY)))
    {
        result = result | 2;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2LowerRightX && Hitbox2LowerRightX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2UpperLeftY && Hitbox2UpperLeftY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1UpperLeftX && Hitbox1UpperLeftX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1LowerRightY && Hitbox1LowerRightY <= Hitbox2LowerRightY)))
    {
        result = result | 4;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2UpperLeftX && Hitbox2UpperLeftX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2UpperLeftY && Hitbox2UpperLeftY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1LowerRightX && Hitbox1LowerRightX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1LowerRightY && Hitbox1LowerRightY <= Hitbox2LowerRightY)))
    {
        result = result | 8;
    }

    return result;
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