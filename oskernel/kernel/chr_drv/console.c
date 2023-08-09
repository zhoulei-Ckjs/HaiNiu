#include "../../include/linux/tty.h"

#define MEM_BASE 0xB8000                            // 显卡内存起始位置
#define MEM_SIZE 0x4000                             // 显卡内存大小
#define MEM_END (MEM_BASE + MEM_SIZE)               // 显卡内存结束位置

static uint screen;                                 // 当前显示器开始的内存位置
static uint pos;                                    // 记录当前光标的内存位置
static uint x, y;                                   // 当前光标的坐标

/**
 * 清屏，实际上是往0xb8000的内存位置写空格，写满就是清屏
 */
void console_clear()
{
    screen = MEM_BASE;
    pos = MEM_BASE;
    x = y = 0;

    u16 *ptr = (u16 *)MEM_BASE;
    while (ptr < MEM_END)
    {
        *ptr++ = 0x0720;
    }
}

void console_init(void)
{
    console_clear();
}
