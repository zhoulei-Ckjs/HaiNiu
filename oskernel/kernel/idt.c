#include "../include/linux/kernel.h"
#include "../include/linux/head.h"
void idt_init()
{
    printk("idt init...");
    interrupt_gate_t temp;
    return;
}