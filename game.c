#include "game.h"

#undef main

int main(int argc, char *argv[])
{
    game* Game;

    Game = malloc(sizeof(game));
    if (loadGame(Game) != 0)
    {
        printf("ERROR An error occured while loading the game.\n");
        return 1;
    }

    while(slayEvent(Game->Display) != 0)
    {   
        Game->DeltaTime = slayDeltaTime(&Game->DisplayPrevTick);

        updateQueue(Game);
        renderQueue(Game);

        slayFPS(165, Game->DisplayPrevTick);
    }

    return 0;
}