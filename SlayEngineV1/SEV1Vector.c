#include "SlayEngineV1.h"

uint8 slayVectorLength(double X1, double Y1, double X2, double Y2, double* Length)
{
    *Length = sqrt(pow((X2 - X1), 2) + pow((Y2 - Y1), 2));

    return 0;
}

uint8 slayVectorTranslate(double X1, double Y1, double* X2, double* Y2, double Length, double Angle)
{
    double cache;

    cache = Angle * PI / 180;
    *X2 = X1 + Length * cos(cache);
    *Y2 = Y1 + Length * sin(cache);

    return 0;
}

uint8 slayVectorAngle(double X1, double Y1, double X2, double Y2, double* Angle)
{
    double length;
    double angle;

    slayVectorLength(X1, Y1, X2, Y2, &length);

    angle = acos((X2 - X1) / length) * 180 / PI;
    if (Y1 > Y2)
    {
        *Angle = 360 - angle;
    }
    else
    {
        *Angle = angle;
    }

    return 0;
}

logic slayVectorRayCastCoordinate(double SourceX, double SourceY, double TargetX, double TargetY, uint16 Size, double Precision, array OverlapLayer)
{
    double RayAngle;
    double RayLength;
    slayOverlapbox* RayOverlapbox;

    if (SourceX == TargetX && SourceY == TargetY)
    {
        return true;
    }

    slayVectorAngle(SourceX, SourceY, TargetX, TargetY, &RayAngle);
    slayVectorLength(SourceX, SourceY, TargetX, TargetY, &RayLength);
    RayOverlapbox = slayNewOverlapbox(NULL, 0, &SourceX, &SourceY, -(Size >> 2), -(Size >> 2), (Size >> 2), (Size >> 2));

    while (0 < RayLength)
    {
        for (uint64 i = 0; i < OverlapLayer->Length; i++)
        {
            if (slayCheckOverlap(RayOverlapbox, OverlapLayer->Values[i]))
            {
                free(RayOverlapbox);
                return false;
            }
        }

        slayVectorTranslate(SourceX, SourceY, &SourceX, &SourceY, Precision, RayAngle);
        RayLength -= Precision;
    }
    free(RayOverlapbox);

    return true;
}

logic slayVectorRayCastOverlapbox(double SourceX, double SourceY, slayOverlapbox* Target, uint16 Size, double Precision, array OverlapLayer)
{
    double TargetX, TargetY;
    double RayAngle;
    double RayLength;
    slayOverlapbox* RayOverlapbox;

    TargetX = *Target->ObjectX + (Target->UpperLeftX + Target->LowerRightX) / 2.0;
    TargetY = *Target->ObjectY + (Target->UpperLeftY + Target->LowerRightY) / 2.0;

    if (SourceX == TargetX && SourceY == TargetY)
    {
        return true;
    }

    slayVectorAngle(SourceX, SourceY, TargetX, TargetY, &RayAngle);
    slayVectorLength(SourceX, SourceY, TargetX, TargetY, &RayLength);
    RayOverlapbox = slayNewOverlapbox(NULL, 0, &SourceX, &SourceY, -(Size >> 2), -(Size >> 2), (Size >> 2), (Size >> 2));

    while (0 < RayLength)
    {
        for (uint64 i = 0; i < OverlapLayer->Length; i++)
        {
            if (OverlapLayer->Values[i] != Target && slayCheckOverlap(RayOverlapbox, OverlapLayer->Values[i]))
            {
                free(RayOverlapbox);
                return false;
            }
        }

        slayVectorTranslate(SourceX, SourceY, &SourceX, &SourceY, Precision, RayAngle);
        RayLength -= Precision;
    }
    free(RayOverlapbox);

    return true;
}