#!/bin/bash

function compile()
{
    git diff --name-only | grep .c 1> /dev/null
    if [ $? == 0 ]
    then
        cd Compiled
        gcc -c ../$(git diff --name-only | grep .c)
        if [ $? != 0 ]
        then
            echo "Pre-compilation failed!"
            exit 1
        fi
        cd ..
    else
        echo "Compilation skipped!"
        return 0;
    fi

    gcc -o Linux/bin Compiled/*.o -Wl,-rpath=. -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
    if [ $? != 0 ]
    then
        echo "Compilation failed!"
        exit 1
    fi

    echo "Compilation successful!"
    return 0
}

compile

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