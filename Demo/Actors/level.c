#include "../game.h"

platform* newPlatform(double X, double Y, uint16 Width, uint16 Height)
{
    platform* result;

    result = malloc(sizeof(platform));

    result->X = X;
    result->Y = Y;

    result->Width = Width;
    result->Height = Height;

    result->Hitbox = slayNewHitbox(result, actPLATFORM, &result->X, &result->Y, &result->X, &result->Y, 0, 0, result->Width, result->Height, 100, 100, NULL, NULL, NULL, NULL);

    return result;
}

uint8 destroyPlatforms(array Platforms)
{
    for (uint16 i = 0; i < Platforms->Length; i++)
    {
        free(((platform*)Platforms->Values[i])->Hitbox);
    }
    for (uint16 i = 0; i < Platforms->Length; i++)
    {
        free(Platforms->Values[i]);
    }
    arrPurge(Platforms);

    return 0;
}