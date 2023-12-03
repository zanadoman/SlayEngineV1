#include "NeoTypes.h"

uint16 fileRead(char* FilePath, array Lines)
{
    FILE* file;
    string line;
    char character;

    file = fopen(FilePath, "r");
    if (file == NULL)
    {
        return 1;
    }

    line = strNew();
    while (!feof(file))
    {
        character = fgetc(file);

        if (character != '\n')
        {
            strAppend(line, character);
        }
        else
        {
            arrInsert(Lines, Lines->Length, line);
            line = strNew();
        }
    }
    strPurge(line);
    fclose(file);

    return 0;
}

uint16 fileWrite(array Lines, char* FilePath)
{
    FILE* file;

    file = fopen(FilePath, "w");
    if (file == NULL)
    {
        return 1;
    }

    for (uint64 i = 0; i < Lines->Length; i++)
    {
        fprintf(file, "%s\n", ((string)Lines->Values[i])->String);
    }

    return 0;
}