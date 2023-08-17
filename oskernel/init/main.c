#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"

void kernel_main(void)
{
    console_init();

    printk("char is : %c", 'H');                // 打印一个字符

    while (true);
}