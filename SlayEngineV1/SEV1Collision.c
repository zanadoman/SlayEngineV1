#include "SlayEngineV1.h"

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

slayCollision slayGetCollisionState(slayHitbox* Hitbox1, slayHitbox* Hitbox2)
{
    slayCollision result;

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

    result = slayColl_NONE;

    if (Hitbox1LowerRightX < Hitbox2UpperLeftX || Hitbox2LowerRightX < Hitbox1UpperLeftX || Hitbox1LowerRightY < Hitbox2UpperLeftY || Hitbox2LowerRightY < Hitbox1UpperLeftY)
    {
        return result;
    }

    if (((Hitbox1UpperLeftX <= Hitbox2LowerRightX && Hitbox2LowerRightX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2LowerRightY && Hitbox2LowerRightY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1UpperLeftX && Hitbox1UpperLeftX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1UpperLeftY && Hitbox1UpperLeftY <= Hitbox2LowerRightY)))
    {
        result |= slayColl_TOP_LEFT;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2UpperLeftX && Hitbox2UpperLeftX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2LowerRightY && Hitbox2LowerRightY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1LowerRightX && Hitbox1LowerRightX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1UpperLeftY && Hitbox1UpperLeftY <= Hitbox2LowerRightY)))
    {
        result |= slayColl_TOP_RIGHT;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2LowerRightX && Hitbox2LowerRightX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2UpperLeftY && Hitbox2UpperLeftY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1UpperLeftX && Hitbox1UpperLeftX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1LowerRightY && Hitbox1LowerRightY <= Hitbox2LowerRightY)))
    {
        result |= slayColl_BOT_LEFT;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2UpperLeftX && Hitbox2UpperLeftX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2UpperLeftY && Hitbox2UpperLeftY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1LowerRightX && Hitbox1LowerRightX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1LowerRightY && Hitbox1LowerRightY <= Hitbox2LowerRightY)))
    {
        result |= slayColl_BOT_RIGHT;
    }

    return result;
}

