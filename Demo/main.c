#include "game.h"

#undef main

uint8 main(uint8 argc, char* *argv)
{
    slayEngine* Engine;

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 2, 3, 165, "assets/icon.png");
    loadGame(Engine);

    loadScene0(Engine);

    slayJSON* save = slayLoadJSON("saves/test.json");
    printf("%s\n", slayGetJSONKey(save, "name")->valuestring);
    printf("%d\n", slayGetJSONKey(save, "age")->valueint);
    printf("%s\n", slayGetJSONKey(save, "city")->valuestring);
    printf("%lf\n", slayGetJSONKey(save, "score")->valuedouble);

    while (slayUpdate(Engine))
    {
        updateQueue(Engine);
        renderQueue(Engine);

        slayCapFPS(Engine);
    }

    unloadSceneCurrent(Engine);

    return 0;
}