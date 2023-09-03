#include "../include/linux/kernel.h"
#include "../include/string.h"

int vsprintf(char *buf, const char *fmt, va_list args)
{
    char *  str;
    char *  s;
    int     len;
    int     i;

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
            case 's':
                s = va_arg(args, char *);
                len = strlen(s);                        // 遇到 '\0' 结束
                for (i = 0; i < len; ++i)
                    *str++ = *s++;
                break;
        }
    }
    *str = '\0';
    return str - buf;
}