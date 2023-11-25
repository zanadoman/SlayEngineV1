#include "game.h"

platform* newPlatform(double X, double Y, uint16 Width, uint16 Height, uint8 R, uint8 G, uint8 B)
{
    platform* result;

    result = malloc(sizeof(platform));

    result->X = X;
    result->Y = Y;

    result->Width = Width;
    result->Height = Height;

    result->ColorR = R;
    result->ColorG = G;
    result->ColorB = B;

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height);

    return result;
}