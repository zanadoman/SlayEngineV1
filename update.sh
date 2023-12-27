#!/bin/sh

RED="\e[91m"
GREEN="\e[92m"
BLUE="\e[94m"
ENDCOLOR="\e[0m"

echo "Updating NeoTypes"

echo -e "${BLUE}NeoTypes.h${ENDCOLOR}"
curl -s "https://raw.githubusercontent.com/zanadoman/NeoTypes/main/Source/NeoTypes.h" -o SlayEngineV1/Includes/NeoTypes.h
if [ $? == 0 ]
then
    echo -e "${GREEN}NeoTypes.h updated!${ENDCOLOR}"
else
    echo -e "${RED}NeoTypes.h update failed!${ENDCOLOR}"
fi

echo -e "${BLUE}libNeoTypes.a (Linux)${ENDCOLOR}"
curl -s "https://raw.githubusercontent.com/zanadoman/NeoTypes/main/Linux%20(x86_64)/libNeoTypes.a" -o SlayEngineV1/Libraries/Linux/libNeoTypes.a
if [ $? == 0 ]
then
    echo -e "${GREEN}libNeoTypes.a (Linux) updated!${ENDCOLOR}"
else
    echo -e "${RED}libNeoTypes.a update (Linux) failed!${ENDCOLOR}"
fi

echo -e "${BLUE}libNeoTypes.a (Windows)${ENDCOLOR}"
curl -s "https://raw.githubusercontent.com/zanadoman/NeoTypes/main/Windows%20(x86_64)/libNeoTypes.a" -o SlayEngineV1/Libraries/Windows/libNeoTypes.a
if [ $? == 0 ]
then
    echo -e "${GREEN}libNeoTypes.a (Windows) updated!${ENDCOLOR}"
else
    echo -e "${RED}libNeoTypes.a (Windows) update failed!${ENDCOLOR}"
fi