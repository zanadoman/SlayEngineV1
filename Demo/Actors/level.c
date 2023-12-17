#include "../game.h"

platform* newPlatform(double X, double Y, uint16 Width, uint16 Height)
{
    platform* result;

    result = malloc(sizeof(platform));

    result->X = X;
    result->Y = Y;

    result->Width = Width;
    result->Height = Height;

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height, -1, -1, 0, 0, 0, 0);

    return result;
}

crate* newCrate(slayEngine* Engine, double X, double Y, double MinX, double MaxX, double MinY, double MaxY, uint16 Width, uint16 Height)
{
    crate* result;

    result = malloc(sizeof(crate));

    result->X = X;
    result->Y = Y;

    result->MinX = MinX;
    result->MaxX = MaxX;
    result->MinY = MinY;
    result->MaxY = MaxY;

    result->Width = Width;
    result->Height = Height;

    result->Texture = slayLoadTexture(Engine, "assets/level/crate.png");

    result->Hitbox = slayNewHitbox(&result->X, &result->Y, 0, 0, result->Width, result->Height, 1, 1, MinX, MinY, MaxX, MaxY);

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
    slayUnloadTexture(Crate->Texture);
    free(Crate->Hitbox);
    free(Crate);

    return 0;
}