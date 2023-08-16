#include "../include/linux/kernel.h"

static char buf[1024];
int printk(const char * fmt, ...)
{
    // 用 p 代表指针，因为 va_list 就是用指针实现的
    va_list p;                       // 使用 va_list
    int i;

    va_start(p, fmt);                // 可变参开始

    i = vsprintf(buf, fmt, p);

    va_end(p);                       // 可变参结束

    console_write(buf, i);
    return i;
}