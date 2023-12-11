#include "SlayEngineV1.h"

cJSON* slayLoadJSON(char* Path)
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