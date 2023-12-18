#include "NeoTypes.h"

array arrNew(uint64 Length)
{
    array Array;

    Array = (array)malloc(sizeof(array));
    if (Array == NULL)
    {
        return NULL;
    }
    Array->Values = (void**)calloc(Length, sizeof(void*));
    if (Length != 0 && Array->Values == NULL)
    {
        free(Array);
        return NULL;
    }
    Array->Length = Length;

    return Array;
}

uint8 arrInit(array Array, uint64 Length, void* Values, ...)
{
    va_list ValuesArgs;

    free(Array->Values);
    Array->Values = (void**)malloc(sizeof(void*) * Length);
    if (Array->Values == NULL)
    {
        Array->Length = 0;
        return 1;
    }
    Array->Length = Length;

    va_start(ValuesArgs, Values);
    Array->Values[0] = Values;
    for (uint64 i = 1; i < Length; i++)
    {
        Array->Values[i] = va_arg(ValuesArgs, void*);
    }
    va_end(ValuesArgs);

    return 0;
}

uint8 arrInsert(array Array, uint64 Index, void* Value)
{
    Array->Values = (void**)realloc(Array->Values, sizeof(void*) * (Array->Length + 1));
    if (Array->Values == NULL)
    {
        Array->Length = 0;
        return 1;
    }
    Array->Length++;

    for (uint64 i = Array->Length - 1; i > Index; i--)
    {
        Array->Values[i] = Array->Values[i - 1];
    }
    Array->Values[Index] = Value;

    return 0;
}

uint8 arrRemove(array Array, uint64 Index)
{
    for (uint64 i = Index; i < Array->Length - 1; i++)
    {
        Array->Values[i] = Array->Values[i + 1];
    }

    Array->Length--;
    Array->Values = (void**)realloc(Array->Values, sizeof(void*) * Array->Length);
    if (Array->Length != 0 && Array->Values == NULL)
    {
        Array->Length = 0;
        return 1;
    }

    return 0;
}

uint8 arrPurge(array Array)
{
    if (Array == NULL)
    {
        return 0;
    }

    free(Array->Values);
    free(Array);

    return 0;
}