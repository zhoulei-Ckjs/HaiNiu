#include "../../include/linux/kernel.h"

/// 键盘中断处理函数
void keymap_handler(int idt_index)
{
    char ch = '0';
    printk("%c\n", ch);
}
