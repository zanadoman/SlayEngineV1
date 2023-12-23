#!/bin/sh

RED="\e[91m"
GREEN="\e[92m"
BLUE="\e[94m"
ENDCOLOR="\e[0m"

if [[ ! -z $1 && $1 == "-w" ]] || [[ ! -z $1 && $1 == "--windows" ]]
then
    x86_64-w64-mingw32-gcc -o Windows/bin.exe $(find . -name '*.c') -LSlayEngineV1/Libraries/Windows -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpthread -lNeoTypes -lcJSON -lm
    if [ $? == 0 ]
    then
        echo -e "${BLUE}Windows ${GREEN}build successful!${ENDCOLOR}"
        exit 0
    else
        echo -e "${BLUE}Windows ${RED}build failed!${ENDCOLOR}"
        exit 1
    fi
fi

if [[ ! -z $1 && $1 == "-a" ]] || [[ ! -z $1 && $1 == "--all" ]]
then
    gcc -c $(find . -name '*.c')
    if [ $? != 0 ]
    then
        echo -e "${RED}Re-compilation failed!${ENDCOLOR}"
        rm *.o
        exit 1
    fi
    rm Compiled/*.o
    mv *.o Compiled
    echo -e "${GREEN}Re-compilation successful!${ENDCOLOR}"
else
    git diff --name-only | grep "\.c" 1> /dev/null
    if [ $? == 0 ]
    then
        gcc -c $(git diff --name-only | grep "\.c")
        if [ $? != 0 ]
        then
            echo -e "${RED}Pre-compilation failed!${ENDCOLOR}"
            rm *.o
            exit 1
        fi
        mv *.o Compiled
        echo -e "${GREEN}Pre-compilation successful!${ENDCOLOR}"
    else
        echo -e "${GREEN}Pre-compilation skipped!${ENDCOLOR}"
    fi
fi

gcc -o Linux/bin.out Compiled/*.o -Wl,-rpath=. -LSlayEngineV1/Libraries/Linux -lfreetype -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lNeoTypes -lcJSON -lm
if [ $? != 0 ]
then
    echo -e "${RED}Compilation failed!${ENDCOLOR}"
    exit 1
else
    echo -e "${GREEN}Compilation successful!${ENDCOLOR}"
fi

cd Linux
./bin.out
if [ $? == 0 ]
then
    echo -e "${GREEN}Run successful!${ENDCOLOR}"
    exit 0
else
    echo -e "${RED}Run failed!${ENDCOLOR}"
    exit 1
fi