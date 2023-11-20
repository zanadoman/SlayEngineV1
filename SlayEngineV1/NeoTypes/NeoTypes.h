#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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

uint64 asInt(double Value);
double asDouble(sint64 Value);

typedef struct
{
    void* *Values;
    uint64 Length;
}* array;
array arrNew(uint64 Length);
uint16 arrInit(array Array, uint64 Length, void* Values, ...);
uint16 arrInsert(array Array, uint64 Index, void* Value);
uint16 arrRemove(array Array, uint64 Index);

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

typedef struct
{
    array List;
    uint64 Length;
    boolean Cache;
}* list;
typedef struct listNodeStruct* listNode;
typedef struct
{
    listNode Next;
    void* Value;
}* listNodeStruct;