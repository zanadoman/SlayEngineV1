#!/bin/bash

projectdir="$(pwd)"

if [[ ! -z $1 && $1 == "-a" ]] || [[ ! -z $1 && $1 == "--all" ]]
then
    rm Compiled/*.o
    gcc -c Demo/*.c Demo/Actors/*.c Demo/Scenes/*.c SlayEngineV1/*.c SlayEngineV1/NeoTypes/*.c
    if [ $? != 0 ]
    then
        echo "Re-compilation failed!"
        rm *.o
        exit 1
    fi
    mv *.o Compiled
    echo "Re-compilation successful!"
else
    git diff --name-only | grep "\.c" 1> /dev/null
    if [ $? == 0 ]
    then
        gcc -c $(git diff --name-only | grep "\.c")
        if [ $? != 0 ]
        then
            echo "Pre-compilation failed!"
            exit 1
        fi
        mv *.o Compiled
        echo "Pre-compilation successful!"
    else
        echo "Pre-compilation skipped!"
    fi
fi

gcc -o Linux/bin Compiled/*.o -Wl,-rpath=. -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
if [ $? != 0 ]
then
    echo "Compilation failed!"
    exit 1
else
    echo "Compilation successful!"
fi

cd Linux
./bin
if [ $? == 0 ]
then
    echo "Run successful!"
    exit 0
else
    echo "Run failed!"
    exit 1
fi