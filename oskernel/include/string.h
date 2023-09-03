#ifndef HAINIU_STRING_H
#define HAINIU_STRING_H

#include "../include/linux/types.h"

/**
 * 计算字符串的长度，不算 '\0'
 * @param str 指针指向字符串
 * @return 字符串长度，不计算 '\0'
 */
size_t strlen(const char* str);

/**
 * 字符串拷贝函数
 * @param dest 目标地址
 * @param src  源地址
 * @param count 拷贝字符数
 * @return 目标地址
 */
void* memcpy(void* dest, const void* src, size_t count);

#endif //HAINIU_STRING_H
