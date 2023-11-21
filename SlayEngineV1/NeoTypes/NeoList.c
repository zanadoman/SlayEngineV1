#include "NeoTypes.h"

uint16 listCacheInit(array Array, uint64 Length, listNode First, listNode Last);
uint16 listCacheInit(array Array, uint64 Length, listNode First, listNode Last)
{
    free(Array->Values);

    Array->Values = malloc(sizeof(void*) * Length);
    Array->Length = Length;
    
    Array->Values[0] = First;
    Array->Values[Array->Length - 1] = Last;
    
    return 0;
}

list listNew()
{
    list result;

    result = malloc(sizeof(list));
    result->List = arrNew(0);
    result->Length = 0;
    result->Cache = false;

    return result;
}

uint16 listAppend(list List, void* Value)
{
    if (List->List->Length == 0)
    {
        listCacheInit(List->List, 2, NULL, NULL);

        List->List->Values[0] = malloc(sizeof(listNode));
        ((listNode)List->List->Values[0])->Value = Value;
        ((listNode)List->List->Values[0])->Next = NULL;

        List->List->Values[1] = List->List->Values[0];
        List->Length++;
        List->Cache = true;

        return 0;
    }

    ((listNode)List->List->Values[List->List->Length - 1])->Next = malloc(sizeof(listNode));
    ((listNode)List->List->Values[List->List->Length - 1])->Next->Value = Value;
    ((listNode)List->List->Values[List->List->Length - 1])->Next->Next = NULL;

    List->List->Values[List->List->Length - 1] = ((listNode)List->List->Values[List->List->Length - 1])->Next;
    List->Length++;
    List->Cache = false;

    return 0;
}

listNode listGet(list List, uint64 Index)
{
    listNode result;

    uint64 CacheCoverage, CacheSection;

    if (List->Cache)
    {
        CacheCoverage = List->Length / (List->List->Length - 1);
        CacheSection = Index / CacheCoverage;

        result = List->List->Values[CacheSection];
        for (uint64 i = 0; i < Index - CacheSection * CacheCoverage; i++)
        {
            result = result->Next;
        }
    }
    else
    {
        result = List->List->Values[0];
        for (uint64 i = 0; i < Index; i++)
        {
            result = result->Next;
        }
    }

    return result;
}

uint16 listCache(list List, uint64 Cache)
{
    listNode node;
    uint64 CacheCoverage;

    if (Cache == 0 || List->Length < 3)
    {
        return 1;
    }

    if (Cache > List->Length / 3)
    {
        Cache = List->Length / 3;
    }

    listCacheInit(List->List, Cache + 1, List->List->Values[0], List->List->Values[List->List->Length - 1]);

    CacheCoverage = List->Length / Cache;
    node = ((listNode)List->List->Values[0])->Next;
    for (uint64 i = 1; i < List->Length - 1; i++)
    {
        if (i % CacheCoverage == 0)
        {
            List->List->Values[i / CacheCoverage] = node;
        }
        node = node->Next;
    }
    List->Cache = true;

    return 0;
}