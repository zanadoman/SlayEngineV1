#include "game.h"

#undef main

int main(int argc, char *argv[])
{
    game* Game;

    Game = malloc(sizeof(game));
    loadGame(Game);

    while(slayEvent(Game->Engine))
    {
        slayUpdateDeltaTime(Game->Engine);

        updateQueue(Game);
        renderQueue(Game);

        slayCapFPS(Game->Engine);
    }

    return 0;
}