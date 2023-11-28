#!/bin/bash

TIMEFORMAT=%R
time gcc -o ./build/bin *.c SlayEngineV1/*.c SlayEngineV1/NeoTypes/*.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

if [ $? == 0 ]
then
    echo -e "Build successful!"
    ./build/bin

    if [ $? == 0 ]
    then
        echo "Run successful!"
        cp -r assets ./build
        exit 0
    fi
    
    echo "Run failed!"
    exit 1
fi

echo -e "Build failed!"
exit 1