#include "NeoTypes.h"

list listNew()
{
    list result;

    result = malloc(sizeof(list));
    if (result == NULL)
    {
        return NULL;
    }
    result->Cache = malloc(sizeof(listCache_t));
    if (result->Cache == NULL)
    {
        free(result);
        return NULL;
    }
    result->Cache->Nodes = NULL;
    result->Cache->Size = 0;
    result->Cache->Coverage = 0;
    result->Length = 0;

    return result;
}

uint8 listInsert(list List, uint64 Index, void* Value)
{
    listNode first;
    listNode last;

    if (Index == 0)
    {
        if (List->Length == 0)
        {
            first = malloc(sizeof(listNode));
            if (first == NULL)
            {
                return 1;
            }
            first->Value = Value;
            first->Next = NULL;

            last = first;
        }
        else
        {
            first = malloc(sizeof(listNode));
            if (first == NULL)
            {
                return 1;
            }
            first->Value = Value;
            first->Next = List->Cache->Nodes[0];

            last = List->Cache->Nodes[List->Cache->Size - 1];
        }
    }
    else if (Index == List->Length)
    {
        List->Cache->Nodes[List->Cache->Size - 1]->Next = malloc(sizeof(listNode));
        if (List->Cache->Nodes[List->Cache->Size - 1]->Next == NULL)
        {
            return 1;
        }
        List->Cache->Nodes[List->Cache->Size - 1]->Next->Value = Value;
        List->Cache->Nodes[List->Cache->Size - 1]->Next->Next = NULL;

        first = List->Cache->Nodes[0];
        last = List->Cache->Nodes[List->Cache->Size - 1]->Next;
    }
    else
    {
        first = listGet(List, Index - 1);
        last = first->Next;

        first->Next = malloc(sizeof(listNode));
        if (first->Next == NULL)
        {
            first->Next = last;
            return 1;
        }
        first->Next->Value = Value;
        first->Next->Next = last;

        first = List->Cache->Nodes[0];
        last = List->Cache->Nodes[List->Cache->Size - 1];
    }

    List->Length++;

    free(List->Cache->Nodes);
    List->Cache->Nodes = malloc(sizeof(listNode) * 2);
    if (List->Cache->Nodes == NULL)
    {
        List->Cache->Size = 0;
        List->Cache->Coverage = 0;
        List->Length = 0;
        return 1;
    }
    List->Cache->Nodes[0] = first;
    List->Cache->Nodes[1] = last;

    List->Cache->Size = 2;
    List->Cache->Coverage = List->Length;

    return 0;
}

uint8 listRemove(list List, uint64 Index)
{
    listNode first;
    listNode last;

    if (Index == 0)
    {
        if (List->Length == 1)
        {
            free(List->Cache->Nodes[0]);
            free(List->Cache->Nodes);
            List->Cache->Nodes = NULL;
            List->Cache->Size = 0;
            List->Cache->Coverage = 0;
            List->Length = 0;

            return 0;
        }
        else
        {
            first = List->Cache->Nodes[0]->Next;
            last = List->Cache->Nodes[List->Cache->Size - 1];

            free(List->Cache->Nodes[0]);
        }
    }
    else if (Index == List->Length - 1)
    {
        first = List->Cache->Nodes[0];
        last = listGet(List, Index - 1);
        free(last->Next);
        last->Next = NULL;
    }
    else
    {
        first = listGet(List, Index - 1);
        last = first->Next->Next;

        free(first->Next);
        first->Next = last;

        first = List->Cache->Nodes[0];
        last = List->Cache->Nodes[List->Cache->Size - 1];
    }

    List->Length--;

    free(List->Cache->Nodes);
    List->Cache->Nodes = malloc(sizeof(listNode) * 2);
    if (List->Cache->Nodes == NULL)
    {
        List->Cache->Size = 0;
        List->Cache->Coverage = 0;
        List->Length = 0;
        return 1;
    }
    List->Cache->Nodes[0] = first;
    List->Cache->Nodes[1] = last;

    List->Cache->Size = 2;
    List->Cache->Coverage = List->Length;

    return 0;
}

listNode listGet(list List, uint64 Index)
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

uint8 listCache(list List, uint64 CacheCoverage)
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
    if (List->Cache->Nodes == NULL)
    {
        List->Cache->Size = 0;
        List->Cache->Coverage = 0;
        List->Length = 0;
        return 1;
    }
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

uint8 listPurge(list List)
{
    listNode tmp;

    tmp = List->Cache->Nodes[0];
    for (listNode i = List->Cache->Nodes[0]->Next; i != NULL; i = i->Next)
    {
        free(tmp);
        tmp = i;
    }
    free(tmp);

    free(List->Cache->Nodes);
    free(List->Cache);
    free(List);

    return 0;
}