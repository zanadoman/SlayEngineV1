#include "SlayEngineV1.h"

slayJSON* slayLoadJSON(char* Path)
{
    cJSON* result;

    FILE* file;
    string raw;

    file = fopen(Path, "r");
    if (file == NULL)
    {
        printf("ERROR Unable to open JSON: %s\n", Path);
        exit(1);
    }

    raw = strNew();
    if (raw == NULL)
    {
        printf("ERROR Unable to allocate memory for JSON_RAW (%s)\n", Path);
        fclose(file);
        exit(1);
    }
    while (!feof(file))
    { 
        if (strAppend(raw, fgetc(file)) != 0)
        {
            printf("ERROR Unable to process JSON_RAW (%s)\n", Path);
            fclose(file);
            exit(1);
        }
    }
    fclose(file);

    result = cJSON_Parse(raw->String);
    if (result == NULL)
    {
        printf("ERROR Unable to parse JSON (%s)\n", Path);
        exit(1);
    }
    strPurge(raw);

    return result;
}

uint8 slaySaveJSON(slayJSON* JSON, char* Path)
{
    FILE* file;
    char* raw;

    file = fopen(Path, "w");
    if (file == NULL)
    {
        printf("ERROR Unable to open JSON: %s\n", Path);
        exit(1);
    }
    
    raw = cJSON_Print(JSON);
    if (raw == NULL)
    {
        printf("ERROR Unable to process JSON_RAW (%s)\n", Path);
        exit(1);
    }
    fputs(raw, file);
    fclose(file);
    free(raw);

    return 0;
}