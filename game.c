#include "game.h"

#undef main

int main(int argc, char *argv[])
{
    game* Game;

    Game = malloc(sizeof(game));
    loadGame(Game);

    //sint32 x, y;
    //logic lmb, mmb, rmb;
    //sint8 wheel;

    while(slayEvent(Game->Display) != 0)
    {
        Game->DeltaTime = slayDeltaTime(&Game->DisplayPrevTick);

        //slayMouse(Game->Display, &x, &y, &lmb, &mmb, &rmb, &wheel);
        //printf("x: %d, y: %d, lmb: %d, mmb: %d, rmb: %d, wheel: %d\n", x, y, lmb, mmb, rmb, wheel);

        updateQueue(Game);
        renderQueue(Game);

        slayFPS(165, Game->DisplayPrevTick);
    }

    return 0;
}