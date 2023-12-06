#!/bin/bash

function compile()
{
    cd Compiled
    gcc -c ../$(git diff --name-only | grep .c)
    if [ $? != 0 ]
    then
        echo "Pre-compilation failed!"
        exit 1
    fi
    cd ..

    gcc -o Linux/bin Compiled/*.o SlayEngineV1/NeoTypes/*.o -Wl,-rpath=. -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
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