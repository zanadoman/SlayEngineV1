#include "SlayEngineV1.h"

uint16 slayLogo(slayEngine* Engine);

slayEngine* slayNewEngine(char* Title, uint16 Width, uint16 Height, uint64 Scenes, uint64 Threads, uint16 MaxFPS)
{
    slayEngine* result;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

    result = malloc(sizeof(slayEngine));
    
    result->Display = malloc(sizeof(slayDisplay));
    result->Display->Width = Width;
    result->Display->Height = Height;
    result->Display->Window = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, result->Display->Width, result->Display->Height, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED);
    result->Display->Renderer = SDL_CreateRenderer(result->Display->Window, -1, SDL_RENDERER_ACCELERATED);  
    SDL_RenderSetLogicalSize(result->Display->Renderer, Width, Height);

    result->Camera = NULL;

    result->Mouse = malloc(sizeof(slayMouse));

    result->Threads = arrNew(Threads);
    for (uint64 i = 0; i < result->Threads->Length; i++)
    {
        result->Threads->Values[i] = malloc(sizeof(pthread_t));
    }

    result->PrevTick = 0;
    result->DeltaTime = 0;
    result->MaxFPS = MaxFPS;

    result->Scenes = arrNew(Scenes);
    result->CurrentScene = 0;

    result->Game = NULL;

    slayLogo(result);

    return result;
}

uint16 slayLogo(slayEngine* Engine)
{
    SDL_Texture* logo;

    logo = slayLoadTexture(Engine, "assets/engine/logo.jpg");

    slayRenderStart(Engine);
    SDL_RenderCopy(Engine->Display->Renderer, logo, NULL, NULL);
    SDL_DestroyTexture(logo);
    slayRenderEnd(Engine);

    SDL_Delay(2000);

    return 0;
}