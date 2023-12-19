#include "SlayEngineV1.h"

uint8 slayResolveCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2);
uint8 slayResolveCollisionOrder(slayHitbox* Hitbox1, slayHitbox* Hitbox2);

slayHitbox* slayNewHitbox(void* Parent, uint64 ParentType, double* ObjectX, double* ObjectY, double* ObjectPrevX, double* ObjectPrevY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY, uint16 Force, uint16 Resistance, double* MinX, double* MinY, double* MaxX, double* MaxY)
{
    slayHitbox* result;

    result = malloc(sizeof(slayHitbox));
    if (result == NULL)
    {
        printf("ERROR Unable to allocate memory for HITBOX\n");
        exit(1);
    }
    if (ObjectX == NULL)
    {
        printf("ERROR Unable to create HITBOX (ObjectX NULL)");
        exit(1);
    }
    if (ObjectY == NULL)
    {
        printf("ERROR UNABLE to create HITBOX (ObjectY NULL)");
        exit(1);
    }
    if (ObjectPrevX == NULL)
    {
        printf("ERROR Unable to create HITBOX (ObjectPrevX NULL)");
        exit(1);
    }
    if (ObjectPrevY == NULL)
    {
        printf("ERROR Unable to create HITBOX (ObjectPrevY NULL)");
        exit(1);
    }

    result->Parent = Parent;
    result->ParentType = ParentType;

    result->ObjectX = ObjectX;
    result->ObjectY = ObjectY;
    result->ObjectPrevX = ObjectPrevX;
    result->ObjectPrevY = ObjectPrevY;

    result->UpperLeftX = UpperLeftX;
    result->UpperLeftY = UpperLeftY;
    result->LowerRightX = LowerRightX;
    result->LowerRightY = LowerRightY;

    result->Force = Force;
    result->Resistance = Resistance;

    result->MinX = MinX;
    result->MinY = MinY;
    result->MaxX = MaxX;
    result->MaxY = MaxY;

    return result;
}

