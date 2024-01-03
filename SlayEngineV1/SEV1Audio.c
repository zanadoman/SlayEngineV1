#include "SlayEngineV1.h"

slaySound* slayLoadSound(char* Path)
{
    Mix_Chunk* result;

    if (Path == NULL)
    {
        printf("slayLoadSound(): Path must not be NULL\nParams: Path: %p\n", Path);
        exit(1);
    }

    result = Mix_LoadWAV(Path);
    if (result == NULL)
    {
        printf("slayLoadSound(): Unable to load Sound\nParams: Path: %s\n", Path);
        exit(1);
    }

    return result;
}

uint8 slayPlaySound(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops)
{
    if (Sound == NULL)
    {
        printf("slayPlaySound(): Sound must not be NULL\nParams: Sound: %p, Channel: %d, Volume: %d, Left: %d, Right: %d, Loops: %d\n", Sound, Channel, Volume, Left, Right, Loops);
        exit(1);
    }
    if (Channel < -1)
    {
        printf("slayPlaySound(): Channel must not be less than -1\nParams: Sound: %p, Channel: %d, Volume: %d, Left: %d, Right: %d, Loops: %d\n", Sound, Channel, Volume, Left, Right, Loops);
        exit(1);
    }
    if (Loops < -1)
    {
        printf("slayPlaySound(): Loops must not be less than -1\nParams: Sound: %p, Channel: %d, Volume: %d, Left: %d, Right: %d, Loops: %d\n", Sound, Channel, Volume, Left, Right, Loops);
        exit(1);
    }

    Mix_VolumeChunk(Sound, Volume);
    if (Mix_PlayChannel(Channel, Sound, Loops) == -1)
    {
        printf("slayPlaySound(): Unable to play Sound\nParams: Sound: %p, Channel: %d, Volume: %d, Left: %d, Right: %d, Loops: %d\n", Sound, Channel, Volume, Left, Right, Loops);
        exit (1);
    }
    if (Mix_SetPanning(Channel, Left, Right) == 0)
    {
        printf("slayPlaySound(): Unable to set Channel Panning\nParams: Sound: %p, Channel: %d, Volume: %d, Left: %d, Right: %d, Loops: %d\n", Sound, Channel, Volume, Left, Right, Loops);
        exit (1);
    }

    return 0;
}

uint8 slayPlaySoundTicks(slaySound* Sound, sint16 Channel, uint8 Volume, uint8 Left, uint8 Right, sint16 Loops, uint32 Ticks)
{
    if (Sound == NULL)
    {
        printf("slayPlaySoundTicks(): Sound must not be NULL\nParams: Sound: %p, Channel: %d, Volume: %d, Left: %d, Right: %d, Loops: %d, Ticks: %d\n", Sound, Channel, Volume, Left, Right, Loops, Ticks);
        exit(1);
    }
    if (Channel < -1)
    {
        printf("slayPlaySoundTicks(): Channel must not be less than -1\nParams: Sound: %p, Channel: %d, Volume: %d, Left: %d, Right: %d, Loops: %d, Ticks: %d\n", Sound, Channel, Volume, Left, Right, Loops, Ticks);
        exit(1);
    }
    if (Loops < -1)
    {
        printf("slayPlaySoundTicks(): Loops must not be less than -1\nParams: Sound: %p, Channel: %d, Volume: %d, Left: %d, Right: %d, Loops: %d, Ticks: %d\n", Sound, Channel, Volume, Left, Right, Loops, Ticks);
        exit(1);
    }

    Mix_VolumeChunk(Sound, Volume);
    if (Mix_PlayChannelTimed(Channel, Sound, Loops, Ticks) == -1)
    {
        printf("slayPlaySoundTicks(): Unable to play Sound\nParams: Sound: %p, Channel: %d, Volume: %d, Left: %d, Right: %d, Loops: %d, Ticks: %d\n", Sound, Channel, Volume, Left, Right, Loops, Ticks);
        exit (1);
    }
    if (Mix_SetPanning(Channel, Left, Right) == 0)
    {
        printf("slayPlaySoundTicks(): Unable to set Channel Panning\nParams: Sound: %p, Channel: %d, Volume: %d, Left: %d, Right: %d, Loops: %d, Ticks: %d\n", Sound, Channel, Volume, Left, Right, Loops, Ticks);
        exit (1);
    }

    return 0;
}