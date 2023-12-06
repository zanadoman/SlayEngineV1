#!/bin/bash

TIMEFORMAT=%R
time gcc -o Linux/bin *.c SlayEngineV1/*.o SlayEngineV1/NeoTypes/*.o -Wl,-rpath=. -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

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