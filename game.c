/*
Contains the main loop for the game.
Updates the DeltaTime and calls the updateQueue and renderQueue functions.
After everything done waits until slayFPS delays the game.
*/

#include "game.h"

#undef main

int main(int argc, char *argv[])
{
    game* Game;

    Game = malloc(sizeof(game));
    if (loadGame(Game) != 0)
    {
        return 1;
    }

    while(slayEvent(Game->Display) != 0)
    {
        //DeltaTime always needs to be the first thing done
        Game->DeltaTime = slayDeltaTime(&Game->DisplayPrevTick);

        updateQueue(Game);
        slayUpdateCamera(Game->Camera);
        renderQueue(Game);

        //slayFPS is always the last thing done
        slayFPS(165, Game->DisplayPrevTick);
    }

    return 0;
}