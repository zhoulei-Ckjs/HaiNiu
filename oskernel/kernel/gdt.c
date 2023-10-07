#include "../include/linux/kernel.h"
#include "../include/linux/head.h"

/**
 * @brief 定义一个存储 gdt 信息的全局结构体
 */
xdt_ptr_t gdt_ptr;

void gdt_init()
{
    printk("init gdt...\n");
    printk("%d\n", gdt_ptr.limit);
    printk("%d\n", gdt_ptr.base);
    __asm__ volatile ("sgdt gdt_ptr;");             // 加载 gdt 表信息，保存到 gdt_ptr 中
    printk("%d\n", gdt_ptr.limit);
    printk("%d\n", gdt_ptr.base);
}