#include "../include/linux/kernel.h"

int vsprintf(char *buf, const char *fmt, va_list args)
{
    char *  str;

    for (str = buf ; *fmt ; ++fmt)
    {
        if (*fmt != '%')
        {
            *str++ = *fmt;
            continue;
        }

        ++fmt;                                          // 跳过 '%'

        switch (*fmt)
        {
            // char 字符
            case 'c':
                *str++ = (unsigned char) va_arg(args, int); // 输出字符
                break;
        }
    }
    *str = '\0';
    return str - buf;
}