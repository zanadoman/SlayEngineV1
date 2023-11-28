#!/bin/bash

time gcc -o ./build/bin *.c SlayEngineV1/*.c SlayEngineV1/NeoTypes/*.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

if [ $? == 0 ]
then
    echo -e "\nBuild successful"
    ./build/bin

    if [ $? == 0 ]
    then
        echo "Run successful, copying assets"
        cp -r assets ./build
        echo "Assets copied"
        exit 0
    fi
    
    echo "Run failed"
    exit 1
fi

echo -e "\nBuild failed"
exit 1