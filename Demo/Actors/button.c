#include "../game.h"

button* newButton(slayEngine* Engine, double X, double Y, uint16 Width, uint16 Height, char* TextureBase, char* TextureHover)
{
    button* result;

    result = malloc(sizeof(button));

    result->X = X;
    result->Y = Y;

    result->Width = Width;
    result->Height = Height;

    result->Pressed = false;

    result->TextureBase = slayLoadTexture(Engine, TextureBase);
    result->TextureHover = slayLoadTexture(Engine, TextureHover);
    result->TextureCurrent = result->TextureBase;

    result->Hitbox = slayNewHitbox(actBUTTON, &result->X, &result->Y, 0, 0, result->Width, result->Height, -1, -1, 0, 0, 0, 0);

    return result;
}

logic updateButton(slayEngine* Engine, button* Button)
{
    if (slayCursorCollision(Engine, Button->Hitbox))
    {
        Button->TextureCurrent = Button->TextureHover;

        if (slayKey(Engine, SDL_SCANCODE_LMB))
        {
            Button->Pressed = true;
        }
        else if (Button->Pressed)
        {
            Button->Pressed = false;

            return true;
        }
    }
    else
    {
        Button->Pressed = false;
        Button->TextureCurrent = Button->TextureBase;
    }

    return false;
}

uint8 destroyButton(button* Button)
{
    slayUnloadTexture(Button->TextureBase);
    slayUnloadTexture(Button->TextureHover);
    free(Button->Hitbox);
    free(Button);

    return 0;
}