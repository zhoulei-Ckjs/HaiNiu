#ifndef HAINIU_TRAPS_H
#define HAINIU_TRAPS_H

/**
 * @brief 初始化 gdt 表
 */
void gdt_init();

/**
 * @brief 初始化中断向量表 idt
 */
void idt_init();

#endif //HAINIU_TRAPS_H
