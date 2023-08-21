#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"

void kernel_main(void)
{
    console_init();

    /* 测试 console_write */
    // 测试字符串输出
    char *p = "HaiNiu";
    console_write(p, 6);
    // 测试换行符
    p = "HaiNiu\n";                     // '\n'为转义字符，在内存中占一个字节，即 0A
    console_write(p, 7);
    // 测试超过字符自动换行
    p = "123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 1234567890";
    console_write(p, 90);

    /* 测试printk */
//    printk("char is : %c", 'H');                // 打印一个字符

    while (true);
}