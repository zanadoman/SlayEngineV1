#include "SlayEngineV1.h"

uint16 slayVectorLength(double X1, double Y1, double X2, double Y2, double* Length)
{
    *Length = sqrt(pow((X2 - X1), 2) + pow((Y2 - Y1), 2));

    return 0;
}

uint16 slayVectorTerminal(double X1, double Y1, double* X2, double* Y2, double Length, double Angle)
{
    return 0;
}

uint16 slayVectorAngle(double X1, double Y1, double X2, double Y2, double* Angle)
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

uint16 slayVectorScalar(double X1, double Y1, double X2, double Y2, double* Scalar)
{
    *Scalar = X1 * X2 + Y1 * Y2;

    return 0;
}