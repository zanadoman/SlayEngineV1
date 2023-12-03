# SlayEngineV1
2D game engine for Linux and Windows, written in C with SDL2, it also uses the NeoTypes library.

# Features
-Keyboard input\
-Mouse input: buttons, wheel, absolute and relative movements\
-Render: colored rectangles, textures, texts, layers, fake 3D, rotation, flipping, opacity\
-Camera: zoom level, anchor to coordinates or ingame objects\
-Audio: stereo, loop, timed\
-Hitbox/Collision detection: hitbox with hitbox, cursor with hitbox\
-Vector calculations: length, scalar, translate, angle\
-Loading: textures, sounds, fonts\
-Saving: store everything you want\
-Control/Event: close event, deltatime, fps capping, pseudo randoms\
-Threads: start, wait for exit, exit\
-Scenes

# Other features
The engine can run in windowed fullscreen and in windowed mode as well.\
It can support any screen resolution or aspect ratio, it can adapt to it
while keeping the game's aspect ratio by using black bars.

# Wiki

## Common

### slayEngine* slayNewEngine()\
Creates a new engine instance for you.\
Arguments: Window title, Window width and height,\
Number of scenes and number of threads will be used\
Maximum FPS for slayCapFPS()

## Control

### uint32 slayGetTicks()\
Return the number of miliseconds since the engine initialized

### logic slayEvent()
Handles the window closing and updates the mouse state

### uint16 slayUpdateDeltaTime(slayEngine* Engine)
Updates the delta time

### uint16 slayCapFPS(slayEngine* Engine)
Caps FPS by the value defined at engine initialization\
You can change it by modifying Engine.MaxFPS

### uint64 slayRandom()
Returns a pseudo random int seeded from slayGetTicks() / your seed

## Render

