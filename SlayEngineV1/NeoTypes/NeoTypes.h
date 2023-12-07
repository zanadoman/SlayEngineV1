#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef struct arrayStruct* array;
typedef struct stringStruct* string;
typedef struct listStruct* list;
typedef struct listCacheStruct* listCache_t;
typedef struct listNodeStruct* listNode;

//________________NeoTypes.h_______________//

#define true 1
#define false 0
typedef char logic;
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;
typedef unsigned long uint64;
typedef signed long sint64;

//________________NeoCast.c________________// COMPLETED

uint64 asInt(double Value);
double asDouble(uint64 Value);

//________________NeoArray.c_______________// COMPLETED

struct arrayStruct
{
    void* *Values;
    uint64 Length;
};

array arrNew(uint64 Length);
uint8 arrInit(array Array, uint64 Length, void* Values, ...);

uint8 arrInsert(array Array, uint64 Index, void* Value);
uint8 arrRemove(array Array, uint64 Index);

uint8 arrPurge(array Array);

//_______________NeoString.c_______________ // COMPLETED

struct stringStruct
{
    char* String;
    uint64 Lenght;
};

uint64 strLength(char* Characters);

string strNew();
uint8 strInit(string String, char* Characters);

uint8 strAppend(string String, char Character);
uint8 strConcat(string String, uint64 Count, char* Characters, ...);

uint8 strRead(string String);
uint8 strSplit(array Array, char* Characters, char Character);
logic strCompare(char* Characters1, char* Characters2);

uint8 strPurge(string String);

//________________NeoList.c________________ // COMPLETED

struct listStruct
{
    listCache_t Cache;
    uint64 Length;
};
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

uint8 listInsert(list List, uint64 Index, void* Value);
uint8 listRemove(list List, uint64 Index);

listNode listGet(list List, uint64 Index);
uint8 listCache(list List, uint64 CacheCoverage);

uint8 listPurge(list List);

//_______________NeoConvert.c______________ // COMPLETED

uint64 STRtoUINT(char* Characters, logic* Success);
uint8 UINTtoSTR(uint64 Number, string String);

sint64 STRtoSINT(char* Characters, logic* Success);
uint8 SINTtoSTR(sint64 Number, string String);

double STRtoDOUBLE(char* Characters, logic* Success);
uint8 DOUBLEtoSTR(double Number, string String);

//________________NeoFile.c________________ // COMPLETED

logic fileRead(char* FilePath, array Lines);
logic fileWrite(array Lines, char* FilePath);