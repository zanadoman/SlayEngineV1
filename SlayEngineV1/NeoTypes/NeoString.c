#include "NeoTypes.h"

uint64 strLength(char* Characters)
{
    uint64 length;

    length = 0;
    while (Characters[length] != '\0')
    {
        length++;
    }

    return length + 1;
}

string strNew()
{
    string String;

    String = malloc(sizeof(string));
    if (String == NULL)
    {
        return NULL;
    }
    String->String = malloc(sizeof(char) * 1);
    if (String->String == NULL)
    {
        free(String);
        return NULL;
    }
    String->String[0] = '\0';
    String->Lenght = 1;

    return String;
}

uint16 strInit(string String, char* Characters)
{   
    String->Lenght = strLength(Characters);
    free(String->String);
    String->String = malloc(sizeof(char) * String->Lenght);
    if (String->String == NULL)
    {
        String->Lenght = 0;
        return 1;
    }

    for (uint64 i = 0; i < String->Lenght; i++)
    {
        String->String[i] = Characters[i];
    }
    String->String[String->Lenght - 1] = '\0';

    return 0;
}

uint16 strAppend(string String, char Character)
{
    String->String = realloc(String->String, String->Lenght + 1);
    if (String->String == NULL)
    {
        String->Lenght = 0;
        return 1;
    }
    String->String[String->Lenght - 1] = Character;
    String->String[String->Lenght] = '\0';
    String->Lenght++;

    return 0;
}

uint16 strConcat(string String, uint64 Count, char* Characters, ...)
{
    char* StringTMP;
    uint64 StringLengthTMP;

    va_list CharactersArgs;
    uint64 current;
    char* CharactersTemp;

    va_start(CharactersArgs, Characters);
    StringLengthTMP = strLength(Characters) - 1;
    for (uint64 i = 1; i < Count; i++)
    {
        StringLengthTMP += strLength(va_arg(CharactersArgs, char*)) - 1;
    }
    StringLengthTMP++;
    va_end(CharactersArgs);

    StringTMP = malloc(sizeof(char) * StringLengthTMP);
    if (StringTMP == NULL)
    {
        return 1;
    }

    va_start(CharactersArgs, Characters);
    for (current = 0; current < strLength(Characters) - 1; current++)
    {
        StringTMP[current] = Characters[current];
    }
    for (uint64 i = 1; i < Count; i++)
    {
        CharactersTemp = va_arg(CharactersArgs, char*);
        for (uint64 j = 0; j < strLength(CharactersTemp) - 1; j++)
        {
            StringTMP[current] = CharactersTemp[j];
            current++;
        }
    }
    StringTMP[StringLengthTMP - 1] = '\0';
    va_end(CharactersArgs);

    free(String->String);
    String->String = StringTMP;
    String->Lenght = StringLengthTMP;

    return 0;
}

uint16 strRead(string String)
{
    char Character;

    while ((Character = getchar()) != '\n')
    {
        if (strAppend(String, Character) == 1)
        {
            return 1;
        }
    }

    return 0;
}

uint16 strSplit(array Array, char* Characters, char Character)
{
    array result;
    
    string StringTMP;

    result = arrNew(0);
    if (result == NULL)
    {
        return 1;
    }

    StringTMP = strNew();
    if (StringTMP == NULL)
    {
        return 1;
    }
    arrInsert(result, result->Length, StringTMP);
    for (uint64 i = 0; i < strLength(Characters) - 1; i++)
    {
        if (Characters[i] != Character)
        {
            if (strAppend(result->Values[result->Length - 1], Characters[i]) == 1)
            {
                return 1;
            }
        }
        else
        {
            if (strAppend(result->Values[result->Length - 1], '\0') == 1)
            {
                return 1;
            }
            StringTMP = strNew();
            if (StringTMP == NULL)
            {
                return 1;
            }
            arrInsert(result, result->Length, StringTMP);
        }
    }

    free(Array->Values);
    Array->Values = result->Values;
    Array->Length = result->Length;
    free(result);

    return 0;
}

boolean strCompare(char* Characters1, char* Characters2)
{
    uint64 Characters1Length;

    Characters1Length = strLength(Characters1);
    if (Characters1Length == strLength(Characters2))
    {
        for (uint64 i = 0; i < Characters1Length; i++)
        {
            if (Characters1[i] != Characters2[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

uint16 strPurge(string String)
{
    free(String->String);
    free(String);

    return 0;
}