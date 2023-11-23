#include "NeoTypes.h"

list listNew() //APPROVED
{
    list result;

    result = malloc(sizeof(list));
    result->Cache = malloc(sizeof(listCache_t));
    result->Cache->Nodes = NULL;
    result->Cache->Size = 0;
    result->Cache->Coverage = 0;
    result->Length = 0;

    return result;
}

uint16 listAppend(list List, void* Value) //APPROVED
{
    listNode first;
    listNode last;

    if (List->Length == 0)
    {
        first = malloc(sizeof(listNode));
        first->Value = Value;
        first->Next = NULL;

        last = first;
    }
    else
    {
        List->Cache->Nodes[List->Cache->Size - 1]->Next = malloc(sizeof(listNode));
        List->Cache->Nodes[List->Cache->Size - 1]->Next->Value = Value;
        List->Cache->Nodes[List->Cache->Size - 1]->Next->Next = NULL;

        List->Cache->Nodes[List->Cache->Size - 1] = List->Cache->Nodes[List->Cache->Size - 1]->Next;

        first = List->Cache->Nodes[0];
        last = List->Cache->Nodes[List->Cache->Size - 1];
    }

    List->Length++;

    free(List->Cache->Nodes);
    List->Cache->Nodes = malloc(sizeof(listNode) * 2);
    List->Cache->Nodes[0] = first;
    List->Cache->Nodes[1] = last;

    List->Cache->Size = 2;
    List->Cache->Coverage = List->Length;

    return 0;
}

listNode listGet(list List, uint64 Index) //APPROVED
{
    listNode result;

    uint64 CacheSection;

    CacheSection = Index / List->Cache->Coverage;

    result = List->Cache->Nodes[CacheSection];
    for (int i = 0; i < Index - CacheSection * List->Cache->Coverage; i++)
    {
        result = result->Next;
    }

    return result;
}

uint16 listCache(list List, uint64 CacheCoverage) //APPROVED
{
    listNode first;
    listNode last;

    //Set the cache coverage
    if (CacheCoverage < 1)
    {
        CacheCoverage = 1;
    }
    else if (List->Length < CacheCoverage)
    {
        CacheCoverage = List->Length;
    }
    List->Cache->Coverage = CacheCoverage;

    //Save the first and last node
    first = List->Cache->Nodes[0];
    last = List->Cache->Nodes[List->Cache->Size - 1];

    //Calculate the size of the cache
    List->Cache->Size = 1;
    for (uint64 i = 0; i < List->Length; i += List->Cache->Coverage)
    {
        List->Cache->Size++;
    }

    //Initialize the cache
    free(List->Cache->Nodes);
    List->Cache->Nodes = malloc(sizeof(listNode) * List->Cache->Size);
    List->Cache->Nodes[0] = first;
    List->Cache->Nodes[List->Cache->Size - 1] = last;

    //Fill the cache
    for (uint64 i = 0; i < List->Length; i++)
    {
        if (i % List->Cache->Coverage == 0)
        {
            List->Cache->Nodes[i / List->Cache->Coverage] = first;
        }
        
        first = first->Next;
    }

    return 0;
}