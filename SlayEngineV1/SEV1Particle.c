#include "SlayEngineV1.h"

slayParticleBatch* newParticleBatch(uint64 Count, uint16 MinWidth, uint16 MaxWidth, uint16 MinHeight, uint16 MaxHeight, double MinSpeed, double MaxSpeed, double MinAngle, double MaxAngle, uint64 MinLifeTime, uint64 MaxLifeTime, slayTexture* Texture, uint8 MinColorR, uint8 MaxColorR, uint8 MinColorG, uint8 MaxColorG, uint8 MinColorB, uint8 MaxColorB, uint8 MinAlpha, uint8 MaxAlpha)
{
    slayParticleBatch* result;

    result = malloc(sizeof(slayParticleBatch));

    result->Particles = malloc(sizeof(slayParticle*) * Count);
    for (uint64 i = 0; i < Count; i++)
    {
        result->Particles[i] = NULL;
    }
    result->Count = Count;

    result->MinWidth = MinWidth;
    result->MaxWidth = MaxWidth;
    result->MinHeight = MinHeight;
    result->MaxHeight = MaxHeight;

    result->MinSpeed = MinSpeed;
    result->MaxSpeed = MaxSpeed;

    result->MaxAngle = MaxAngle;
    result->MinAngle = MinAngle;

    result->MinLifeTime = MinLifeTime;
    result->MaxLifeTime = MaxLifeTime;

    result->Texture = Texture;

    result->MinColorR = MinColorR;
    result->MaxColorR = MaxColorR;
    result->MinColorG = MinColorG;
    result->MaxColorG = MaxColorG;
    result->MinColorB = MinColorB;
    result->MaxColorB = MaxColorB;

    result->MinAlpha = MinAlpha;
    result->MaxAlpha = MaxAlpha;

    return result;
}

slayParticle* newParticle(slayParticleBatch* ParticleBatch)
{
    slayParticle* result;

    result = malloc(sizeof(slayParticle));

    result->Width = slayRandom(ParticleBatch->MinWidth, ParticleBatch->MaxWidth, 1);
    result->Height = slayRandom(ParticleBatch->MinHeight, ParticleBatch->MaxHeight, 2);

    result->Speed = slayRandom(ParticleBatch->MinSpeed, ParticleBatch->MaxSpeed, 3);
    result->Angle = slayRandom(ParticleBatch->MinAngle, ParticleBatch->MaxAngle, 4);

    result->LifeTime = slayRandom(ParticleBatch->MinLifeTime, ParticleBatch->MaxLifeTime, 5);

    if (ParticleBatch->Texture == NULL)
    {
        result->ColorR = slayRandom(ParticleBatch->MinColorR, ParticleBatch->MaxColorR, 6);
        result->ColorG = slayRandom(ParticleBatch->MinColorG, ParticleBatch->MaxColorG, 7);
        result->ColorB = slayRandom(ParticleBatch->MinColorB, ParticleBatch->MaxColorB, 8);
    }
    else
    {
        result->ColorR = 0;
        result->ColorG = 0;
        result->ColorB = 0;
    }

    result->Alpha = slayRandom(ParticleBatch->MinAlpha, ParticleBatch->MaxAlpha, 9);

    return result;
}

uint8 slayUpdateParticleBatch(slayEngine* Engine, slayParticleBatch* ParticleBatch)
{
    for (uint64 i = 0; i < ParticleBatch->Count; i++)
    {
        if (ParticleBatch->Particles[i] != NULL)
        {
            ParticleBatch->Particles[i]->LifeTime -= Engine->DeltaTime;
            if (ParticleBatch->Particles[i]->LifeTime <= 0)
            {
                free(ParticleBatch->Particles[i]);
                ParticleBatch->Particles[i] = NULL;
                break;
            }

            slayVectorTranslate(ParticleBatch->Particles[i]->X, ParticleBatch->Particles[i]->Y, &ParticleBatch->Particles[i]->X, &ParticleBatch->Particles[i]->Y, ParticleBatch->Particles[i]->Speed * Engine->DeltaTime, ParticleBatch->Particles[i]->Angle);
        }

        if (ParticleBatch->Particles[i] == NULL)
        {
            ParticleBatch->Particles[i] = newParticle(ParticleBatch);
        }
    }

    return 0;
}

uint8 slayRenderParticleBatch(slayEngine* Engine, slayParticleBatch* ParticleBatch)
{
    //ADD DISTANCE TO EACH PARTICLE (3D batching)
    //RENDER BY CAMERA OPTION

    return 0;
}

uint8 slayDestroyParticleBatch(slayParticleBatch* ParticleBatch)
{
    for (uint64 i = 0; i < ParticleBatch->Count; i++)
    {
        free(ParticleBatch->Particles[i]);
    }
    free(ParticleBatch);

    return 0;
}