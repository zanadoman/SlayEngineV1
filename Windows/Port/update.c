#include "game.h"

uint16 updateQueue(game* Game)
{
    updatePlayer(Game);
    updateProjectile(Game);

    return 0;
}