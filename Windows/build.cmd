@echo off

gcc -o ./build/bin.exe *.c ./SlayEngineV1/*.c ./SlayEngineV1/NeoTypes/*.c -L./SlayEngineV1/lib -lSDL2 -L./SlayEngineV1/lib -lSDL2_image -L./SlayEngineV1/lib -lSDL2_ttf -L./SlayEngineV1/lib -lSDL2_mixer -lpthread -lm
if %errorlevel%==0 (
	start ./build/bin
)