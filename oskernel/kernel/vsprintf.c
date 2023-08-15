#include "../include/linux/kernel.h"

int vsprintf(char *buf, const char *fmt, va_list args)
{
    for(int i = 0; i < 10; i++)
        *(buf + i) = i;
    return 10;
}