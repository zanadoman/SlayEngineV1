#include "SlayEngineV1.h"

uint16 slayVectorLength(double X1, double Y1, double X2, double Y2, double* Length)
{
    *Length = sqrt(pow((X2 - X1), 2) + pow((Y2 - Y1), 2));

    return 0;
}

uint16 slayVectorTranslate(double X1, double Y1, double* X2, double* Y2, double Length, double Angle)
{
    *X2 = X1 + Length * cos(Angle * PI / 180);
    *Y2 = Y1 + Length * sin(Angle * PI / 180);

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