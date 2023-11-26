#include "game.h"

#undef main

int main(int argc, char *argv[])
{
    game* Game = malloc(sizeof(game));

    player* Player1;

    Game->Display = slayNew("Graphical User Interface", 800, 600);
    
    Game->Threads = arrNew(2);
    Game->Threads->Values[0] = malloc(sizeof(pthread_t));
    Game->Threads->Values[1] = malloc(sizeof(pthread_t));

    Game->DisplayPrevTick = 0;

    Game->Platforms = arrNew(5);
    Game->Platforms->Values[0] = newPlatform(0, 550, 800, 50, 64, 64, 128);
    Game->Platforms->Values[1] = newPlatform(300, 450, 200, 30, 16, 16, 32);
    Game->Platforms->Values[2] = newPlatform(200, 350, 100, 30, 16, 16, 32);
    Game->Platforms->Values[3] = newPlatform(350, 250, 100, 30, 16, 16, 32);
    Game->Platforms->Values[4] = newPlatform(500, 150, 100, 30, 16, 16, 32);

    Game->Player = newPlayer(100, 100, 28, 40, 0.4, 1.1, 200, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_LCTRL);

    Game->Projectiles = arrNew(0);

    if (loadTextures(Game) != 0)
    {
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