@echo off

gcc -o ./Windows/bin.exe *.c ./SlayEngineV1/*.c ./SlayEngineV1/NeoTypes/*.c -mwindows -L./SlayEngineV1/lib -lSDL2 -L./SlayEngineV1/lib -lSDL2_image -L./SlayEngineV1/lib -lSDL2_ttf -L./SlayEngineV1/lib -lSDL2_mixer -lpthread -lm
if %errorlevel%==0 (
	cd Windows
	start ./bin
	cd ..
)