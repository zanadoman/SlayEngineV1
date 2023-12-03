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

### uint32 slayGetTicks()
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

### Types
slayTexture* - for stroring a texture loaded with slayLoadTexture()
slayFont* - for storring a font loaded with slayLoadFont()
slayObject* - an object with x, y, width, height values, you can render it
with a color or a texture

### slayTexture* slayLoadTexture()
It can load a image file and turn it into a slayTexture*

### slayFont* slayLoadFont()
It can load a .ttf file and turn it into a slayFont*

### uint16 slayRenderStart()
You need to start every render session with this function

### uint16 slayRenderEnd()
You need to end every render sesson by calling this function

### uint16 slayRender***()
With these functions you can render something to the screen with absolute positions

### uint16 slayRender***Camera()
This time the rendering process will apply the perspective of the camera to the\
position and the size to the object to be rendered

### uint16 slayRender3D***Camera()
With this rendering function you can create fake 3D effect by stacking multiple\
layers behind each other

## Audio