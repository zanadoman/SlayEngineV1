#include "SlayEngineV1.h"

uint8 slayResolveCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2, uint64 Hitbox1Force);
uint8 slayNewCollisionBranch(array CollisionLayer, uint64 Root, uint64 RootForce, uint64 CurrentBranch);

slayHitbox* slayNewHitbox(void* Parent, uint64 ParentType, double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY, uint16 Force, uint16 Resistance)
{
    slayHitbox* result;

    if (ObjectX == NULL)
    {
        printf("slayNewHitbox(): ObjectX must not be NULL\nParams: Parent: %p, ParentType: %lld, ObjectX: %p, ObjectY: %p, UpperleftX: %d, UpperLeftY: %d, LowerRightX: %d, LowerRightY: %d, Force: %d, Resistance: %d\n", Parent, ParentType, ObjectX, ObjectY, UpperLeftX, UpperLeftY, LowerRightX, LowerRightY, Force, Resistance);
        exit(1);
    }
    if (ObjectY == NULL)
    {
        printf("slayNewHitbox(): ObjectY must not be NULL\nParams: Parent: %p, ParentType: %lld, ObjectX: %lf, ObjectY: %p, UpperleftX: %d, UpperLeftY: %d, LowerRightX: %d, LowerRightY: %d, Force: %d, Resistance: %d\n", Parent, ParentType, *ObjectX, ObjectY, UpperLeftX, UpperLeftY, LowerRightX, LowerRightY, Force, Resistance);
        exit(1);
    }

    result = malloc(sizeof(slayHitbox));
    if (result == NULL)
    {
        printf("slayNewHitbox(): Memory allocation failed\nParams: Parent: %p, ParentType: %lld, ObjectX: %lf, ObjectY: %lf, UpperleftX: %d, UpperLeftY: %d, LowerRightX: %d, LowerRightY: %d, Force: %d, Resistance: %d\n", Parent, ParentType, *ObjectX, *ObjectY, UpperLeftX, UpperLeftY, LowerRightX, LowerRightY, Force, Resistance);
        exit(1);
    }

    result->Parent = Parent;
    result->ParentType = ParentType;

    result->ObjectX = ObjectX;
    result->ObjectY = ObjectY;
    result->ObjectPrevX = *result->ObjectX;
    result->ObjectPrevY = *result->ObjectY;

    result->UpperLeftX = UpperLeftX;
    result->UpperLeftY = UpperLeftY;
    result->LowerRightX = LowerRightX;
    result->LowerRightY = LowerRightY;

    result->Force = Force;
    result->Resistance = Resistance;

    return result;
}

slayOverlapbox* slayNewOverlapbox(void* Parent, uint64 ParentType, double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY)
{
    slayOverlapbox* result;

    if (ObjectX == NULL)
    {
        printf("slayNewOverlapbox(): ObjectX must not be NULL\nParams: Parent: %p, ParentType: %lld, ObjectX: %p, ObjectY: %p, UpperleftX: %d, UpperLeftY: %d, LowerRightX: %d, LowerRightY: %d\n", Parent, ParentType, ObjectX, ObjectY, UpperLeftX, UpperLeftY, LowerRightX, LowerRightY);
        exit(1);
    }
    if (ObjectY == NULL)
    {
        printf("slayNewOverlapbox(): ObjectY must not be NULL\nParams: Parent: %p, ParentType: %lld, ObjectX: %lf, ObjectY: %p, UpperleftX: %d, UpperLeftY: %d, LowerRightX: %d, LowerRightY: %d\n", Parent, ParentType, *ObjectX, ObjectY, UpperLeftX, UpperLeftY, LowerRightX, LowerRightY);
        exit(1);
    }

    result = malloc(sizeof(slayOverlapbox));
    if (result == NULL)
    {
        printf("slayNewOverlapbox(): Memory allocation failed\nParams: Parent %p, ParentType: %lld, ObjectX: %lf, ObjectY: %lf, UpperleftX: %d, UpperLeftY: %d, LowerRightX: %d, LowerRightY: %d\n", Parent, ParentType, *ObjectX, *ObjectY, UpperLeftX, UpperLeftY, LowerRightX, LowerRightY);
        exit(1);
    }

    result->Parent = Parent;
    result->ParentType = ParentType;

    result->ObjectX = ObjectX;
    result->ObjectY = ObjectY;

    result->UpperLeftX = UpperLeftX;
    result->UpperLeftY = UpperLeftY;
    result->LowerRightX = LowerRightX;
    result->LowerRightY = LowerRightY;

    return result;
}

