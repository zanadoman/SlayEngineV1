#include "game.h"

#undef main

int main(int argc, char *argv[])
{
    game* Game;

    Game = malloc(sizeof(game));
    loadGame(Game);

    while(slayEvent(Game->Display, Game->Mouse) != 0)
    {
        Game->DeltaTime = slayDeltaTime(&Game->DisplayPrevTick);

        printf("x: %d, y: %d, lmb: %d, mmb: %d, rmb: %d, wheel: %d\n", Game->Mouse->X, Game->Mouse->Y, Game->Mouse->LMB, Game->Mouse->MMB, Game->Mouse->RMB, Game->Mouse->Wheel);

        updateQueue(Game);
        renderQueue(Game);

        slayFPS(165, Game->DisplayPrevTick);
    }

    return 0;
}