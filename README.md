# SlayEngineV1
2D game engine for Linux and Windows, written in C with SDL2, it also uses the NeoTypes library.

# Features
-Keyboard input\
-Mouse input: buttons, wheel, absolute and relative movements\
-Render: colored rectangles, textures, texts, layers, fake 3D, rotation, flipping, opacity\
-Camera: zoom level, anchor to coordinates or ingame objects\
-Audio: stereo, loop, timed\
-Hitbox/Collision detection: hitbox with hitbox, cursor with hitbox\
-Vector calculations: length, translate, angle\
-Loading: textures, sounds, fonts\
-Saving: store everything you want\
-Control/Event: close event, deltatime, fps capping, pseudo randoms\
-Threads: start, wait for exit, exit\
-Scenes

# Other features
The engine can run in windowed fullscreen and in windowed mode as well. It can support any screen resolution or aspect ratio, it can adapt to it
while keeping the game's aspect ratio by using black bars.

# Wiki

## Common

### slayEngine* slayNewEngine()\
Creates a new engine instance for you.\
Arguments: Window title, Window width and height, Number of scenes and number of threads will be used Maximum FPS for slayCapFPS()

## Control

### uint32 slayGetTicks()
Return the number of miliseconds since the engine initialized

### logic slayEvent()
Handles the window closing and updates the mouse state

### uint16 slayUpdateDeltaTime(slayEngine* Engine)
Updates the delta time

### uint16 slayCapFPS(slayEngine* Engine)
Caps FPS by the value defined at engine initialization You can change it by modifying Engine.MaxFPS

### uint64 slayRandom()
Returns a pseudo random int seeded from slayGetTicks() / your seed

## Render

### Types
slayTexture* - for storing a texture loaded with slayLoadTexture()\
slayFont* - for storing a font loaded with slayLoadFont()\
slayObject* - an object with x, y, width, height values, you can render it with a color or a texture

### slayTexture* slayLoadTexture()
It can load a image file and turn it into a slayTexture*

### slayFont* slayLoadFont()
It can load a .ttf file and turn it into a slayFont*

### uint16 slayRenderStart()
You need to start every render session with this function

### uint16 slayRenderEnd()
You need to end every render sesson by calling this function

### uint16 slayRender***()
With these functions you can render something to the screen with absolute positions\
For textures and texts you can set rotation and flipping (slayFlipNONE, slayFlipHORIZONTAL, slayFlipVERTICAL) you can set both vertical and horizontal flip with a | operator.

### uint16 slayRender***Camera()
This time the rendering process will apply the perspective of the camera to the position and the size to the object to be rendered

### uint16 slayRender3D***Camera()
With this rendering function you can create fake 3D effect by stacking multiple layers behind each other

## Audio

### Types

slaySound* - for storing a sound loaded with slayLoadSound()

### slaySound* slayLoadSound()
It can load a .wav and turn it into a slaySound*

### uint16 slayPlaySound()
It can play a sound on a channel, you can set the volume for the left and right track separately and you can loop the sound if you want it

### uint16 slayPlaySoundTicks()
With this function you cap the length of the sound with ticks

## Inputs

### uint8 slayKey()
You can query the state of all keyboard buttons and LMB, MMB, RMB

## Mouse

### sint32 slayMouseRelative()
If you call this function with a true value then the engine will hide your cursor
and sets the input mode to relative

### logic slayCursorCollision()
Polls the collision state of the cursor with a slayHitbox* you can use this function to create buttons

### logic slayCursorCollisionCamera()
You should use this function if you want to interact with something that lives inside the game and being rendered by the perspective of the camera

## Vector

### uint16 slayVectorLength()
This function returns the length of a vector defined by two coordinates into a double*

### uint16 slayVectorTranslate()
This function creates a vector from a initial point, length and angle then outputs the coordinates of the terminal point into two double*

### uint16 slayVectorAngle()
This function returns the angle of a vector defined by two coordinates into a double*

## Hitbox

### slayHitbox* slayNewHitbox()
You can create new hitboxes with this function

### uint8 slayCollision()
This function checks the collision between two hitboxes and returns the collision value in a 8bit bitmask

### Collision values
You can get the predefinied values with: slayColl***\
\
The four main value from the bitmask:\
1 - TOPLEFT - 0b....0001\
2 - TOPRIGHT - 0b....0010\
3 - BOTTOMLEFT - 0b....0100\
4 - BOTTOMRIGHT - 0b....1000\
\
Other values:\
3 - TOP - 0b....0011\
12 - BOTTOM - 0b....1100\
5 - LEFT - 0b....0101\
10 - RIGHT - 0b....1010\
15 - ALL - 0b....1111

## Camera

### uint16 slaySetCamera()
You can change the properties of the camera with this function, you attach it to an ingame object or a fixed coordinate, you can also set zoom level

### uint16 slayApplyCamera()
This function can apply the perspective of the camera to a slayObject*

## Thread

### uint16 slayThreadStart()
You can start any function in a new thread with the engine as argument

### uint16 slayThreadWaitExit()
Halt your program until the thread with the given ID returns

### slayThreadExit;
You should put this command at the end of each thread function

### A sample for thread functions:
void* updatePlayerThread(void* Engine)
{
    updatePlayer(Engine);

    slayThreadExit;
}

# Samples

## main.c
#include "game.h"\
\
#undef main\
\
uint16 main(uint64 argc, char* *argv)\
{\
    slayEngine* Engine;\
\
    Engine = slayNewEngine("SlayEngineV1 DEMO", 1920, 1080, 1, 2, 165);\
    loadQueue(Engine);\
\
    Engine->CurrentScene = 0;\
\
    while(slayEvent(Engine))\
    {\
        slayUpdateDeltaTime(Engine);\
\
        updateQueue(Engine);\
        renderQueue(Engine);\
\
        slayCapFPS(Engine);\
    }\
\
    saveQueue(Engine);\
\
    return 0;\
}\