logic slayCheckOverlap(slayOverlapbox* Overlapbox1, slayOverlapbox* Overlapbox2)
{
    double Overlapbox1UpperLeftX;
    double Overlapbox1UpperLeftY;
    double Overlapbox1LowerRightX;
    double Overlapbox1LowerRightY;

    double Overlapbox2UpperLeftX;
    double Overlapbox2UpperLeftY;
    double Overlapbox2LowerRightX;
    double Overlapbox2LowerRightY;

    Overlapbox1UpperLeftX = Overlapbox1->UpperLeftX + *Overlapbox1->ObjectX;
    Overlapbox1UpperLeftY = Overlapbox1->UpperLeftY + *Overlapbox1->ObjectY;
    Overlapbox1LowerRightX = Overlapbox1->LowerRightX + *Overlapbox1->ObjectX;
    Overlapbox1LowerRightY = Overlapbox1->LowerRightY + *Overlapbox1->ObjectY;

    Overlapbox2UpperLeftX = Overlapbox2->UpperLeftX + *Overlapbox2->ObjectX;
    Overlapbox2UpperLeftY = Overlapbox2->UpperLeftY + *Overlapbox2->ObjectY;
    Overlapbox2LowerRightX = Overlapbox2->LowerRightX + *Overlapbox2->ObjectX;
    Overlapbox2LowerRightY = Overlapbox2->LowerRightY + *Overlapbox2->ObjectY;

    if (Overlapbox1LowerRightX < Overlapbox2UpperLeftX || Overlapbox2LowerRightX < Overlapbox1UpperLeftX || Overlapbox1LowerRightY < Overlapbox2UpperLeftY || Overlapbox2LowerRightY < Overlapbox1UpperLeftY)
    {
        return false;
    }

    if (((Overlapbox1UpperLeftX <= Overlapbox2LowerRightX && Overlapbox2LowerRightX <= Overlapbox1LowerRightX) && (Overlapbox1UpperLeftY <= Overlapbox2LowerRightY && Overlapbox2LowerRightY <= Overlapbox1LowerRightY)) || ((Overlapbox2UpperLeftX <= Overlapbox1UpperLeftX && Overlapbox1UpperLeftX <= Overlapbox2LowerRightX) && (Overlapbox2UpperLeftY <= Overlapbox1UpperLeftY && Overlapbox1UpperLeftY <= Overlapbox2LowerRightY)))
    {
        return true; //top left
    }
    if (((Overlapbox1UpperLeftX <= Overlapbox2UpperLeftX && Overlapbox2UpperLeftX <= Overlapbox1LowerRightX) && (Overlapbox1UpperLeftY <= Overlapbox2LowerRightY && Overlapbox2LowerRightY <= Overlapbox1LowerRightY)) || ((Overlapbox2UpperLeftX <= Overlapbox1LowerRightX && Overlapbox1LowerRightX <= Overlapbox2LowerRightX) && (Overlapbox2UpperLeftY <= Overlapbox1UpperLeftY && Overlapbox1UpperLeftY <= Overlapbox2LowerRightY)))
    {
        return true; //top right
    }
    if (((Overlapbox1UpperLeftX <= Overlapbox2LowerRightX && Overlapbox2LowerRightX <= Overlapbox1LowerRightX) && (Overlapbox1UpperLeftY <= Overlapbox2UpperLeftY && Overlapbox2UpperLeftY <= Overlapbox1LowerRightY)) || ((Overlapbox2UpperLeftX <= Overlapbox1UpperLeftX && Overlapbox1UpperLeftX <= Overlapbox2LowerRightX) && (Overlapbox2UpperLeftY <= Overlapbox1LowerRightY && Overlapbox1LowerRightY <= Overlapbox2LowerRightY)))
    {
        return true; //bottom left
    }
    if (((Overlapbox1UpperLeftX <= Overlapbox2UpperLeftX && Overlapbox2UpperLeftX <= Overlapbox1LowerRightX) && (Overlapbox1UpperLeftY <= Overlapbox2UpperLeftY && Overlapbox2UpperLeftY <= Overlapbox1LowerRightY)) || ((Overlapbox2UpperLeftX <= Overlapbox1LowerRightX && Overlapbox1LowerRightX <= Overlapbox2LowerRightX) && (Overlapbox2UpperLeftY <= Overlapbox1LowerRightY && Overlapbox1LowerRightY <= Overlapbox2LowerRightY)))
    {
        return true; //bottom right
    }

    return false;
}

