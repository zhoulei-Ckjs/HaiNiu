#include "../include/linux/kernel.h"
#include "../include/linux/head.h"
#include "../include/string.h"

#define INTERRUPT_TABLE_SIZE    256         // 中断门个数

interrupt_gate_t interrupt_table[INTERRUPT_TABLE_SIZE] = {0};

extern void interrupt_handler();

void idt_init()
{
    for (int i = 0; i < INTERRUPT_TABLE_SIZE; ++i)
    {
        interrupt_gate_t* p = &interrupt_table[i];

        int handler = interrupt_handler;

        p->offset0 = handler & 0xffff;
        p->offset1 = (handler >> 16) & 0xffff;
        p->selector = 1 << 3; // 代码段
        p->reserved = 0;      // 保留不用
        p->type = 0b1110;     // 中断门
        p->segment = 0;       // 系统段
        p->DPL = 0;           // 内核态
        p->present = 1;       // 有效
    }
}