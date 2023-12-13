@echo off

gcc -o Windows/bin.exe Demo/*.c Demo/Actors/*.c Demo/Scenes/*.c SlayEngineV1/*.c SlayEngineV1/NeoTypes/*.c SlayEngineV1/cJSON/*.c -mwindows -m64 -LSlayEngineV1/lib -lSDL2 -LSlayEngineV1/lib -lSDL2_image -LSlayEngineV1/lib -lSDL2_ttf -LSlayEngineV1/lib -lSDL2_mixer -lpthread -lm
if %errorlevel%==0 (
	cd Windows
	start ./bin
	cd ..
) else (
	pause
)