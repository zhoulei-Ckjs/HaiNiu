#include "../include/linux/kernel.h"

static char buf[1024];
int printk(const char * fmt, ...)
{
    va_list args;                       //处理可变参，待实现
    int i;
    i = vsprintf(buf, fmt, args);
    console_write(buf, i);
    return i;
}