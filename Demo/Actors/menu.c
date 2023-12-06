#include "../game.h"

uint16 updateMenu(slayEngine* Engine, scene0* Scene)
{
    if (updateButton(Engine, Scene->Buttons->Values[0]))
    {
        unloadSceneCurrent(Engine);
        loadScene1(Engine);

        return 1;
    }

    if (updateButton(Engine, Scene->Buttons->Values[1]))
    {
        unloadSceneCurrent(Engine);
        loadScene2(Engine);

        return 1;
    }

    return 0;
}