#include "../include/linux/kernel.h"
#include "../include/string.h"

/**
 * 内联汇编，做除法运算
 */
#define do_div(n, base) ({ \
int __res; \
__asm__("div %4":"=a" (n),"=d" (__res):"0" (n),"1" (0), "r" (base)); \
__res; })

/**
 *
 * @param str 转换后数据所保存的位置
 * @param num 需要转换的数据
 * @param base 进制数
 * @return 返回 原始传递的 buffer
 */
static char * number(char * str, int num, int base)
{
    const char *    digits = "0123456789";
    int             i;
    char            tmp[36];
    i = 0;
    if (num==0)
        tmp[i++]='0';
    else while (num != 0)
            tmp[i++] = digits[do_div(num, base)];

    while(i-->0)
        *str++ = tmp[i];
    return str;
}

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
            // 字符串
            case 's':
                s = va_arg(args, char *);
                len = strlen(s);                        // 遇到 '\0' 结束
                for (i = 0; i < len; ++i)
                    *str++ = *s++;
                break;
            // 十六进制
            case 'X':
                str = number(str, va_arg(args, unsigned long), 16);
                break;
            // 整数
            case 'd':
                str = number(str, va_arg(args, unsigned long), 10);
                break;
        }
    }
    *str = '\0';
    return str - buf;
}