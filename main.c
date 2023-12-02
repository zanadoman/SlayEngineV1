/*
Vektorok
Forgatások
Player lőjön a kurzor irányába kattintással
*/

#include "game.h"

#undef main

int main(int argc, char *argv[])
{
    slayEngine* Engine;

    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 1, 2, 165);
    loadQueue(Engine);

    Engine->CurrentScene = 0;

    double X2, Y2;
    slayVectorTerminal(0, 0, &X2, &Y2, 7, 45);
    printf("X2: %lf, Y2: %lf\n", X2, Y2);

    while(slayEvent(Engine))
    {
        slayUpdateDeltaTime(Engine);

        updateQueue(Engine);
        renderQueue(Engine);

        slayCapFPS(Engine);
    }

    return 0;
}