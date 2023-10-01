#include "../include/linux/kernel.h"
#include "../include/string.h"

/**
 * 检测是否是数字
 */
#define is_digit(c)	((c) >= '0' && (c) <= '9')

#define ZEROPAD	1		        // 补零操作
#define SIGN	2		        // 有符号
#define PLUS	4		        // 输出带 + 的数
#define SPACE	8		        // 空格
#define LEFT	16		        // 左对齐
#define SPECIAL	32		        // 输出带有0x前缀的
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
static char * number(char * str, int num, int base, int flags, int size)
{
    const char *    digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";    // 更多进制使用，不局限于 16 进制
    int             i = 0;
    char            tmp[36];
    char            sign;
    char            c;

    if (flags & SMALL)
        digits = "0123456789abcdefghijklmnopqrstuvwxyz";                // 将大写换成小写的，这种常量字符串在内存只一份，是只读的
    if (flags & LEFT)                                                   // 左对齐的话去掉补零操作
        flags &= ~ZEROPAD;

    c = (flags & ZEROPAD) ? '0' : ' ' ;

    if (flags & SIGN && num < 0)
    {
        sign = '-';
        num = -num;
    }
    else
        sign = (flags & PLUS) ? '+' : ((flags & SPACE) ? ' ' : 0);

    if (sign)
        size--;                                                         // 如果是有符号的负值，则 '-' 占一个位置

    if (flags & SPECIAL)
    {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }

    if (num == 0)
        tmp[i++]='0';
    else while (num != 0)
            tmp[i++] = digits[do_div(num, base)];

    size -= i;                                                          // 右对齐，将要打印的字符去掉，前面打印空格

    if (!(flags & LEFT))
        while(size-- > 0)                                               // 前面打印空格 或 0
            *str++ = c;

    if (sign)
        *str++ = sign;

    if (flags & SPECIAL)                                                 // 打印 0x 前缀
    {
        if (base == 8)
            *str++ = '0';
        else if (base == 16)
        {
            *str++ = '0';
            *str++ = digits[33];
        }
    }

    while(i-->0)
        *str++ = tmp[i];
    while(size-- > 0)
        *str++ = ' ';
    return str;
}

/**
 * 略过字符串中数字的部分
 * @param s 这里传递二级指针，用于改变一级指针指向的位置
 * @return 字符串中整数值
 */
static int skip_atoi(const char **s)
{
    int num = 0;
    while (is_digit(**s))
        num = num * 10 + *((*s)++) - '0';
    return num;
}

int vsprintf(char *buf, const char *fmt, va_list args)
{
    char *  str;
    char *  s;
    int     len;
    int     i;
    int     flags;                                      // 做各种标记用
    int *   ip;                                         // int 型指针
    int     field_width;	                            // 打印宽度

    for (str = buf ; *fmt ; ++fmt)
    {
        if (*fmt != '%')
        {
            *str++ = *fmt;
            continue;
        }

        flags = 0;

repeat:
        ++fmt;                                          // 跳过 '%'
        switch (*fmt)
        {
            case '-':
                flags |= LEFT;
                goto repeat;
            case '0':
                flags |= ZEROPAD;
                goto repeat;
            case '+':
                flags |= PLUS;
                goto repeat;
            case ' ':
                flags |= SPACE;
                goto repeat;
            case '#':
                flags |= SPECIAL;
                goto repeat;
        }

        field_width = -1;                               // 宽度初始化
        if (is_digit(*fmt))
            field_width = skip_atoi(&fmt);
        else if (*fmt == '*')
        {
            /* 宽度为下一个参数 */
            field_width = va_arg(args, int);
            fmt++;
        }

        switch (*fmt)
        {
            // char 字符
            case 'c':
                if (!(flags & LEFT))
                    while (--field_width > 0)
                        *str++ = ' ';
                *str++ = (unsigned char) va_arg(args, int); // 输出字符
                while (--field_width > 0)                   // 用空格补齐宽度
                    *str++ = ' ';
                break;
            // 字符串
            case 's':
                if (!(flags & LEFT))
                    while (len < field_width--)
                        *str++ = ' ';
                s = va_arg(args, char *);
                len = strlen(s);                        // 遇到 '\0' 结束
                for (i = 0; i < len; ++i)
                    *str++ = *s++;
                while (len < field_width--)
                    *str++ = ' ';
                break;
            // 八进制
            case 'o':
                str = number(str, va_arg(args, unsigned long), 8, flags, field_width);
                break;
            // 以十六进制的形式输出指针类型的内容
            case 'p':
                str = number(str,  (unsigned long) va_arg(args, void *), 16, flags, field_width);
                break;
            // 十六进制
            case 'x':
                flags |= SMALL;                             // 小写 16 进制
            case 'X':
                str = number(str, va_arg(args, unsigned long), 16, flags, field_width);
                break;
            // 整数
            case 'd':
            case 'i':
                flags |= SIGN;
            // unsigned
            case 'u':
                str = number(str, va_arg(args, unsigned long), 10, flags, field_width);
                break;
            // 打印已经输出的字符数量
            case 'n':
                ip = va_arg(args, int *);
                *ip = (str - buf);
                break;
            // '%' 后面不是标准操作时的处理，如输出 "%a" 等
            default:
                if (*fmt != '%')
                    *str++ = '%';
                if (*fmt)
                {
                    *str++ = *fmt;
                    if(*fmt == '%')
                        --fmt;
                }
                else                // 当前字符为 '\0'，--fmt ，default 结束后会进入下一次 for 循环，++fmt
                    --fmt;          // 先--，for循环又++，for 循环中间的判断 *fmt，故而结束 for 循环，不会输出 '\0' 之后的内容
                break;
        }
    }
    *str = '\0';
    return str - buf;
}