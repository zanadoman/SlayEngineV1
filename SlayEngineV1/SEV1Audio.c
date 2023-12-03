#include "SlayEngineV1.h"

slaySound* slayLoadSound(char* Path)
{
    Mix_Chunk* result;

    result = Mix_LoadWAV(Path);
    if (result == NULL)
    {
        printf("ERROR Unable to load sound: %s\n", Path);
        exit(1);
    }

    return result;
}

uint16 slayPlaySound(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops)
{
    Mix_VolumeChunk(Sound, Volume);
    Mix_PlayChannel(Channel, Sound, Loops);
    Mix_SetPanning(Channel, Left, Right);

    return 0;
}

uint16 slayPlaySoundTicks(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops, uint64 Ticks)
{
    Mix_VolumeChunk(Sound, Volume);
    Mix_SetPanning(Channel, Left, Right);
    Mix_PlayChannelTimed(Channel, Sound, Loops, Ticks);

    return 0;
}