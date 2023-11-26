#!/bin/bash

gcc -o ./build/bin *.c SlayEngineV1/*.c SlayEngineV1/NeoTypes/*.c -lSDL2 -lSDL2_image -lm && ./build/bin