#include "SlayEngineV1.h"

uint8 slayLogo(slayEngine* Engine);

slayEngine* slayNewEngine(char* Title, uint16 Width, uint16 Height, uint64 Scenes, uint16 MaxFPS, char* IconPath)
{
    slayEngine* result;

    SDL_Surface* icon;

    if (Title == NULL)
    {
        printf("slayNewEngine(): Title must not be NULL\nParams: Title: %p, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        printf("slayNewEngine(): SDL_Init() failed\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }
    if (TTF_Init() != 0)
    {
        printf("slayNewEngine(): TTF_Init() failed\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) != 0)
    {
        printf("slayNewEngine(): Mix_OpenAudio() failed\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }

    result = malloc(sizeof(slayEngine));
    if (result == NULL)
    {
        printf("slayNewEngine(): Memory allocation failed (result)\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }
    
    result->Display = malloc(sizeof(slayDisplay));
    if (result->Display == NULL)
    {
        printf("slayNewEngine(): Memory allocation failed (result->Display)\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }
    result->Display->Width = Width;
    result->Display->Height = Height;
    result->Display->Window = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, result->Display->Width, result->Display->Height, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED);
    if (result->Display->Window == NULL)
    {
        printf("slayNewEngine(): SDL_CreateWindow() failed\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }
    result->Display->Renderer = SDL_CreateRenderer(result->Display->Window, -1, SDL_RENDERER_ACCELERATED);
    if (result->Display->Renderer == NULL)
    {
        printf("slayNewEngine(): SDL_CreateRenderer() failed\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }
    if (SDL_RenderSetLogicalSize(result->Display->Renderer, Width, Height) != 0)
    {
        printf("slayNewEngine(): SDL_RenderSetLogicalSize() failed\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }
    if (SDL_SetRenderDrawBlendMode(result->Display->Renderer, SDL_BLENDMODE_BLEND) != 0)
    {
        printf("slayNewEngine(): SDL_SetRenderDrawBlendMode() failed\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }

    if (IconPath != NULL)
    {
        icon = IMG_Load(IconPath);
        if (icon == NULL)
        {
            printf("slayNewEngine(): Icon loading failed\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %s\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
            exit(1);
        }
        SDL_SetWindowIcon(result->Display->Window, icon);
        SDL_FreeSurface(icon);
    }

    result->Camera = malloc(sizeof(slayCamera));
    if (result->Camera == NULL)
    {
        printf("slayNewEngine(): Memory allocation failed (result->Camera)\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }
    result->Mouse = malloc(sizeof(slayMouse));
    if (result->Mouse == NULL)
    {
        printf("slayNewEngine(): Memory allocation failed (result->Mouse)\nParams: Title: %s, Width: %d, Height: %d, Scenes: %lld, MaxFPS: %d, IconPath: %p\n", Title, Width, Height, Scenes, MaxFPS, IconPath);
        exit(1);
    }

    result->Threads = arrNew(0);

    result->PrevTick = 0;
    result->DeltaTime = 0;
    result->MaxFPS = MaxFPS;

    result->Scenes = arrNew(Scenes);
    result->CurrentScene = 0;

    result->Game = NULL;

    slayLogo(result);

    return result;
}

uint8 slayLogo(slayEngine* Engine)
{
    SDL_Texture* logo;

    if (Engine == NULL)
    {
        printf("slayLogo(): Engine must not be NULL\nParams: Engine: %p\n", Engine);
        exit(1);
    }

    logo = slayLoadTexture(Engine, "assets/engine/logo.jpg");
    if (logo == NULL)
    {
        printf("slayLogo(): slayLoadTexture() failed\nParams: Engine: %p\n", Engine);
        exit(1);
    }

    slayRenderStart(Engine);
    slayRenderTexture(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, 0, slayFlipNONE, logo, 255, 255, 255, 255);
    slayRenderEnd(Engine);
    SDL_DestroyTexture(logo);

    SDL_Delay(1500);

    return 0;
}