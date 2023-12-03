#include "game.h"

uint16 savePlayer(player* Player);

uint16 saveQueue(slayEngine* Engine)
{
    savePlayer(((scene0*)Engine->Scenes->Values[0])->Player);

    return 0;
}

uint16 savePlayer(player* Player)
{
    array save;

    save = arrNew(2);
    save->Values[0] = strNew();
    save->Values[1] = strNew();
    DOUBLEtoSTR(Player->X, save->Values[0]);
    DOUBLEtoSTR(Player->Y, save->Values[1]);
    fileWrite(save, "save.txt");

    return 0;
}