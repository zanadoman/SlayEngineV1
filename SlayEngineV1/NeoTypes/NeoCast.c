#include "NeoTypes.h"

uint64 asInt(double Value)
{
    return *(uint64*)&Value;
}

double asDouble(uint64 Value)
{
    return *(double*)&Value;
}