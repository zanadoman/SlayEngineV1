@echo off

gcc -o bin.exe *.c ./SlayEngineV1/*.c ./SlayEngineV1/NeoTypes/*.c -L./SlayEngineV1/lib -lSDL2 -lm
if %errorlevel%==0 (
	bin
)