logic slayCheckCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2)
{
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

    Hitbox2UpperLeftX = Hitbox2->UpperLeftX + *Hitbox2->ObjectX;
    Hitbox2UpperLeftY = Hitbox2->UpperLeftY + *Hitbox2->ObjectY;
    Hitbox2LowerRightX = Hitbox2->LowerRightX + *Hitbox2->ObjectX;
    Hitbox2LowerRightY = Hitbox2->LowerRightY + *Hitbox2->ObjectY;

    if (Hitbox1LowerRightX < Hitbox2UpperLeftX || Hitbox2LowerRightX < Hitbox1UpperLeftX || Hitbox1LowerRightY < Hitbox2UpperLeftY || Hitbox2LowerRightY < Hitbox1UpperLeftY)
    {
        return false;
    }

    if (((Hitbox1UpperLeftX <= Hitbox2LowerRightX && Hitbox2LowerRightX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2LowerRightY && Hitbox2LowerRightY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1UpperLeftX && Hitbox1UpperLeftX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1UpperLeftY && Hitbox1UpperLeftY <= Hitbox2LowerRightY)))
    {
        return true; //top left
    }
    if (((Hitbox1UpperLeftX <= Hitbox2UpperLeftX && Hitbox2UpperLeftX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2LowerRightY && Hitbox2LowerRightY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1LowerRightX && Hitbox1LowerRightX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1UpperLeftY && Hitbox1UpperLeftY <= Hitbox2LowerRightY)))
    {
        return true; //top right
    }
    if (((Hitbox1UpperLeftX <= Hitbox2LowerRightX && Hitbox2LowerRightX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2UpperLeftY && Hitbox2UpperLeftY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1UpperLeftX && Hitbox1UpperLeftX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1LowerRightY && Hitbox1LowerRightY <= Hitbox2LowerRightY)))
    {
        return true; //bottom left
    }
    if (((Hitbox1UpperLeftX <= Hitbox2UpperLeftX && Hitbox2UpperLeftX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2UpperLeftY && Hitbox2UpperLeftY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1LowerRightX && Hitbox1LowerRightX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1LowerRightY && Hitbox1LowerRightY <= Hitbox2LowerRightY)))
    {
        return true; //bottom right
    }

    return false;
}

