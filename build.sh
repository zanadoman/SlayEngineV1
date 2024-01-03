#!/bin/sh

RED="\e[91m"
GREEN="\e[92m"
BLUE="\e[94m"
ENDCOLOR="\e[0m"

if [[ ! -z $1 && $1 == "-w" ]] || [[ ! -z $1 && $1 == "--windows" ]]
then
    x86_64-w64-mingw32-gcc -o Builds/Windows/bin.exe $(find . -name '*.c') -mwindows -LSlayEngineV1/Libraries/Windows -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lNeoTypes -lm
    if [ $? == 0 ]
    then
        echo -e "${BLUE}Windows ${GREEN}build successful!${ENDCOLOR}"
        cd Builds/Windows
        wine64 bin.exe
        if [ $? == 0 ]
        then
            echo -e "${BLUE}Windows ${GREEN}run successful!${ENDCOLOR}"
            exit 0
        else
            echo -e "${BLUE}Windows ${RED}run failed!${ENDCOLOR}"
            exit 1
        fi
    else
        echo -e "${BLUE}Windows ${RED}build failed!${ENDCOLOR}"
        exit 1
    fi
fi

if [[ ! -z $1 && $1 == "-a" ]] || [[ ! -z $1 && $1 == "--all" ]]
then
    gcc -c $(find . -name '*.c')
    if [ $? == 0 ]
    then
        rm Compiled/*.o
        mv *.o Compiled
        echo -e "${GREEN}Re-compilation successful!${ENDCOLOR}"
    else
        echo -e "${RED}Re-compilation failed!${ENDCOLOR}"
        rm *.o
        exit 1
    fi
else
    git diff --name-only | grep "\.c" 1> /dev/null
    if [ $? == 0 ]
    then
        gcc -c $(git diff --name-only | grep "\.c")
        if [ $? == 0 ]
        then
            mv *.o Compiled
            echo -e "${GREEN}Pre-compilation successful!${ENDCOLOR}"
        else
            echo -e "${RED}Pre-compilation failed!${ENDCOLOR}"
            rm *.o
            exit 1
        fi
    else
        echo -e "${GREEN}Pre-compilation skipped!${ENDCOLOR}"
    fi
fi

gcc -o Builds/Linux/bin.out Compiled/*.o -Wl,-rpath=. -LSlayEngineV1/Libraries/Linux -lfreetype -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lNeoTypes -lm
if [ $? == 0 ]
then
    echo -e "${GREEN}Compilation successful!${ENDCOLOR}"
    cd Builds/Linux
    ./bin.out
    if [ $? == 0 ]
    then
        echo -e "${GREEN}Run successful!${ENDCOLOR}"
        exit 0
    else
        echo -e "${RED}Run failed!${ENDCOLOR}"
        exit 1
    fi
else
    echo -e "${RED}Compilation failed!${ENDCOLOR}"
    exit 1
fi