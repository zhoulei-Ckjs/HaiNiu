#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"

void kernel_main(void)
{
    console_init();

    char* s = "HaiNiu";

    for (int i = 0; i < 10; ++i) {
        printk("name: %s, age:%d\n", s, i);
    }

    while (true);
}