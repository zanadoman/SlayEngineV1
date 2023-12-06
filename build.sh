#!/bin/bash

function compile()
{
    cd Compiled
    gcc -c ../$(git diff --name-only)
    if [ $? != 0 ]
    then
        return 1
    fi
    cd ..

    gcc -o Linux/bin Compiled/*.o SlayEngineV1/NeoTypes/*.o -Wl,-rpath=. -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm
    if [ $? != 0 ]
    then
        return 1
    fi

    return 0
}

TIMEFORMAT=%R
time compile

if [ $? == 0 ]
then
    echo -e "Build successful!"
    cd Linux
    ./bin

    if [ $? == 0 ]
    then
        echo "Run successful!"
        exit 0
    fi
    
    echo "Run failed!"
    exit 1
fi

echo -e "Build failed!"
exit 1