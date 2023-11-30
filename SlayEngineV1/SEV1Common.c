#include "SlayEngineV1.h"

slayDisplay* slayNew(char* Title, int Width, int Height)
{
    slayDisplay* result;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

    result = malloc(sizeof(slayDisplay));
    
    result->Width = Width;
    result->Height = Height;
    result->Window = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, result->Width, result->Height, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED);
    result->Renderer = SDL_CreateRenderer(result->Window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_RenderSetLogicalSize(result->Renderer, Width, Height);

    return result;
}

slayMouse* slayNewMouse()
{
    return malloc(sizeof(slayMouse));
}