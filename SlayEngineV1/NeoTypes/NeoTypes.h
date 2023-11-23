#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

//________________NeoTypes.h_______________

#define true 1
#define false 0
typedef char boolean;
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;
typedef unsigned long uint64;
typedef signed long sint64;

//________________NeoCast.c________________

uint64 asInt(double Value);
double asDouble(sint64 Value);

//________________NeoArray.c_______________

typedef struct
{
    void* *Values;
    uint64 Length;
}* array;


array arrNew(uint64 Length);
uint16 arrInit(array Array, uint64 Length, void* Values, ...);

uint16 arrInsert(array Array, uint64 Index, void* Value);

uint16 arrRemove(array Array, uint64 Index);

//_______________NeoString.c_______________

typedef struct
{
    char* String;
    uint64 Lenght;
}* string;


uint64 strLength(char* Characters);

string strNew();
uint16 strInit(string String, char* Characters);

uint16 strAppend(string String, char Character);
uint16 strConcat(string String, uint64 Count, char* Characters, ...);

uint16 strRead(string String);
uint16 strSplit(array Array, string String, char Character);
boolean strCompare(char* Characters1, char* Characters2);

//________________NeoList.c________________

typedef struct listCacheStruct* listCache_t;
typedef struct listNodeStruct* listNode;
typedef struct
{
    listCache_t Cache;
    uint64 Length;
}* list;
struct listCacheStruct
{
    listNode* Nodes;
    uint64 Size;
    uint64 Coverage;
};
struct listNodeStruct
{
    listNode Next;
    void* Value;
};


list listNew();
uint16 listAppend(list List, void* Value);
listNode listGet(list List, uint64 Index);
uint16 listCache(list List, uint64 CacheCoverage);
//Insert
//Remove
//Purge

//_______________NeoConvert.c______________

uint64 STRtoUINT(char* Characters, boolean* Success);
uint16 UINTtoSTR(uint64 Number, string String);

sint64 STRtoSINT(char* Characters, boolean* Success);
uint16 SINTtoSTR(sint64 Number, string String);

double STRtoDOUBLE(char* Characters, boolean* Success);
uint16 DOUBLEtoSTR(double Number, string String);