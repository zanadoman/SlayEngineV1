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

logic slayVectorRayCast(double SourceX, double SourceY, double TargetX, double TargetY, uint16 Size, double Precision, array OverlapLayer)
{
    double result;

    double RayAngle;
    double RayLength;
    slayCollision overlap;
    slayOverlapbox* RayOverlapbox;

    slayVectorAngle(SourceX, SourceY, TargetX, TargetY, &RayAngle);
    slayVectorLength(SourceX, SourceY, TargetX, TargetY, &RayLength);
    RayOverlapbox = slayNewOverlapbox(NULL, 0, &SourceX, &SourceY, -(Size >> 2), -(Size >> 2), (Size >> 2), (Size >> 2));

    overlap = slayColl_NONE;
    for (uint64 i = 0; i < OverlapLayer->Length; i++)
    {
        if (OverlapLayer->Values[i] != RayOverlapbox)
        {
            overlap |= slayGetOverlapState(RayOverlapbox, OverlapLayer->Values[i]);
        }
    }

    while (overlap == slayColl_NONE)
    {
        slayVectorTranslate(SourceX, SourceY, &SourceX, &SourceY, 3, RayAngle);
        RayLength -= 3;

        if (RayLength <= 0)
        {
            free(RayOverlapbox);
            return true;
        }

        for (uint64 i = 0; i < OverlapLayer->Length; i++)
        {
            if (OverlapLayer->Values[i] != RayOverlapbox)
            {
                overlap |= slayGetOverlapState(RayOverlapbox, OverlapLayer->Values[i]);
            }
        }
    }
    free(RayOverlapbox);

    return false;
}