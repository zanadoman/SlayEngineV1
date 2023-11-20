#include "game.h"

int displayEvent(display Display);

int main(int argc, char *argv[])
{
    game* Game = malloc(sizeof(game));

    pthread_t Thread;
    player* Player1;

    Game->Display = slayNew("Graphical User Interface", 800, 600);
    
    Game->Threads = malloc(sizeof(pthread_t) * 2);
    Game->Threads[0] = malloc(sizeof(pthread_t));
    Game->Threads[1] = malloc(sizeof(pthread_t));

    Game->DisplayPrevTick = 0;

    Game->Platforms = malloc(sizeof(platform) * 6);
    Game->Platforms[0] = newPlatform(0, 550, 800, 50, 0, 128, 0);
    Game->Platforms[1] = newPlatform(300, 450, 200, 30, 0, 0, 0);
    Game->Platforms[2] = newPlatform(200, 350, 100, 30, 0, 0, 0);
    Game->Platforms[3] = newPlatform(350, 250, 100, 30, 0, 0, 0);
    Game->Platforms[4] = newPlatform(500, 150, 100, 30, 0, 0, 0);
    Game->Platforms[5] = NULL;

    Game->Player = newPlayer(100, 100, 30, 30, 0.4, 1.1, 200, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_LCTRL, 0, 0, 255);

    Game->Projectiles = malloc(sizeof(projectile));
    Game->Projectiles[0] = NULL;

    while(slayEvent(Game->Display) != 0)
    {   
        Game->DeltaTime = slayDeltaTime(&Game->DisplayPrevTick);

        updateQueue(Game);
        renderQueue(Game);

        slayFPS(165, Game->DisplayPrevTick);
    }
}