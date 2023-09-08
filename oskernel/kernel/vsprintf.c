#include "../include/linux/kernel.h"
#include "../include/string.h"

#define SIGN	2		        // 有符号
#define SMALL	64		        // 使用 'abcdef' 代替 'ABCDEF'

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
 * @param flag 一些标记，如是大写 16 进制还是小写 16 进制
 * @return 返回 原始传递的 buffer
 */
static char * number(char * str, int num, int base, int flags)
{
    const char *    digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";    // 更多进制使用，不局限于 16 进制
    int             i;
    char            tmp[36];
    char            sign;
    i = 0;

    if (flags & SMALL)
        digits = "0123456789abcdefghijklmnopqrstuvwxyz";                // 将大写换成小写的，这种常量字符串在内存只一份，是只读的

    if (flags & SIGN && num < 0)
    {
        sign='-';
        num = -num;
    }
    else
        sign = 0;

    if (sign)
        *str++ = sign;

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
    int     flags;                                      // 做各种标记用

    for (str = buf ; *fmt ; ++fmt)
    {
        if (*fmt != '%')
        {
            *str++ = *fmt;
            continue;
        }

        flags = 0;

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
            case 'x':
                flags |= SMALL;                             // 小写 16 进制
            case 'X':
                str = number(str, va_arg(args, unsigned long), 16, flags);
                break;
            // 整数
            case 'd':
                flags |= SIGN;
            // unsigned
            case 'u':
                str = number(str, va_arg(args, unsigned long), 10, flags);
                break;
        }
    }
    *str = '\0';
    return str - buf;
}