slayCollision slayGetCollisionDirection(slayHitbox* Hitbox1, slayHitbox* Hitbox2)
{
    slayHitbox* Hitbox1Prev;

    double Hitbox1PrevUpperLeftX;
    double Hitbox1PrevUpperLeftY;
    double Hitbox1PrevLowerRightX;
    double Hitbox1PrevLowerRightY;

    double Hitbox1UpperLeftX;
    double Hitbox1UpperLeftY;
    double Hitbox1LowerRightX;
    double Hitbox1LowerRightY;

    double Hitbox2UpperLeftX;
    double Hitbox2UpperLeftY;
    double Hitbox2LowerRightX;
    double Hitbox2LowerRightY;

    if (!slayCheckCollision(Hitbox1, Hitbox2))
    {
        return slayColl_NONE;
    }

    Hitbox1Prev = slayNewHitbox(NULL, 0, &Hitbox1->ObjectPrevX, &Hitbox1->ObjectPrevY, Hitbox1->UpperLeftX, Hitbox1->UpperLeftY, Hitbox1->LowerRightX, Hitbox1->LowerRightY, 0, 0);
    if (slayCheckCollision(Hitbox1Prev, Hitbox2))
    {
        free(Hitbox1Prev);
        return slayColl_NONE;
    }
    free(Hitbox1Prev);

    Hitbox1PrevUpperLeftX = Hitbox1->UpperLeftX + Hitbox1->ObjectPrevX;
    Hitbox1PrevUpperLeftY = Hitbox1->UpperLeftY + Hitbox1->ObjectPrevY;
    Hitbox1PrevLowerRightX = Hitbox1->LowerRightX + Hitbox1->ObjectPrevX;
    Hitbox1PrevLowerRightY = Hitbox1->LowerRightY + Hitbox1->ObjectPrevY;

    Hitbox1UpperLeftX = Hitbox1->UpperLeftX + *Hitbox1->ObjectX;
    Hitbox1UpperLeftY = Hitbox1->UpperLeftY + *Hitbox1->ObjectY;
    Hitbox1LowerRightX = Hitbox1->LowerRightX + *Hitbox1->ObjectX;
    Hitbox1LowerRightY = Hitbox1->LowerRightY + *Hitbox1->ObjectY;

    Hitbox2UpperLeftX = Hitbox2->UpperLeftX + *Hitbox2->ObjectX;
    Hitbox2UpperLeftY = Hitbox2->UpperLeftY + *Hitbox2->ObjectY;
    Hitbox2LowerRightX = Hitbox2->LowerRightX + *Hitbox2->ObjectX;
    Hitbox2LowerRightY = Hitbox2->LowerRightY + *Hitbox2->ObjectY;

    if ((Hitbox2UpperLeftX <= Hitbox1PrevUpperLeftX && Hitbox1PrevLowerRightX <= Hitbox2LowerRightX) || (Hitbox1PrevUpperLeftX <= Hitbox2UpperLeftX && Hitbox2LowerRightX <= Hitbox1PrevLowerRightX))
    {
        if (Hitbox2LowerRightY < Hitbox1PrevUpperLeftY)
        {
            return slayColl_TOP;
        }
        if (Hitbox1PrevLowerRightY < Hitbox2UpperLeftY)
        {    
            return slayColl_BOTTOM;
        }
    }
    if ((Hitbox2UpperLeftY <= Hitbox1PrevUpperLeftY && Hitbox1PrevLowerRightY <= Hitbox2LowerRightY) || (Hitbox1PrevUpperLeftY <= Hitbox2UpperLeftY && Hitbox2LowerRightY <= Hitbox1PrevLowerRightY))
    {
        if (Hitbox2LowerRightX < Hitbox1PrevUpperLeftX)
        {
            return slayColl_LEFT;
        }
        if (Hitbox1PrevLowerRightX < Hitbox2UpperLeftX)
        {
            return slayColl_RIGHT;
        }
    }

    if (Hitbox2UpperLeftX < Hitbox1PrevUpperLeftX && Hitbox2UpperLeftY < Hitbox1PrevUpperLeftY)
    {
        if (Hitbox1PrevUpperLeftX <= Hitbox2LowerRightX)
        {
            return slayColl_TOP;
        }
        if (Hitbox1PrevUpperLeftY <= Hitbox2LowerRightY)
        {
            return slayColl_LEFT;
        }
        if (Hitbox2LowerRightX - Hitbox1UpperLeftX > Hitbox2LowerRightY - Hitbox1UpperLeftY)
        {
            return slayColl_TOP;
        }
        if (Hitbox2LowerRightX - Hitbox1UpperLeftX < Hitbox2LowerRightY - Hitbox1UpperLeftY)
        {
            return slayColl_LEFT;
        }

        return slayColl_TOP_LEFT;
    }
    if (Hitbox1PrevLowerRightX < Hitbox2LowerRightX && Hitbox2UpperLeftY < Hitbox1PrevUpperLeftY)
    {
        if (Hitbox2UpperLeftX <= Hitbox1PrevLowerRightX)
        {
            return slayColl_TOP;
        }
        if (Hitbox1PrevUpperLeftY <= Hitbox2LowerRightY)
        {
            return slayColl_RIGHT;
        }
        if (Hitbox1LowerRightX - Hitbox2UpperLeftX > Hitbox2LowerRightY - Hitbox1UpperLeftY)
        {
            return slayColl_TOP;
        }
        if (Hitbox1LowerRightX - Hitbox2UpperLeftX < Hitbox2LowerRightY - Hitbox1UpperLeftY)
        {
            return slayColl_RIGHT;
        }

        return slayColl_TOP_RIGHT;
    }
    if (Hitbox2UpperLeftX < Hitbox1PrevUpperLeftX && Hitbox1PrevLowerRightY < Hitbox2LowerRightY)
    {
        if (Hitbox1PrevUpperLeftX <= Hitbox2LowerRightX)
        {
            return slayColl_BOTTOM;
        }
        if (Hitbox2UpperLeftY <= Hitbox1PrevLowerRightY)
        {
            return slayColl_LEFT;
        }
        if (Hitbox2LowerRightX - Hitbox1UpperLeftX > Hitbox1LowerRightY - Hitbox2UpperLeftY)
        {
            return slayColl_BOTTOM;
        }
        if (Hitbox2LowerRightX - Hitbox1UpperLeftX < Hitbox1LowerRightY - Hitbox2UpperLeftY)
        {
            return slayColl_LEFT;
        }

        return slayColl_BOT_LEFT;
    }
    if (Hitbox1PrevLowerRightX < Hitbox2LowerRightX && Hitbox1PrevLowerRightY < Hitbox2LowerRightY)
    {
        if (Hitbox2UpperLeftX <= Hitbox1PrevLowerRightX)
        {
            return slayColl_BOTTOM;
        }
        if (Hitbox2UpperLeftY <= Hitbox1PrevLowerRightY)
        {
            return slayColl_RIGHT;
        }
        if (Hitbox1LowerRightX - Hitbox2UpperLeftX > Hitbox1LowerRightY - Hitbox2UpperLeftY)
        {
            return slayColl_BOTTOM;
        }
        if (Hitbox1LowerRightX - Hitbox2UpperLeftX < Hitbox1LowerRightY - Hitbox2UpperLeftY)
        {
            return slayColl_RIGHT;
        }

        return slayColl_BOT_RIGHT;
    }

    return slayColl_NONE;
}

