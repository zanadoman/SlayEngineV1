#include "SlayEngineV1.h"

//Maintains the main game loop
sint64 slayEvent(slayDisplay* Display)
{
    while (SDL_PollEvent(&Display->Event) != 0)
    {
        switch (Display->Event.type)
        {
            case SDL_QUIT:
                SDL_Quit();
                return 0;
        }
    }

    return -1;
}
//Returns the state of the specified key
uint8 slayKey(slayDisplay* Display, uint64 Key)
{
    SDL_PollEvent(&Display->Event);
    const uint8 *state = SDL_GetKeyboardState(NULL);

    return state[Key];
}