#include "SlayEngineV1.h"

slayJSON* slayLoadJSON(char* Path)
{
    cJSON* result;

    FILE* file;
    string raw;

    file = fopen(Path, "r");
    if (file == NULL)
    {
        return NULL;
    }

    raw = strNew();
    while (!feof(file))
    { 
        strAppend(raw, fgetc(file));
    }
    fclose(file);

    result = cJSON_Parse(raw->String);
    strPurge(raw);
    if (result == NULL)
    {
        return NULL;
    }

    return result;
}

uint8 slaySaveJSON(slayJSON* JSON, char* Path)
{
    FILE* file;
    char* raw;

    file = fopen(Path, "w");
    if (file == NULL)
    {
        return 1;
    }
    
    raw = cJSON_Print(JSON);
    fputs(raw, file);
    fclose(file);
    free(raw);

    return 0;
}