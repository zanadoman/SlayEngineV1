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

    uint64 Hitbox1UpperLeftX;
    uint64 Hitbox1UpperLeftY;
    uint64 Hitbox1LowerRightX;
    uint64 Hitbox1LowerRightY;

    uint64 Hitbox2UpperLeftX;
    uint64 Hitbox2UpperLeftY;
    uint64 Hitbox2LowerRightX;
    uint64 Hitbox2LowerRightY;

    Hitbox1UpperLeftX = Hitbox1->UpperLeftX + (sint32)round(*Hitbox1->ObjectX);
    Hitbox1UpperLeftY = Hitbox1->UpperLeftY + (sint32)round(*Hitbox1->ObjectY);
    Hitbox1LowerRightX = Hitbox1->LowerRightX + (sint32)round(*Hitbox1->ObjectX);
    Hitbox1LowerRightY = Hitbox1->LowerRightY + (sint32)round(*Hitbox1->ObjectY);

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