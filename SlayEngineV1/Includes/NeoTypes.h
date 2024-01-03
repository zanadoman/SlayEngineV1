#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

//_____________________________________________NeoTypes.h____________________________________________//

#define true 1
#define false 0
/*Logical variable just like bool or boolean.*/
typedef unsigned char logic;
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;
typedef unsigned long long uint64;
typedef signed long long sint64;

#define ARRAY_SIZE (sizeof(void*) + sizeof(uint64))
/*Dynamically sized Array, with insertion and deletion capabilities.*/
typedef struct arrayStruct* array;
#define STRING_SIZE (sizeof(void*) + sizeof(uint64))
/*String that holds String and Length data.*/
typedef struct stringStruct* string;

/*Universal data type for NeoTypes.*/
typedef union
{
    logic Logic;

    uint64 uInt;
    sint64 sInt;
    double Double;

    array Array;
    string String;

    void* Pointer;
} NeoTypes;

//_____________________________________________NeoArray.c____________________________________________//

struct arrayStruct
{
    NeoTypes* Values;
    uint64 Length;
};

/*Creates a new Array with the given Length.
Returns the address of the newly allocated Array.
You must initialize every Array with this function before use.*/
array arrNew(uint64 Length);
/*Returns an Element from the Array at the given Index.
Assign a value to an Element: arrElement(Array, Index)->uInt = 10;
Get a value from an Element: uint8 a = arrElement(Array, Index)->uInt;*/
NeoTypes* arrElement(array Array, uint64 Index);
/*Inserts a new Element to the Array at the given Index.
Returns the address of the new Element.
The default value of the new Element is 0.
Set the value of the new Element: arrInsert(Array, Index)->uInt = 10;*/
NeoTypes* arrInsert(array Array, uint64 Index);
/*Removes an element from the Array at the given Index.*/
uint8 arrRemove(array Array, uint64 Index);
/*Frees the Array from the memory with all of its Elements.
It is safe to pass NULL to this function.*/
uint8 arrPurge(array Array);

//____________________________________________NeoString.c____________________________________________//

struct stringStruct
{
    char* String;
    uint64 Length;
};

/*Returns the Length of the String (char*) with the '\0' included.*/
uint64 strLength(char* Characters);
/*Creates a new String, the String->String will be "\0" and the String->Length will be 1.
Returns the address of the newly allocated String.
You must initialize every String with this function before use.*/
string strNew();
/*Replaces the String->String of the String with the given String (char*).*/
uint8 strInit(string String, char* Characters);
/*Appends the given Character to the end of the String.*/
uint8 strAppend(string String, char Character);
/*Concatenates two or more Strings (char*) into one String.
The number of the Strings (char*) to be concatenated must be accurate.*/
uint8 strConcat(string String, uint64 Count, char* Characters, ...);
/*Reads the content of standard input until '\n' and stores it in a String.*/
uint8 strRead(string String);
/*Splits the String (char*) into an Array by the given Character.*/
uint8 strSplit(array Array, char* Characters, char Character);
/*Compares two Strings (char*) Character by Character and returns true if they are equal or false if they differ.*/
logic strCompare(char* Characters1, char* Characters2);
/*Frees the String from the memory and its String->String value.
It is safe to pass NULL to this function.*/
uint8 strPurge(string String);

//____________________________________________NeoConvert.c___________________________________________//

/*Converts the String to an Unsigned Integer.
You can check the Success of the conversion by passing a Logic variable by reference, it is safe to pass NULL if Error handling is not needed.
If it fails it will return 0 as result.*/
uint64 STRtoUINT(char* Characters, logic* Success);
/*Converts an Unsigned Integer to String.
Returns 0 on Success or 1 on Error.*/
uint8 UINTtoSTR(uint64 Number, string String);
/*Converts the String to a Signed Integer.
You can check the Success of the conversion by passing a Logic variable by reference, it is safe to pass NULL if Error handling is not needed.
If it fails it will return 0 as result.*/
sint64 STRtoSINT(char* Characters, logic* Success);
/*Converts a Signed Integer to String.
Returns 0 on Success or 1 on Error.*/
uint8 SINTtoSTR(sint64 Number, string String);
/*Converts the String to a Double.
You can check the Success of the conversion by passing a Logic variable by reference, it is safe to pass NULL if Error handling is not needed.
If it fails it will return 0 as result.*/
double STRtoDOUBLE(char* Characters, logic* Success);
/*Converts a Double to String.
Returns 0 on Success or 1 on Error.*/
uint8 DOUBLEtoSTR(double Number, string String);

//_____________________________________________NeoFile.c_____________________________________________//

/*Reads the content of a text file and puts its lines into an Array.
Returns 0 on Success or 1 on Error.*/
uint8 fileRead(char* FilePath, array Lines);
/*Writes the content of an Array of Strings line by line into a text file.
Returns 0 on Success or 1 on Error.*/
uint8 fileWrite(array Lines, char* FilePath);

//____________________________________________NeoMemory.c____________________________________________//

/*Copies a block of memory.\
Returns the address of the copied memory or NULL if Size was 0.*/
void* memCopy(void* Source, uint64 Size);
/*Copies a block of memory to the given Destination.
You must preallocate the Destination to the correct Size.*/
uint8 memCopyTo(void* Source, void* Destination, uint64 Size);
/*Loads data to the memory from a file.
Returns the address of the loaded data or NULL if Size was 0.*/
void* memLoad(char* FilePath, uint64 Size);
/*Loads data to the given Destination.
You must preallocate the Destination to the correct Size.*/
uint8 memLoadTo(char* FilePath, void* Destination, uint64 Size);
/*Saves data from the memory into a file.
Returns 0 on Success or 1 on Error.*/
uint8 memSave(void* Source, uint64 Size, char* FilePath);