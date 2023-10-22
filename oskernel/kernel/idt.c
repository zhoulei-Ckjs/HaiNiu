#include "../include/linux/kernel.h"
#include "../include/linux/head.h"
#include "../include/string.h"
void idt_init()
{
    printk("idt init...");
    interrupt_gate_t temp;
    memset(&temp, 0, sizeof(temp));
    return;
}