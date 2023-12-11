#include "SlayEngineV1.h"

cJSON* slaySaveLoad(char* SavePath)
{
    cJSON* result;

    FILE* save;
    string raw;

    save = fopen(SavePath, "r");
    if (save == NULL)
    {
        return NULL;
    }

    raw = strNew();
    while (!feof(save))
    {
        strAppend(raw, fgetc(save));
    }
    fclose(save);

    result = cJSON_Parse(raw->String);
    if (result == NULL)
    {
        cJSON_Delete(result);
        return NULL;
    }

    return result;
}