#include "NeoTypes.h"

logic fileRead(char* FilePath, array Lines)
{
    FILE* file;
    string line;
    char character;

    file = fopen(FilePath, "r");
    if (file == NULL)
    {
        return false;
    }

    line = strNew();
    if (line == NULL)
    {
        fclose(file);
        return false;
    }
    while (!feof(file))
    {
        character = fgetc(file);

        if (character != '\n')
        {
            if (strAppend(line, character) == false)
            {
                strPurge(line);
                fclose(file);
                return false;
            }
        }
        else
        {
            if (arrInsert(Lines, Lines->Length, line) == 1)
            {
                strPurge(line);
                fclose(file);
                return false;
            }
            
            line = strNew();
            if (line == NULL)
            {
                fclose(file);
                return false;
            }
        }
    }
    strPurge(line);
    fclose(file);

    return true;
}

logic fileWrite(array Lines, char* FilePath)
{
    FILE* file;

    file = fopen(FilePath, "w");
    if (file == NULL)
    {
        return false;
    }

    for (uint64 i = 0; i < Lines->Length; i++)
    {
        fprintf(file, "%s\n", ((string)Lines->Values[i])->String);
    }
    fclose(file);

    return true;
}