uint8 slayResolveCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2, uint64 Hitbox1Force)
{
    slayCollision direction;
    double ratio;

    double Hitbox1UpperLeftX;
    double Hitbox1UpperLeftY;
    double Hitbox1LowerRightX;
    double Hitbox1LowerRightY;

    double Hitbox2UpperLeftX;
    double Hitbox2UpperLeftY;
    double Hitbox2LowerRightX;
    double Hitbox2LowerRightY;

    direction = slayGetCollisionDirection(Hitbox1, Hitbox2);
    if (direction == slayColl_NONE)
    {
        return 1;
    }

    Hitbox1UpperLeftX = Hitbox1->UpperLeftX + *Hitbox1->ObjectX;
    Hitbox1UpperLeftY = Hitbox1->UpperLeftY + *Hitbox1->ObjectY;
    Hitbox1LowerRightX = Hitbox1->LowerRightX + *Hitbox1->ObjectX;
    Hitbox1LowerRightY = Hitbox1->LowerRightY + *Hitbox1->ObjectY;

    Hitbox2UpperLeftX = Hitbox2->UpperLeftX + *Hitbox2->ObjectX;
    Hitbox2UpperLeftY = Hitbox2->UpperLeftY + *Hitbox2->ObjectY;
    Hitbox2LowerRightX = Hitbox2->LowerRightX + *Hitbox2->ObjectX;
    Hitbox2LowerRightY = Hitbox2->LowerRightY + *Hitbox2->ObjectY;

    if (Hitbox1Force <= Hitbox2->Resistance)
    {
        switch (direction)
        {
            case slayColl_TOP:
                *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY + EPSILON;
            return 0;

            case slayColl_BOTTOM:
                *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY + EPSILON;
            return 0;

            case slayColl_LEFT:
                *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX + EPSILON;
            return 0;

            case slayColl_RIGHT:
                *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX + EPSILON;
            return 0;

            case slayColl_TOP_LEFT:
                *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY + EPSILON;
                *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX + EPSILON;
            return 0;

            case slayColl_TOP_RIGHT:
                *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY + EPSILON;
                *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX + EPSILON;
            return 0;

            case slayColl_BOT_LEFT:
                *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY + EPSILON;
                *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX + EPSILON;
            return 0;

            case slayColl_BOT_RIGHT:
                *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY + EPSILON;
                *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX + EPSILON;
            return 0;
        }
    }
    else
    {
        ratio = (double)Hitbox1Force / (Hitbox1Force + Hitbox2->Resistance);

        switch (direction)
        {
            case slayColl_TOP:
                *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratio;
            return 0;

            case slayColl_BOTTOM:
                *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratio;
            return 0;

            case slayColl_LEFT:
                *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratio;
            return 0;

            case slayColl_RIGHT:
                *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratio;
            return 0;

            case slayColl_TOP_LEFT:
                *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratio;

                *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratio;
            return 0;

            case slayColl_TOP_RIGHT:
                *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratio;

                *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratio;
            return 0;

            case slayColl_BOT_LEFT:
                *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratio;

                *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratio;
            return 0;

            case slayColl_BOT_RIGHT:
                *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratio;

                *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratio) + EPSILON;
                *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratio;
            return 0;
        }
    }
}

