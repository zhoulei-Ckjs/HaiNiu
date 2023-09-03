#include "../include/linux/kernel.h"

static char buf[1024];
/**
 * 依据压栈规则，栈中数据如下：
 * 如 printk("%s", "123456")         "123456" 是定义了字符串常量，并返回地址
 * 高地址          stack                        指向的数据
 *  |       |       p       |       ->          "123456"        // 存储的是指针，指针指向 “123456” 的常量
 *  |       |      fmt      |       ->          "%s"            // 存储的是指针，指向字符串常量 "%s"
 * \/       |    返回地址    |
 * 低地址
 */
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