#include "../../include/linux/kernel.h"
#include "../../include/asm/io.h"

/// 键盘中断处理函数
void keymap_handler(int idt_index)
{
    char scancode = in_byte(0x60);             ///< 0x60端口是用于接收键盘数据的输入端口

    char ch = scancode;
    printk("%c\n", ch);
}
