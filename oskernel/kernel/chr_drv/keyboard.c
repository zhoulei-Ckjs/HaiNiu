#include "../../include/linux/kernel.h"
#include "../../include/asm/io.h"
#include "../../include/linux/types.h"

/**
 * 一个按键按下会触发中断两次
 * 按下返回的码叫通码 make code
 * 弹起返回的码叫断码 break code
 *
 * 断码 = 通码 | 8
 */

/// 键盘中断处理函数
void keymap_handler(int idt_index)
{
    uchar scancode = in_byte(0x60);             ///< 0x60端口是用于接收键盘数据的输入端口

    char ch = 'a';                                  ///< 这里一次按键会打印两次 a，通码一次，断码一次
    printk("%c\n", ch);
}
