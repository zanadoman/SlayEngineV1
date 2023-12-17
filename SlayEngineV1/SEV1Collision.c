#include "SlayEngineV1.h"

slayHitbox* slayNewHitbox(double* ObjectX, double* ObjectY, sint32 UpperLeftX, sint32 UpperLeftY, sint32 LowerRightX, sint32 LowerRightY)
{
    slayHitbox* result;

    result = malloc(sizeof(slayHitbox));
    if (result == NULL)
    {
        printf("ERROR Unable to allocate memory for HITBOX\n");
        exit(1);
    }

    result->ObjectX = ObjectX;
    result->ObjectY = ObjectY;
    result->UpperLeftX = UpperLeftX;
    result->UpperLeftY = UpperLeftY;
    result->LowerRightX = LowerRightX;
    result->LowerRightY = LowerRightY;

    return result;
}

slayColls slayCollision(slayHitbox* Hitbox1, slayHitbox* Hitbox2)
{
    slayColls result;

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

    result = slayCollNONE;

    if (Hitbox1LowerRightX < Hitbox2UpperLeftX || Hitbox2LowerRightX < Hitbox1UpperLeftX || Hitbox1LowerRightY < Hitbox2UpperLeftY || Hitbox2LowerRightY < Hitbox1UpperLeftY)
    {
        return result;
    }

    if (((Hitbox1UpperLeftX <= Hitbox2LowerRightX && Hitbox2LowerRightX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2LowerRightY && Hitbox2LowerRightY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1UpperLeftX && Hitbox1UpperLeftX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1UpperLeftY && Hitbox1UpperLeftY <= Hitbox2LowerRightY)))
    {
        result = result | slayCollTOPLEFT;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2UpperLeftX && Hitbox2UpperLeftX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2LowerRightY && Hitbox2LowerRightY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1LowerRightX && Hitbox1LowerRightX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1UpperLeftY && Hitbox1UpperLeftY <= Hitbox2LowerRightY)))
    {
        result = result | slayCollTOPRIGHT;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2LowerRightX && Hitbox2LowerRightX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2UpperLeftY && Hitbox2UpperLeftY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1UpperLeftX && Hitbox1UpperLeftX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1LowerRightY && Hitbox1LowerRightY <= Hitbox2LowerRightY)))
    {
        result = result | slayCollBOTTOMLEFT;
    }
    if (((Hitbox1UpperLeftX <= Hitbox2UpperLeftX && Hitbox2UpperLeftX <= Hitbox1LowerRightX) && (Hitbox1UpperLeftY <= Hitbox2UpperLeftY && Hitbox2UpperLeftY <= Hitbox1LowerRightY)) || ((Hitbox2UpperLeftX <= Hitbox1LowerRightX && Hitbox1LowerRightX <= Hitbox2LowerRightX) && (Hitbox2UpperLeftY <= Hitbox1LowerRightY && Hitbox1LowerRightY <= Hitbox2LowerRightY)))
    {
        result = result | slayCollBOTTOMRIGHT;
    }

    return result;
}

