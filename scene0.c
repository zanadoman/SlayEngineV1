#include "game.h"

uint16 updateScene0(slayEngine* Engine, scene0* Scene)
{
    //1
    if (updateMenu(Engine, Scene))
    {
        return 2;
    }
    //2

    return 0;
}

uint16 renderScene0(slayEngine* Engine, scene0* Scene)
{
    //Background
    slayRenderColor(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, Scene->ColorR, Scene->ColorG, Scene->ColorB, 255);

    //Button
    for (uint64 i = 0; i < Scene->Buttons->Length; i++)
    {
        slayRenderTexture(Engine, ((button*)Scene->Buttons->Values[i])->X, ((button*)Scene->Buttons->Values[i])->Y, ((button*)Scene->Buttons->Values[i])->Width, ((button*)Scene->Buttons->Values[i])->Height, 0, slayFlipNONE, ((button*)Scene->Buttons->Values[i])->TextureCurrent, 255);
    }

    return 0;
}

uint16 loadScene0(slayEngine* Engine)
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
    
    scene->Buttons->Values[0] = malloc(sizeof(button));
    ((button*)scene->Buttons->Values[0])->TextureBase = slayLoadTexture(Engine, "assets/buttons/buttonbase.png");
    ((button*)scene->Buttons->Values[0])->TextureHover = slayLoadTexture(Engine, "assets/buttons/buttonhover.png");
    ((button*)scene->Buttons->Values[0])->TextureCurrent = ((button*)scene->Buttons->Values[0])->TextureBase;
    ((button*)scene->Buttons->Values[0])->X = 810;
    ((button*)scene->Buttons->Values[0])->Y = 330;
    ((button*)scene->Buttons->Values[0])->Width = 300;
    ((button*)scene->Buttons->Values[0])->Height = 100;
    ((button*)scene->Buttons->Values[0])->Pressed = false;
    ((button*)scene->Buttons->Values[0])->Hitbox = slayNewHitbox(&((button*)scene->Buttons->Values[0])->X, &((button*)scene->Buttons->Values[0])->Y, 0, 0, 300, 100);

    scene->Buttons->Values[1] = malloc(sizeof(button));
    ((button*)scene->Buttons->Values[1])->TextureBase = slayLoadTexture(Engine, "assets/buttons/buttonbase.png");
    ((button*)scene->Buttons->Values[1])->TextureHover = slayLoadTexture(Engine, "assets/buttons/buttonhover.png");
    ((button*)scene->Buttons->Values[1])->TextureCurrent = ((button*)scene->Buttons->Values[1])->TextureBase;
    ((button*)scene->Buttons->Values[1])->X = 810;
    ((button*)scene->Buttons->Values[1])->Y = 630;
    ((button*)scene->Buttons->Values[1])->Width = 300;
    ((button*)scene->Buttons->Values[1])->Height = 100;
    ((button*)scene->Buttons->Values[1])->Pressed = false;
    ((button*)scene->Buttons->Values[1])->Hitbox = slayNewHitbox(&((button*)scene->Buttons->Values[1])->X, &((button*)scene->Buttons->Values[1])->Y, 0, 0, 300, 100);

    //Scene
    Engine->CurrentScene = 0;

    return 0;
}

uint16 unloadScene0(slayEngine* Engine)
{
    scene0* scene;

    scene = Engine->Scenes->Values[0];

    //Buttons
    for (uint64 i = 0; i < scene->Buttons->Length; i++)
    {
        slayUnloadTexture(((button*)scene->Buttons->Values[i])->TextureBase);
        slayUnloadTexture(((button*)scene->Buttons->Values[i])->TextureHover);
        free(((button*)scene->Buttons->Values[i])->Hitbox);
        free(scene->Buttons->Values[i]);
    }
    arrPurge(scene->Buttons);

    //Scene
    free(scene);
    Engine->Scenes->Values[0] = NULL;

    return 0;
}