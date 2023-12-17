#include "../game.h"

platform* newPlatform(double X, double Y, uint16 Width, uint16 Height)
{
    platform* result;

    result = malloc(sizeof(platform));

    result->X = X;
    result->Y = Y;

    result->Width = Width;
    result->Height = Height;

    result->Hitbox = slayNewHitbox(actPLATFORM, &result->X, &result->Y, NULL, NULL, 0, 0, result->Width, result->Height, -1, -1, NULL, NULL, NULL, NULL);

    return result;
}

crate* newCrate(slayEngine* Engine, uint16 Width, uint16 Height)
{
    crate* result;

    result = malloc(sizeof(crate));

    result->X = 0;
    result->Y = 0;
    result->PrevX = 0;
    result->PrevY = 0;

    result->MinX = 0;
    result->MinY = 0;
    result->MaxX = 0;
    result->MaxY = 0;

    result->Width = Width;
    result->Height = Height;

    result->Hitbox = slayNewHitbox(actCRATE, &result->X, &result->Y, &result->PrevX, &result->PrevY, 0, 0, result->Width, result->Height, 1, 1, &result->MinX, &result->MinY, &result->MaxX, &result->MaxY);

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

uint8 destroyCrate(crate* Crate)
{
    free(Crate->Hitbox);
    free(Crate);

    return 0;
}