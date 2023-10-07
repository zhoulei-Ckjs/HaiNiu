#ifndef HAINIU_HEAD_H
#define HAINIU_HEAD_H

/**
 * @brief 定义存储 gdt 信息的结构体
 */
#pragma pack(2)
typedef struct xdt_ptr_t
{
    short   limit;
    int     base;    // 这个base需要大端存储，默认是小端存储
} xdt_ptr_t;
#pragma pack()

#endif //HAINIU_HEAD_H
