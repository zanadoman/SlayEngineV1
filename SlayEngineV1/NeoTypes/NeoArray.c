#include "NeoTypes.h"

array arrNew(uint64 Length)
{
    array Array;

    Array = malloc(sizeof(array));
    if (Array == NULL)
    {
        return NULL;
    }
    Array->Values = calloc(Length, sizeof(void*));
    Array->Length = Length;

    return Array;
}

uint16 arrInit(array Array, uint64 Length, void* Values, ...)
{
    free(Array->Values);
    Array->Values = NULL;

    va_list ValuesArgs;

    Array->Values = malloc(sizeof(void*) * Length);
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

uint16 arrInsert(array Array, uint64 Index, void* Value)
{
    Array->Values = realloc(Array->Values, sizeof(void*) * (Array->Length + 1));
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

uint16 arrRemove(array Array, uint64 Index)
{
    for (uint64 i = Index; i < Array->Length - 1; i++)
    {
        Array->Values[i] = Array->Values[i + 1];
    }

    Array->Values = realloc(Array->Values, sizeof(void*) * (Array->Length - 1));
    Array->Length--;

    return 0;
}

uint16 arrPurge(array Array)
{
    free(Array->Values);
    Array->Values = NULL;
    free(Array);
    Array = NULL;

    return 0;
}