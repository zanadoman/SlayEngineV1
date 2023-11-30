#include "game.h"

#undef main

int main(int argc, char *argv[])
{
    game* Game;

    Game = malloc(sizeof(game));
    loadGame(Game);

    while(slayEvent(Game->Display, Game->Mouse))
    {
        Game->DeltaTime = slayDeltaTime(&Game->DisplayPrevTick);

        updateQueue(Game);
        renderQueue(Game);

        slayFPS(165, Game->DisplayPrevTick);
    }

    return 0;
}