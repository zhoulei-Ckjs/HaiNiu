#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"

void kernel_main(void)
{
    console_init();

    char* s = "HaiNiu";

    printk("name: %s, age:%d\n", s, 6);

    while (true);
}