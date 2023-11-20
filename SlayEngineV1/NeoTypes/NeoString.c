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
    String->String = malloc(sizeof(char) * 1);
    String->String[0] = '\0';
    String->Lenght = 1;

    return String;
}

uint16 strInit(string String, char* Characters)
{
    free(String->String);
    
    String->Lenght = strLength(Characters);
    String->String = malloc(sizeof(char) * String->Lenght);

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
    String->String[String->Lenght - 1] = Character;
    String->String[String->Lenght] = '\0';
    String->Lenght++;

    return 0;
}

uint16 strConcat(string String, uint64 Count, char* Characters, ...)
{
    char* StringTMP;

    va_list CharactersArgs;
    uint64 current;
    char* CharactersTemp;

    va_start(CharactersArgs, Characters);
    String->Lenght = strLength(Characters) - 1;
    for (uint64 i = 1; i < Count; i++)
    {
        String->Lenght += strLength(va_arg(CharactersArgs, char*)) - 1;
    }
    String->Lenght++;
    va_end(CharactersArgs);

    StringTMP = malloc(sizeof(char) * String->Lenght);

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
    String->String[String->Lenght - 1] = '\0';
    va_end(CharactersArgs);

    free(String->String);
    String->String = StringTMP;

    return 0;
}

uint16 strRead(string String)
{
    char Character;

    while ((Character = getchar()) != '\n')
    {
        strAppend(String, Character);
    }

    return 0;
}

uint16 strSplit(array Array, string String, char Character)
{
    free(Array->Values);

    Array->Values = NULL;
    Array->Length = 0;

    arrInsert(Array, Array->Length, strNew());
    for (uint64 i = 0; i < String->Lenght - 1; i++)
    {
        if (String->String[i] != Character)
        {
            strAppend((string)Array->Values[Array->Length - 1], String->String[i]);
        }
        else
        {
            strAppend((string)Array->Values[Array->Length - 1], '\0');
            arrInsert(Array, Array->Length, strNew());
        }
    }

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