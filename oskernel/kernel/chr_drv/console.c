#include "../../include/linux/tty.h"

#define MEM_BASE 0xB8000                            // 显卡内存起始位置

void console_clear()
{
    char *p = "[init::main.c] : in kernel_main ...";
    char* video = (char*)MEM_BASE + 80 * 2 * 2;       // 显示在第三行，0xb8000是显存和内存的映射位置，每行80字符，每个字符2字节
    while(*p != '\0')
    {
        *video = *p;
        ++video;
        *video = 12;
        ++video;
        p++;
    }
}

void console_init(void)
{
    console_clear();
}