slayOverlapbox* slayNewOverlapbox(void* Parent, uint64 ParentType, double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY)
{
    slayOverlapbox* result;

    result = malloc(sizeof(slayOverlapbox));
    if (result == NULL)
    {
        printf("ERROR Unable to allocate memory for OVERLAPBOX\n");
        exit(1);
    }
    if (ObjectX == NULL)
    {
        printf("ERROR Unable to create OVERLAPBOX (ObjectX NULL)");
        exit(1);
    }
    if (ObjectY == NULL)
    {
        printf("ERROR UNABLE to create OVERLAPBOX (ObjectY NULL)");
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

    Hitbox1Prev = slayNewHitbox(NULL, 0, Hitbox1->ObjectPrevX, Hitbox1->ObjectPrevY, Hitbox1->ObjectPrevX, Hitbox1->ObjectPrevY, Hitbox1->UpperLeftX, Hitbox1->UpperLeftY, Hitbox1->LowerRightX, Hitbox1->LowerRightY, 0, 0, 0, 0, 0, 0);
    if (slayCheckCollision(Hitbox1Prev, Hitbox2))
    {
        free(Hitbox1Prev);
        return slayColl_ERROR;
    }
    free(Hitbox1Prev);

    Hitbox1PrevUpperLeftX = Hitbox1->UpperLeftX + *Hitbox1->ObjectPrevX;
    Hitbox1PrevUpperLeftY = Hitbox1->UpperLeftY + *Hitbox1->ObjectPrevY;
    Hitbox1PrevLowerRightX = Hitbox1->LowerRightX + *Hitbox1->ObjectPrevX;
    Hitbox1PrevLowerRightY = Hitbox1->LowerRightY + *Hitbox1->ObjectPrevY;

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

    return slayColl_ERROR;
}

uint8 slayResolveCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2)
{
    double ratio;

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
        return 0;
    }

    Hitbox1UpperLeftX = Hitbox1->UpperLeftX + *Hitbox1->ObjectX;
    Hitbox1UpperLeftY = Hitbox1->UpperLeftY + *Hitbox1->ObjectY;
    Hitbox1LowerRightX = Hitbox1->LowerRightX + *Hitbox1->ObjectX;
    Hitbox1LowerRightY = Hitbox1->LowerRightY + *Hitbox1->ObjectY;

    Hitbox2UpperLeftX = Hitbox2->UpperLeftX + *Hitbox2->ObjectX;
    Hitbox2UpperLeftY = Hitbox2->UpperLeftY + *Hitbox2->ObjectY;
    Hitbox2LowerRightX = Hitbox2->LowerRightX + *Hitbox2->ObjectX;
    Hitbox2LowerRightY = Hitbox2->LowerRightY + *Hitbox2->ObjectY;

    if (Hitbox1->Force <= Hitbox2->Resistance)
    {
        switch (slayGetCollisionDirection(Hitbox1, Hitbox2))
        {
            case slayColl_TOP:
                *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY + EPSILON;
            return 1;

            case slayColl_BOTTOM:
                *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY + EPSILON;
            return 1;

            case slayColl_LEFT:
                *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX + EPSILON;
            return 1;

            case slayColl_RIGHT:
                *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX + EPSILON;
            return 1;

            case slayColl_TOP_LEFT:
                *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY + EPSILON;
                *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX + EPSILON;
            return 1;

            case slayColl_TOP_RIGHT:
                *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY + EPSILON;
                *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX + EPSILON;
            return 1;

            case slayColl_BOT_LEFT:
                *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY + EPSILON;
                *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX + EPSILON;
            return 1;

            case slayColl_BOT_RIGHT:
                *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY + EPSILON;
                *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX + EPSILON;
            return 1;

            default:
            return 0;
        }
    }
    else
    {
        ratio = (double)Hitbox2->Resistance / (double)Hitbox1->Force;

        switch (slayGetCollisionDirection(Hitbox1, Hitbox2))
        {
            case slayColl_TOP:
                *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratio + EPSILON;
                *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratio);
            break;

            case slayColl_BOTTOM:
                *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratio + EPSILON;
                *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratio);
            break;

            case slayColl_LEFT:
                *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratio + EPSILON;
                *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratio);
            break;

            case slayColl_RIGHT:
                *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratio + EPSILON;
                *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratio);
            break;

            case slayColl_TOP_LEFT:
                *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratio + EPSILON;
                *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratio);

                *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratio + EPSILON;
                *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratio);
            break;

            case slayColl_TOP_RIGHT:
                *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratio + EPSILON;
                *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratio);

                *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratio + EPSILON;
                *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratio);
            break;

            case slayColl_BOT_LEFT:
                *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratio + EPSILON;
                *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratio);

                *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratio + EPSILON;
                *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratio);
            break;

            case slayColl_BOT_RIGHT:
                *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratio + EPSILON;
                *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratio);

                *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratio + EPSILON;
                *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratio);
            break;

            default:
            return 0;
        }
    }

    if (Hitbox2->MinX != NULL && Hitbox2UpperLeftX < *Hitbox2->MinX)
    {
        *Hitbox2->ObjectX += *Hitbox2->MinX - Hitbox2UpperLeftX;
        *Hitbox1->ObjectX += *Hitbox2->MinX - Hitbox2UpperLeftX;
    }
    else if (Hitbox2->MaxX != NULL && *Hitbox2->MaxX < Hitbox2LowerRightX)
    {
        *Hitbox2->ObjectX -= Hitbox2LowerRightX - *Hitbox2->MaxX;
        *Hitbox1->ObjectX -= Hitbox2LowerRightX - *Hitbox2->MaxX;
    }
    if (Hitbox2->MinY != NULL && Hitbox2UpperLeftY < *Hitbox2->MinY)
    {
        *Hitbox2->ObjectY += *Hitbox2->MinY - Hitbox2UpperLeftY;
        *Hitbox1->ObjectY += *Hitbox2->MinY - Hitbox2UpperLeftY;
    }
    else if (Hitbox2->MaxY != NULL && *Hitbox2->MaxY < Hitbox2LowerRightY)
    {
        *Hitbox2->ObjectY -= Hitbox2LowerRightY - *Hitbox2->MaxY;
        *Hitbox1->ObjectY -= Hitbox2LowerRightY - *Hitbox2->MaxY;
    }

    return 1;
}