slayCollision slayGetCollisionDirection(slayHitbox* Hitbox1, slayHitbox* Hitbox2)
{
    uint8 collision;
    slayHitbox* hitbox;
    double angle;

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

    hitbox = slayNewHitbox(NULL, 0, Hitbox1->ObjectPrevX, Hitbox1->ObjectPrevY, Hitbox1->ObjectPrevX, Hitbox1->ObjectPrevY, Hitbox1->UpperLeftX, Hitbox1->UpperLeftY, Hitbox1->LowerRightX, Hitbox1->LowerRightY, 0, 0, 0, 0, 0, 0);
    collision = slayGetCollisionState(hitbox, Hitbox2);
    free(hitbox);
    if (collision != slayColl_NONE)
    {
        return slayColl_ERROR;
    }

    collision = slayGetCollisionState(Hitbox1, Hitbox2);
    if (collision == slayColl_NONE)
    {
        return slayColl_NONE;
    }

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

    switch (collision)
    {
        case slayColl_TOP_LEFT | slayColl_TOP_RIGHT:
            return slayColl_TOP;

        case slayColl_BOT_LEFT | slayColl_BOT_RIGHT:
            return slayColl_BOTTOM;

        case slayColl_TOP_LEFT | slayColl_BOT_LEFT:
            return slayColl_LEFT;

        case slayColl_TOP_RIGHT | slayColl_BOT_RIGHT:
            return slayColl_RIGHT;

        case slayColl_TOP_LEFT:
            if (Hitbox1PrevUpperLeftX < Hitbox2LowerRightX)
            {
                return slayColl_TOP;
            }
            else if (Hitbox1PrevUpperLeftY < Hitbox2LowerRightY)
            {
                return slayColl_LEFT;
            }
            else
            {
                slayVectorAngle(Hitbox2LowerRightX, Hitbox2LowerRightY, Hitbox1UpperLeftX, Hitbox1UpperLeftY, &angle);

                if (angle < 225)
                {
                    return slayColl_TOP;
                }
                else if (225 < angle)
                {
                    return slayColl_LEFT;
                }
                else
                {
                    return slayColl_TOP_LEFT;
                }
            }
            
        case slayColl_TOP_RIGHT:
            if (Hitbox2UpperLeftX < Hitbox1PrevLowerRightX)
            {
                return slayColl_TOP;
            }
            else if (Hitbox1PrevUpperLeftY < Hitbox2LowerRightY)
            {
                return slayColl_RIGHT;
            }
            else
            {
                slayVectorAngle(Hitbox2UpperLeftX, Hitbox2LowerRightY, Hitbox1LowerRightX, Hitbox1UpperLeftY, &angle);

                if (315 < angle)
                {
                    return slayColl_TOP;
                }
                else if (angle < 315)
                {
                    return slayColl_RIGHT;
                }
                else
                {
                    return slayColl_TOP_RIGHT;
                }
            }

        case slayColl_BOT_LEFT:
            if (Hitbox1PrevUpperLeftX < Hitbox2LowerRightX)
            {
                return slayColl_BOTTOM;
            }
            else if (Hitbox2UpperLeftY < Hitbox1PrevLowerRightY)
            {
                return slayColl_LEFT;
            }
            else
            {
                slayVectorAngle(Hitbox2UpperLeftX, Hitbox2UpperLeftY, Hitbox1LowerRightX, Hitbox1LowerRightY, &angle);

                if (angle < 45)
                {
                    return slayColl_BOTTOM;
                }
                else if (45 < angle)
                {
                    return slayColl_LEFT;
                }
                else
                {
                    return slayColl_BOT_LEFT;
                }
            }

        case slayColl_BOT_RIGHT:
            if (Hitbox2UpperLeftX < Hitbox1PrevLowerRightX)
            {
                return slayColl_BOTTOM;
            }
            else if (Hitbox2UpperLeftY < Hitbox1PrevLowerRightY)
            {
                return slayColl_RIGHT;
            }
            else
            {
                slayVectorAngle(Hitbox2LowerRightX, Hitbox2UpperLeftY, Hitbox1UpperLeftX, Hitbox1LowerRightY, &angle);

                if (135 < angle)
                {
                    return slayColl_BOTTOM;
                }
                else if (angle < 135)
                {
                    return slayColl_RIGHT;
                }
                else
                {
                    return slayColl_BOT_RIGHT;
                }
            }
    }

    return slayColl_NONE;
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

    if (slayGetCollisionState(Hitbox1, Hitbox2) == slayColl_NONE)
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
                *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY;
            return 1;

            case slayColl_BOTTOM:
                *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY;
            return 1;

            case slayColl_LEFT:
                *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX;
            return 1;

            case slayColl_RIGHT:
                *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX;
            return 1;

            case slayColl_TOP_LEFT:
                *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY;
                *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX;
            return 1;

            case slayColl_TOP_RIGHT:
                *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY;
                *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX;
            return 1;

            case slayColl_BOT_LEFT:
                *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY;
                *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX;
            return 1;

            case slayColl_BOT_RIGHT:
                *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY;
                *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX;
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
                *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratio;
                *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratio);
            break;

            case slayColl_BOTTOM:
                *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratio;
                *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratio);
            break;

            case slayColl_LEFT:
                *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratio;
                *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratio);
            break;

            case slayColl_RIGHT:
                *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratio;
                *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratio);
            break;

            case slayColl_TOP_LEFT:
                *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratio;
                *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratio);

                *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratio;
                *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratio);
            break;

            case slayColl_TOP_RIGHT:
                *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratio;
                *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratio);

                *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratio;
                *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratio);
            break;

            case slayColl_BOT_LEFT:
                *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratio;
                *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratio);

                *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratio;
                *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratio);
            break;

            case slayColl_BOT_RIGHT:
                *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratio;
                *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratio);

                *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratio;
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

uint8 slayResolveCollisionLayer(array CollisionLayer)
{
    logic disorder;

    disorder = true;
    while (disorder)
    {
        disorder = false;
        for (uint64 i = 0; i < CollisionLayer->Length; i++)
        {
            for (uint64 j = i + 1; j < CollisionLayer->Length; j++)
            {
                if (CollisionLayer->Values[i] != CollisionLayer->Values[j])
                {
                    if (slayResolveCollision(CollisionLayer->Values[i], CollisionLayer->Values[j]) == 1)
                    {
                        disorder = true;
                    }
                }
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

/*switch (collision)
{
    case slayCollTOP:
        *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY;
    return 0;

    case slayCollBOTTOM:
        *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY;
    return 0;

    case slayCollLEFT:
        *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX;
    return 0;

    case slayCollRIGHT:
        *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX;
    return 0;
}*/

/*case slayCollTOP:
                *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratioCache;
                *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratioCache);
            break;

            case slayCollBOTTOM:
                *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratioCache;
                *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratioCache);
            break;

            case slayCollLEFT:
                *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratioCache;
                *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratioCache);
            break;

            case slayCollRIGHT:
                *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratioCache;
                *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratioCache);
            break;
*/