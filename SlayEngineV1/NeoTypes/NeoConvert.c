#include "NeoTypes.h"

uint64 STRtoUINT(char* Characters, boolean* Success)
{
    uint64 result;

    result = 0;
    for (uint64 i = 0; i < strLength(Characters) - 1; i++)
    {
        if ((Characters[i] < '0' || '9' < Characters[i]))
        {
            if (Success != NULL)
            {
                *Success = false;
            }
            return 0;
        }
        result += (Characters[i] - '0') * pow(10, strLength(Characters) - 2 - i);
    }

    if (Success != NULL)
    {
        *Success = true;
    }

    return result;
}
uint16 UINTtoSTR(uint64 Number, string String)
{
    uint64 i;

    free(String->String);
    String->String = malloc(sizeof(char) * 1);
    if (String->String == NULL)
    {
        String->Lenght = 0;
        return 1;
    }
    String->String[0] = '\0';
    String->Lenght = 1;

    for (i = 1; Number / i > 10; i *= 10);
    for (; i > 0; i /= 10)
    {
        strAppend(String, Number / i + '0');
        Number %= i;
    }

    return 0;
}

//######################################################################################

sint64 STRtoSINT(char* Characters, boolean* Success)
{
    sint64 result;

    result = 0;
    for (uint64 i = 1; i < strLength(Characters) - 1; i++)
    {
        if ((Characters[i] < '0' || '9' < Characters[i]))
        {
            if (Success != NULL)
            {
                *Success = false;
            }
            return 0;
        }
        result += (Characters[i] - '0') * pow(10, strLength(Characters) - 2 - i);
    }

    if (Characters[0] == '-')
    {
        result *= -1;
    }
    else
    {
        if ((Characters[0] < '0' || '9' < Characters[0]))
        {
            if (Success != NULL)
            {
                *Success = false;
            }
            return 0;
        }
        result += (Characters[0] - '0') * pow(10, strLength(Characters) - 2);
    }

    if (Success != NULL)
    {
        *Success = true;
    }

    return result;
}
uint16 SINTtoSTR(sint64 Number, string String)
{
    uint64 i;

    free(String->String);
    String->String = malloc(sizeof(char) * 1);
    if (String->String == NULL)
    {
        String->Lenght = 0;
        return 1;
    }
    String->String[0] = '\0';
    String->Lenght = 1;

    if (Number < 0)
    {
        Number *= -1;
        strAppend(String, '-');
    }

    for (i = 1; Number / i > 10; i *= 10);
    for (; i > 0; i /= 10)
    {
        strAppend(String, Number / i + '0');
        Number %= i;
    }

    return 0;
}

//######################################################################################

double STRtoDOUBLE(char* Characters, boolean* Success)
{
    double result;

    uint64 decimal;

    decimal = strLength(Characters) - 1;
    for (uint64 i = 0; i < strLength(Characters) - 1; i++)
    {
        if (Characters[i] == '.' || Characters[i] == ',')
        {
            decimal = i;
            break;
        }
    }

    result = 0;
    for (uint64 i = 1; i < decimal; i++)
    {
        if ((Characters[i] < '0' || '9' < Characters[i]))
        {
            if (Success != NULL)
            {
                *Success = false;
            }
            return 0;
        }
        result += (Characters[i] - '0') * pow(10, decimal - 1 - i);
    }
    for (uint64 i = decimal + 1; i < strLength(Characters) - 1; i++)
    {
        if ((Characters[i] < '0' || '9' < Characters[i]))
        {
            if (Success != NULL)
            {
                *Success = false;
            }
            return 0;
        }
        result += (Characters[i] - '0') * 1 / pow(10, i - decimal);
    }

    if (Characters[0] == '-')
    {
        result *= -1;
    }
    else
    {
        if ((Characters[0] < '0' || '9' < Characters[0]))
        {
            if (Success != NULL)
            {
                *Success = false;
            }
            return 0;
        }
        result += (Characters[0] - '0') * pow(10, decimal - 1);
    }

    if (Success != NULL)
    {
        *Success = true;
    }

    return result;
}
uint16 DOUBLEtoSTR(double Number, string String)
{
    uint64 i, whole;
    double fraction;

    free(String->String);
    String->String = malloc(sizeof(char) * 1);
    if (String->String == NULL)
    {
        String->Lenght = 0;
        return 1;
    }
    String->String[0] = '\0';
    String->Lenght = 1;

    if (Number < 0)
    {
        Number *= -1;
        strAppend(String, '-');
    }

    whole = (uint64)trunc(Number);
    fraction = Number - trunc(Number);

    for (i = 1; whole / i > 10; i *= 10);
    for (; i > 0; i /= 10)
    {
        strAppend(String, whole / i + '0');
        whole %= i;
    }
    if (fraction > 0)
    {
        strAppend(String, '.');

        for (; fraction - trunc(fraction) > 0; fraction *= 10);

        for (i = 1; (uint64)round(fraction) / i > 10; i *= 10);
        for (; i > 0; i /= 10)
        {
            strAppend(String, (uint64)round(fraction) / i + '0');
            fraction = (uint64)round(fraction) % i;
        }
    }

    return 0;
}