uint8 slayResolveCollisionLayer(array CollisionLayer)
{
    uint64 ForceRequirement;

    for (uint64 Root = 0; Root < CollisionLayer->Length; Root++)
    {
        ForceRequirement = 0;
        for (uint64 NextBranch = 0; NextBranch < CollisionLayer->Length; NextBranch++)
        {
            if (NextBranch != Root && slayGetCollisionDirection(CollisionLayer->Values[Root], CollisionLayer->Values[NextBranch]) != slayColl_NONE)
            {
                ForceRequirement += ((slayHitbox*)CollisionLayer->Values[NextBranch])->Resistance;
            }
        }

        for (uint64 NextBranch = 0; NextBranch < CollisionLayer->Length; NextBranch++)
        {
            if (NextBranch != Root && ((slayHitbox*)CollisionLayer->Values[Root])->Force <= ForceRequirement)
            {
                slayResolveCollision(CollisionLayer->Values[Root], CollisionLayer->Values[NextBranch], 0);
            }
            else if (NextBranch != Root && slayResolveCollision(CollisionLayer->Values[Root], CollisionLayer->Values[NextBranch], ((slayHitbox*)CollisionLayer->Values[NextBranch])->Resistance + ((slayHitbox*)CollisionLayer->Values[Root])->Force - ForceRequirement) == 0)
            {
                slayNewCollisionBranch(CollisionLayer, Root, ((slayHitbox*)CollisionLayer->Values[Root])->Force - ForceRequirement, NextBranch);
                slayResolveCollision(CollisionLayer->Values[Root], CollisionLayer->Values[NextBranch], 0);
            }
        }
    }

    for (uint64 i = 0; i < CollisionLayer->Length; i++)
    {
        ((slayHitbox*)CollisionLayer->Values[i])->ObjectPrevX = *(((slayHitbox*)CollisionLayer->Values[i])->ObjectX);
        ((slayHitbox*)CollisionLayer->Values[i])->ObjectPrevY = *(((slayHitbox*)CollisionLayer->Values[i])->ObjectY);
    }

    return 0;
}