uint8 slayResolveCollisionOrder(slayHitbox* Hitbox1, slayHitbox* Hitbox2)
{
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
        return 0;
    }

    Hitbox1UpperLeftX = Hitbox1->UpperLeftX + *Hitbox1->ObjectX;
    Hitbox1UpperLeftY = Hitbox1->UpperLeftY + *Hitbox1->ObjectY;
    Hitbox1LowerRightX = Hitbox1->LowerRightX + *Hitbox1->ObjectX;
    Hitbox1LowerRightY = Hitbox1->LowerRightY + *Hitbox1->ObjectY;

    Hitbox2UpperLeftX = Hitbox2->UpperLeftX + *Hitbox2->ObjectX;
    Hitbox2UpperLeftY = Hitbox2->UpperLeftY + *Hitbox2->ObjectY;
    Hitbox2LowerRightX = Hitbox2->LowerRightX + *Hitbox2->ObjectX;
    Hitbox2LowerRightY = Hitbox2->LowerRightY + *Hitbox2->ObjectY;

    switch (slayGetCollisionDirection(Hitbox1, Hitbox2))
    {
        case slayColl_TOP:
            *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY + EPSILON;
        return 1;

        case slayColl_BOTTOM:
            *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY + EPSILON;
        return 1;

        case slayColl_LEFT:
            *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX + EPSILON;
        return 1;

        case slayColl_RIGHT:
            *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX + EPSILON;
        return 1;

        case slayColl_TOP_LEFT:
            *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY + EPSILON;
            *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX + EPSILON;
        return 1;

        case slayColl_TOP_RIGHT:
            *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY + EPSILON;
            *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX + EPSILON;
        return 1;

        case slayColl_BOT_LEFT:
                *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY + EPSILON;
                *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX + EPSILON;
        return 1;

        case slayColl_BOT_RIGHT:
            *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY + EPSILON;
            *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX + EPSILON;
        return 1;

        default:
        return 0;
    }
}

uint8 slayResolveCollisionLayer(array CollisionLayer)
{
    for (uint64 i = 0; i < CollisionLayer->Length; i++)
    {
        for (uint64 j = 0; j < CollisionLayer->Length; j++)
        {
            if (CollisionLayer->Values[i] != CollisionLayer->Values[j])
            {
                slayResolveCollision(CollisionLayer->Values[i], CollisionLayer->Values[j]);
            }
        }
    }

    for (uint64 i = CollisionLayer->Length - 1; 0 <= i; i--)
    {
        for (uint64 j = CollisionLayer->Length - 1; 0 <= j; j--)
        {
            if (CollisionLayer->Values[i] != CollisionLayer->Values[j])
            {
                slayResolveCollisionOrder(CollisionLayer->Values[j], CollisionLayer->Values[i]);
            }
        }
    }

    return 0;
}

uint8 slayRenderHitbox(slayEngine* Engine, slayHitbox* Hitbox)
{
    slayRenderColor(Engine, *Hitbox->ObjectX + Hitbox->UpperLeftX, *Hitbox->ObjectY+ Hitbox->UpperLeftY, Hitbox->LowerRightX - Hitbox->UpperLeftX, Hitbox->LowerRightY - Hitbox->UpperLeftY, 255, 0, 0, 128);

    return 0;
}

uint8 slayRenderHitboxCamera(slayEngine* Engine, slayHitbox* Hitbox, double Distance)
{
    slayRenderColorCamera(Engine, *Hitbox->ObjectX + Hitbox->UpperLeftX, *Hitbox->ObjectY+ Hitbox->UpperLeftY, Hitbox->LowerRightX - Hitbox->UpperLeftX, Hitbox->LowerRightY - Hitbox->UpperLeftY, Distance, 255, 0, 0, 128);

    return 0;
}