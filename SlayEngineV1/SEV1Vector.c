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

logic slayVectorRayCast(double SourceX, double SourceY, double TargetX, double TargetY, slayHitbox* Obstacle, uint16 Size, double Precision)
{
    double result;

    double RayAngle;
    double RayLength;
    slayHitbox* RayHitbox;

    slayVectorAngle(SourceX, SourceY, TargetX, TargetY, &RayAngle);
    slayVectorLength(SourceX, SourceY, TargetX, TargetY, &RayLength);
    RayHitbox = slayNewHitbox(&SourceX, &SourceY, -(Size >> 2), -(Size >> 2), (Size >> 2), (Size >> 2));

    while (slayCollision(RayHitbox, Obstacle) == 0)
    {
        slayVectorTranslate(SourceX, SourceY, &SourceX, &SourceY, 3, RayAngle);
        RayLength -= 3;

        if (RayLength <= 0)
        {
            free(RayHitbox);
            return true;
        }
    }
    free(RayHitbox);

    return false;
}