uint8 slayNewCollisionBranch(array CollisionLayer, uint64 Root, uint64 RootForce, uint64 CurrentBranch)
{
    uint64 ForceRequirement;

    ForceRequirement = 0;
    for (uint64 NextBranch = 0; NextBranch < CollisionLayer->Length; NextBranch++)
    {
        if (NextBranch != Root && NextBranch != CurrentBranch && slayGetCollisionDirection(CollisionLayer->Values[CurrentBranch], CollisionLayer->Values[NextBranch]) != slayColl_NONE)
        {
            ForceRequirement += ((slayHitbox*)CollisionLayer->Values[NextBranch])->Resistance;
        }
    }

    for (uint64 NextBranch = 0; NextBranch < CollisionLayer->Length; NextBranch++)
    {
        if (NextBranch != Root && NextBranch != CurrentBranch && RootForce <= ForceRequirement)
        {
            slayResolveCollision(CollisionLayer->Values[CurrentBranch], CollisionLayer->Values[NextBranch], 0);
        }
        else if (NextBranch != Root && NextBranch != CurrentBranch && slayResolveCollision(CollisionLayer->Values[CurrentBranch], CollisionLayer->Values[NextBranch], ((slayHitbox*)CollisionLayer->Values[NextBranch])->Resistance + RootForce - ForceRequirement) == 0)
        {
            slayNewCollisionBranch(CollisionLayer, Root, RootForce - ForceRequirement, NextBranch);
            slayResolveCollision(CollisionLayer->Values[CurrentBranch], CollisionLayer->Values[NextBranch], 0);
        }
    }

    return 0;
}

uint8 slayRenderOverlapbox(slayEngine* Engine, slayOverlapbox* Overlapbox, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    slayRenderColor(Engine, *Overlapbox->ObjectX + Overlapbox->UpperLeftX, *Overlapbox->ObjectY + Overlapbox->UpperLeftY, Overlapbox->LowerRightX - Overlapbox->UpperLeftX, Overlapbox->LowerRightY - Overlapbox->UpperLeftY, ColorR, ColorG, ColorB, ColorA);

    return 0;
}

uint8 slayRenderOverlapboxCamera(slayEngine* Engine, slayOverlapbox* Overlapbox, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    slayRenderColorCamera(Engine, *Overlapbox->ObjectX + Overlapbox->UpperLeftX, *Overlapbox->ObjectY + Overlapbox->UpperLeftY, Overlapbox->LowerRightX - Overlapbox->UpperLeftX, Overlapbox->LowerRightY - Overlapbox->UpperLeftY, Distance, ColorR, ColorG, ColorB, ColorA);

    return 0;
}

uint8 slayRenderHitbox(slayEngine* Engine, slayHitbox* Hitbox, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    slayRenderColor(Engine, *Hitbox->ObjectX + Hitbox->UpperLeftX, *Hitbox->ObjectY + Hitbox->UpperLeftY, Hitbox->LowerRightX - Hitbox->UpperLeftX, Hitbox->LowerRightY - Hitbox->UpperLeftY, ColorR, ColorG, ColorB, ColorA);

    return 0;
}

uint8 slayRenderHitboxCamera(slayEngine* Engine, slayHitbox* Hitbox, double Distance, uint8 ColorR, uint8 ColorG, uint8 ColorB, uint8 ColorA)
{
    slayRenderColorCamera(Engine, *Hitbox->ObjectX + Hitbox->UpperLeftX, *Hitbox->ObjectY+ Hitbox->UpperLeftY, Hitbox->LowerRightX - Hitbox->UpperLeftX, Hitbox->LowerRightY - Hitbox->UpperLeftY, Distance, ColorR, ColorG, ColorB, ColorA);

    return 0;
}