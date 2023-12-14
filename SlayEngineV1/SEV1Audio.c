#include "SlayEngineV1.h"

slaySound* slayLoadSound(char* Path)
{
    Mix_Chunk* result;

    result = Mix_LoadWAV(Path);
    if (result == NULL)
    {
        printf("ERROR Unable to load SOUND: %s\n", Path);
        exit(1);
    }

    return result;
}

uint8 slayPlaySound(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops)
{
    Mix_VolumeChunk(Sound, Volume);
    if (Mix_PlayChannel(Channel, Sound, Loops) == -1)
    {
        printf("ERROR Unable to play SOUND (%d)", Channel);
        exit (1);
    }
    if (Mix_SetPanning(Channel, Left, Right) == 0)
    {
        printf("ERROR Unable to set SOUND_PANNING (%d)", Channel);
        exit (1);
    }

    return 0;
}

uint8 slayPlaySoundTicks(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops, uint32 Ticks)
{
    Mix_VolumeChunk(Sound, Volume);
    if (Mix_PlayChannelTimed(Channel, Sound, Loops, Ticks) == -1)
    {
        printf("ERROR Unable to play SOUND (%d)", Channel);
        exit (1);
    }
    if (Mix_SetPanning(Channel, Left, Right) == 0)
    {
        printf("ERROR Unable to set SOUND_PANNING (%d)", Channel);
        exit (1);
    }

    return 0;
}