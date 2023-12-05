#include "game.h"

uint16 renderQueue(slayEngine* Engine)
{
    slayRenderStart(Engine);

    switch (Engine->CurrentScene)
    {
        case 0:
            renderScene0(Engine, Engine->Scenes->Values[0]);
            break;
        case 1:
            renderScene1(Engine, Engine->Scenes->Values[1]);
            break;
        case 2:
            renderScene2(Engine, Engine->Scenes->Values[2]);
            break;
    }
    
    slayRenderEnd(Engine);

    return 0;
}