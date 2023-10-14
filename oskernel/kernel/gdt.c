#include "../include/linux/kernel.h"
#include "../include/linux/head.h"
#include "../include/linux/types.h"

#define GDT_SIZE    256

/**
 * @brief 定义一个存储 gdt 信息的全局结构体
 */
xdt_ptr_t gdt_ptr;

/**
 * @brief 用于存储 gdt 表中每一个段描述符，每个描述符占 8 字符
 */
u64 gdt[GDT_SIZE] = {0};

void gdt_init()
{
    printk("init gdt...\n");
    __asm__ volatile ("sgdt gdt_ptr;");             // 加载 gdt 表信息，保存到 gdt_ptr 中
    memcpy(&gdt, gdt_ptr.base, gdt_ptr.limit);      // 拷贝 gdt 中段描述符出来
    gdt_item_t *item = &gdt[1];
    printk("%x\n", item->limit_low);            // 应该是 0xffff
    printk("%x\n", item->base_low);            // 应该是 0x0000
    printk("%x\n", item->base_low);            // 应该是 0x0000
    printk("%x\n", item->segment);              // 应该是 0x1
    printk("%x\n", item->DPL);                  // 应该是 0x0
    printk("%x\n", item->present);              // 应该是 0x1
}