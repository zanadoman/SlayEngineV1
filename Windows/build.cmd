@echo off

gcc -o ./build/bin.exe *.c ./SlayEngineV1/*.c ./SlayEngineV1/NeoTypes/*.c -L./SlayEngineV1/lib -lSDL2 -lpthread -lm
if %errorlevel%==0 (
	start ./build/bin
)