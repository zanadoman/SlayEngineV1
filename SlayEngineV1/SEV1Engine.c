#include "SlayEngineV1.h"

uint8 slayLogo(slayEngine* Engine);

slayEngine* slayNewEngine(char* Title, uint16 Width, uint16 Height, uint64 Scenes, uint16 MaxFPS, char* IconPath)
{
    slayEngine* result;

    SDL_Surface* icon;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        printf("ERROR Unable to initialize SDL");
        exit(1);
    }
    if (TTF_Init() != 0)
    {
        printf("ERROR Unable to initialize SDL_TTF");
        exit(1);
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) != 0)
    {
        printf("ERROR Unable to initialize SDL_MIXER");
        exit(1);
    }

    result = malloc(sizeof(slayEngine));
    if (result == NULL)
    {
        printf("ERROR Unable to allocate memory for ENGINE\n");
        exit(1);
    }
    
    result->Display = malloc(sizeof(slayDisplay));
    if (result->Display == NULL)
    {
        printf("ERROR Unable to allocate memory for DISPLAY\n");
        exit(1);
    }
    result->Display->Width = Width;
    result->Display->Height = Height;
    result->Display->Window = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, result->Display->Width, result->Display->Height, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED);
    if (result->Display->Window == NULL)
    {
        printf("ERROR Unable to create WINDOW");
        exit(1);
    }
    result->Display->Renderer = SDL_CreateRenderer(result->Display->Window, -1, SDL_RENDERER_ACCELERATED);
    if (result->Display->Renderer == NULL)
    {
        printf("ERROR Unable to create RENDERER");
        exit(1);
    }
    if (SDL_RenderSetLogicalSize(result->Display->Renderer, Width, Height) != 0)
    {
        printf("ERROR Unable to set RENDERER_LOGICAL_SIZE");
        exit(1);
    }
    if (SDL_SetRenderDrawBlendMode(result->Display->Renderer, SDL_BLENDMODE_BLEND) != 0)
    {
        printf("ERROR Unable to set RENDERER_BLEND_MODE");
        exit(1);
    }

    if (IconPath != NULL)
    {
        icon = IMG_Load(IconPath);
        if (icon == NULL)
        {
            printf("ERROR Unable to load ICON: %s\n", IconPath);
            exit(1);
        }
        SDL_SetWindowIcon(result->Display->Window, icon);
        SDL_FreeSurface(icon);
    }

    result->Camera = malloc(sizeof(slayCamera));
    if (result->Camera == NULL)
    {
        printf("ERROR Unable to allocate memory for CAMERA\n");
        exit(1);
    }
    result->Mouse = malloc(sizeof(slayMouse));
    if (result->Mouse == NULL)
    {
        printf("ERROR Unable to allocate memory for MOUSE\n");
        exit(1);
    }

    result->Threads = arrNew(0);
    if (result->Threads == NULL)
    {
        printf("ERROR Unable to allocate memory for THREADS\n");
        exit(1);
    }

    result->PrevTick = 0;
    result->DeltaTime = 0;
    result->MaxFPS = MaxFPS;

    result->Scenes = arrNew(Scenes);
    if (result->Scenes == NULL)
    {
        printf("ERROR Unable to allocate memory for SCENES\n");
        exit(1);
    }
    for (uint64 i = 0; i < result->Scenes->Length; i++)
    {
        result->Scenes->Values[i] = NULL;
    }
    result->CurrentScene = 0;

    result->Game = NULL;

    slayLogo(result);

    return result;
}

uint8 slayLogo(slayEngine* Engine)
{
    SDL_Texture* logo;

    logo = slayLoadTexture(Engine, "assets/engine/logo.jpg");

    slayRenderStart(Engine);
    slayRenderTexture(Engine, 0, 0, Engine->Display->Width, Engine->Display->Height, 0, slayFlipNONE, logo, 255, 255, 255, 255);
    slayRenderEnd(Engine);
    SDL_DestroyTexture(logo);

    SDL_Delay(1500);

    return 0;
}