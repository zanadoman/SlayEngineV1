@echo off

gcc -o bin.exe test.c -Llib -lSDL2 -lm
if %errorlevel%==0 (
	bin
)
pause