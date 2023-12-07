#include "../game.h"

uint8 updateScene0(slayEngine* Engine, scene0* Scene)
{
    //1
    if (updateMenu(Engine, Scene))
    {
        return 1;
    }
    //2

    return 0;
}

uint8 renderScene0(slayEngine* Engine, scene0* Scene)
{
    //Background
    slayRenderColor(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, Scene->ColorR, Scene->ColorG, Scene->ColorB, 255);

    //Button
    for (uint8 i = 0; i < Scene->Buttons->Length; i++)
    {
        slayRenderTexture(Engine, ((button*)Scene->Buttons->Values[i])->X, ((button*)Scene->Buttons->Values[i])->Y, ((button*)Scene->Buttons->Values[i])->Width, ((button*)Scene->Buttons->Values[i])->Height, 0, slayFlipNONE, ((button*)Scene->Buttons->Values[i])->TextureCurrent, 255);
    }

    return 0;
}

uint8 loadScene0(slayEngine* Engine)
{
    scene0* scene;

    //Scene
    Engine->Scenes->Values[0] = malloc(sizeof(scene0));
    scene = Engine->Scenes->Values[0];

    //Color
    scene->ColorR = 0;
    scene->ColorG = 0;
    scene->ColorB = 0;

    //Button
    scene->Buttons = arrNew(2);
    
    scene->Buttons->Values[0] = newButton(Engine, 810, 330, 300, 100, "assets/buttons/buttonbase.png", "assets/buttons/buttonhover.png");
    scene->Buttons->Values[1] = newButton(Engine, 810, 630, 300, 100, "assets/buttons/buttonbase.png", "assets/buttons/buttonhover.png");

    //Scene
    Engine->CurrentScene = 0;

    return 0;
}

uint8 unloadScene0(slayEngine* Engine)
{
    scene0* scene;

    scene = Engine->Scenes->Values[0];

    //Buttons
    for (uint8 i = 0; i < scene->Buttons->Length; i++)
    {
        destroyButton(scene->Buttons->Values[i]);
    }

    //Scene
    free(scene);
    Engine->Scenes->Values[0] = NULL;

    return 0;
}