uint8 slayApplyCollision(slayColls Collision, double Hitbox1PrevObjectX, double Hitbox1PrevObjectY, slayHitbox* Hitbox1, double Hitbox1Force, slayHitbox* Hitbox2, double Hitbox2Resistance, double Hitbox2MinX, double Hitbox2MaxX, double Hitbox2MinY, double Hitbox2MaxY)
{
    double ratioCache;

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

    if (Collision == slayCollNONE)
    {
        return 0;
    }

    Hitbox1PrevUpperLeftX = Hitbox1->UpperLeftX + Hitbox1PrevObjectX;
    Hitbox1PrevUpperLeftY = Hitbox1->UpperLeftY + Hitbox1PrevObjectY;
    Hitbox1PrevLowerRightX = Hitbox1->LowerRightX + Hitbox1PrevObjectX;
    Hitbox1PrevLowerRightY = Hitbox1->LowerRightY + Hitbox1PrevObjectY;

    Hitbox1UpperLeftX = Hitbox1->UpperLeftX + *Hitbox1->ObjectX;
    Hitbox1UpperLeftY = Hitbox1->UpperLeftY + *Hitbox1->ObjectY;
    Hitbox1LowerRightX = Hitbox1->LowerRightX + *Hitbox1->ObjectX;
    Hitbox1LowerRightY = Hitbox1->LowerRightY + *Hitbox1->ObjectY;

    Hitbox2UpperLeftX = Hitbox2->UpperLeftX + *Hitbox2->ObjectX;
    Hitbox2UpperLeftY = Hitbox2->UpperLeftY + *Hitbox2->ObjectY;
    Hitbox2LowerRightX = Hitbox2->LowerRightX + *Hitbox2->ObjectX;
    Hitbox2LowerRightY = Hitbox2->LowerRightY + *Hitbox2->ObjectY;

    if (Hitbox1Force <= Hitbox2Resistance)
    {
        switch(Collision)
        {
            case slayCollLEFT:
                *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX;
                return 0;
            case slayCollRIGHT:
                *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX;
                return 0;
            case slayCollTOP:
                *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY;
                return 0;
            case slayCollBOTTOM:
                *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY;
                return 0;

            case slayCollTOPLEFT:
                if (Hitbox1PrevUpperLeftX < Hitbox2LowerRightX)
                {
                    *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY;
                }
                else if (Hitbox1PrevUpperLeftY < Hitbox2LowerRightY)
                {
                    *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX;
                }
                else
                {
                    *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY;
                    *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX;
                }
                return 0;
            
            case slayCollTOPRIGHT:
                if (Hitbox2UpperLeftX < Hitbox1PrevLowerRightX)
                {
                    *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY;
                }
                else if (Hitbox1PrevUpperLeftY < Hitbox2LowerRightY)
                {
                    *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX;
                }
                else
                {
                    *Hitbox1->ObjectY += Hitbox2LowerRightY - Hitbox1UpperLeftY;
                    *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX;
                }
                return 0;
            case slayCollBOTTOMLEFT:
                if (Hitbox1PrevUpperLeftX < Hitbox2LowerRightX)
                {
                    *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY;
                }
                else if (Hitbox2UpperLeftY < Hitbox1PrevLowerRightY)
                {
                    *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX;
                }
                else
                {
                    *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY;
                    *Hitbox1->ObjectX += Hitbox2LowerRightX - Hitbox1UpperLeftX;
                }
                return 0;
            case slayCollBOTTOMRIGHT:
                if (Hitbox2UpperLeftX < Hitbox1PrevLowerRightX)
                {
                    *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY;
                }
                else if (Hitbox2UpperLeftY < Hitbox1PrevLowerRightY)
                {
                    *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX;
                }
                else
                {
                    *Hitbox1->ObjectY -= Hitbox1LowerRightY - Hitbox2UpperLeftY;
                    *Hitbox1->ObjectX -= Hitbox1LowerRightX - Hitbox2UpperLeftX;
                }
                return 0;
        }
    }
    else
    {
        ratioCache = Hitbox2Resistance / Hitbox1Force;

        switch(Collision)
        {
            case slayCollLEFT:
                *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratioCache;
                *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratioCache);
                return 0;
            case slayCollRIGHT:
                *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratioCache;
                *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratioCache);
                return 0;
            case slayCollTOP:
                *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratioCache;
                *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratioCache);
                return 0;
            case slayCollBOTTOM:
                *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratioCache;
                *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratioCache);
                return 0;

            case slayCollTOPLEFT:
                if (Hitbox1PrevUpperLeftX < Hitbox2LowerRightX)
                {
                    *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratioCache;
                    *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratioCache);
                }
                else
                {
                    *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratioCache;
                    *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratioCache);
                }
                return 0;
            
            case slayCollTOPRIGHT:
                if (Hitbox2UpperLeftX < Hitbox1PrevLowerRightX)
                {
                    *Hitbox1->ObjectY += (Hitbox2LowerRightY - Hitbox1UpperLeftY) * ratioCache;
                    *Hitbox2->ObjectY -= (Hitbox2LowerRightY - Hitbox1UpperLeftY) * (1 - ratioCache);
                }
                else
                {
                    *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratioCache;
                    *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratioCache);
                }
                return 0;
            case slayCollBOTTOMLEFT:
                if (Hitbox1PrevUpperLeftX < Hitbox2LowerRightX)
                {
                    *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratioCache;
                    *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratioCache);
                }
                else
                {
                    *Hitbox1->ObjectX += (Hitbox2LowerRightX - Hitbox1UpperLeftX) * ratioCache;
                    *Hitbox2->ObjectX -= (Hitbox2LowerRightX - Hitbox1UpperLeftX) * (1 - ratioCache);
                }
                return 0;
            case slayCollBOTTOMRIGHT:
                if (Hitbox2UpperLeftX < Hitbox1PrevLowerRightX)
                {
                    *Hitbox1->ObjectY -= (Hitbox1LowerRightY - Hitbox2UpperLeftY) * ratioCache;
                    *Hitbox2->ObjectY += (Hitbox1LowerRightY - Hitbox2UpperLeftY) * (1 - ratioCache);
                }
                else
                {
                    *Hitbox1->ObjectX -= (Hitbox1LowerRightX - Hitbox2UpperLeftX) * ratioCache;
                    *Hitbox2->ObjectX += (Hitbox1LowerRightX - Hitbox2UpperLeftX) * (1 - ratioCache);
                }
                return 0;
        }
    }

    return 0;
}