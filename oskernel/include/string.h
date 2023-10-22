#ifndef HAINIU_STRING_H
#define HAINIU_STRING_H

#include "../include/linux/types.h"

/**
 * @brief 计算字符串的长度，不算 '\0'
 * @param str 指针指向字符串
 * @return 字符串长度，不计算 '\0'
 */
size_t strlen(const char* str);

/**
 * @brief 字符串拷贝函数
 * @param dest 目标地址
 * @param src  源地址
 * @param count 拷贝字符数
 * @return 目标地址
 */
void* memcpy(void* dest, const void* src, size_t count);

/**
 * @brief 将内存设定为指定的值
 * @param dest 目标内存
 * @param ch 要设定为的值
 * @param count 要设定的长度
 * @return 传递来的 dest
 */
void* memset(void* dest, int ch, size_t count);

#endif //HAINIU_STRING_H
