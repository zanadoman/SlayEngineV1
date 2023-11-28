#include "SlayEngineV1.h"

Mix_Chunk* slayLoadSound(char* Path)
{
    Mix_Chunk* result;

    result = Mix_LoadWAV(Path);
    if (result == NULL)
    {
        printf("ERROR Unable to load sound: %s\n", Path);
        SDL_Quit();
        TTF_Quit();
        exit(1);
    }
    
    return result;
}

uint16 slayPlaySound(Mix_Chunk* Sound, uint8 Volume, sint16 Loops)
{
    Mix_VolumeChunk(Sound, Volume);
    Mix_PlayChannel(-1, Sound, Loops);

    return 0;
}