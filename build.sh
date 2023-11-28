#!/bin/bash

TIMEFORMAT=%R
buildtime=$(time (gcc -o ./build/bin *.c SlayEngineV1/*.c SlayEngineV1/NeoTypes/*.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm) 2>&1 1>/dev/null)

if [ $? == 0 ]
then
    echo -e "Build successful ${buildtime}"
    ./build/bin

    if [ $? == 0 ]
    then
        echo "Run successful, copying assets"
        cp -r assets ./build
        exit 0
    fi
    
    echo "Run failed"
    exit 1
fi

echo -e "Build failed"
exit 1