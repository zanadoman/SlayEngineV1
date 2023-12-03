/*
Wiki írása
*/

#include "game.h"

#undef main

uint16 main(uint64 argc, char* *argv)
{
    slayEngine* Engine;

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 1, 2, 165);
    loadQueue(Engine);

    Engine->CurrentScene = 0;

    array save = arrNew(0);
    fileRead("save.txt", save);
    ((scene0*)Engine->Scenes->Values[0])->Player->X = STRtoDOUBLE(((string)save->Values[0])->String, NULL);
    ((scene0*)Engine->Scenes->Values[0])->Player->Y = STRtoDOUBLE(((string)save->Values[1])->String, NULL);
    strPurge(save->Values[0]);
    strPurge(save->Values[1]);
    arrPurge(save);

    while(slayEvent(Engine))
    {
        slayUpdateDeltaTime(Engine);

        updateQueue(Engine);
        renderQueue(Engine);

        slayCapFPS(Engine);
    }

    save = arrNew(2);
    save->Values[0] = strNew();
    save->Values[1] = strNew();
    DOUBLEtoSTR(((scene0*)Engine->Scenes->Values[0])->Player->X, save->Values[0]);
    DOUBLEtoSTR(((scene0*)Engine->Scenes->Values[0])->Player->Y, save->Values[1]);
    fileWrite(save, "save.txt");

    return 0;
}