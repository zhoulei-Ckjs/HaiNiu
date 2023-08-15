#ifndef HAINIU_KERNEL_H
#define HAINIU_KERNEL_H

#include "../stdarg.h"

/**
 * 内核打印函数
 * @param fmt 打印格式
 * @param ... 可变参
 * @return
 */
int printk(const char * fmt, ...);

/**
 * 组装字符串函数
 * @param buf   格式化字符串存储的内存地址
 * @param fmt   格式
 * @param args  格式的参数
 * @return      字符串总长度
 */
int vsprintf(char *buf, const char *fmt, va_list args);

#endif //HAINIU_KERNEL_H
