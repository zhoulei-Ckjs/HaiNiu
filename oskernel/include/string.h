#ifndef HAINIU_STRING_H
#define HAINIU_STRING_H

#include "../include/linux/types.h"

/**
 * 字符串拷贝函数
 * @param dest 目标地址
 * @param src  源地址
 * @param count 拷贝字符数
 * @return 目标地址
 */
void* memcpy(void* dest, const void* src, size_t count);

#endif //HAINIU_STRING_H
