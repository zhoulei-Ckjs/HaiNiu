#include "../../include/asm/io.h"
#include "../../include/linux/tty.h"

/**
 * 索引寄存器，一般用法：
 *  1. 往 0x3D4 发送一个值（这个值是协议规定，你要做什么操作就发送什么值）
 *  2. 有相应操作了，就可以操作 0x3D5 了，如果是读取数据就从 0x3D5 读取数据，是写入就往 0x3D5 写数据
 */
#define CRT_ADDR_REG 0x3D4                          // CRT(6845)索引寄存器
#define CRT_DATA_REG 0x3D5                          // CRT(6845)数据寄存器

/**
 * 根据 CRT 芯片的规格和文档：
 *      往 0x3D4 发送 0xE 表示要操作光标高位
 *      往 0x3D4 发送 0xF 表示要操作光标低位
 */
#define CRT_CURSOR_H 0xE                            // 光标位置 - 高位
#define CRT_CURSOR_L 0xF                            // 光标位置 - 低位

/**
 * 根据 CRT 芯片的规格和文档：
 *      往 0x3D4 发送 0xC 表示要操作显示起始位置的高位
 *      往 0x3D4 发送 0xD 表示要操作显示起始位置的低位
 */
#define CRT_START_ADDR_H 0xC                        // 显示内存起始位置 - 高位
#define CRT_START_ADDR_L 0xD                        // 显示内存起始位置 - 低位

#define MEM_BASE 0xB8000                            // 显卡内存起始位置
#define MEM_SIZE 0x4000                             // 显卡内存大小
#define MEM_END (MEM_BASE + MEM_SIZE)               // 显卡内存结束位置

static uint screen;                                 // 当前显示器开始的内存位置
static uint pos;                                    // 记录当前光标的内存位置
static uint x, y;                                   // 当前光标的坐标

/**
 * 将光标设定为当前 pos 所指向的位置
 */
static void set_cursor()
{
    out_byte(CRT_ADDR_REG, CRT_CURSOR_H);                           // 要操作光标高位
    out_byte(CRT_DATA_REG, ((pos - MEM_BASE) >> 9) & 0xff);         // 往光标高位写数据
    // 当前位置 - 0xb8000（首地址）右移 9 位
    // 右移 9 位是因为低位占8位，而屏幕上的每一个字符都占2位，即右移8位再除以2，即右移9位
    out_byte(CRT_ADDR_REG, CRT_CURSOR_L);                           // 要操作光标低位
    out_byte(CRT_DATA_REG, ((pos - MEM_BASE) >> 1) & 0xff);         // 往光标低位写数据
}

/**
 * 设置显示器显示的起始位置
 *      因为0xb8000到0xc000都是显存的位置，怎么让显示器从固定的内存位置显示开始显示呢？
 *      这个函数完成此功能
 */
static void set_screen()
{
    out_byte(CRT_ADDR_REG, CRT_START_ADDR_H);                       // 要操作显示起始位置的高位
    out_byte(CRT_DATA_REG, ((screen - MEM_BASE) >> 9) & 0xff);      // 往要显示起始位置的高位写数据
    // 当前位置 - 0xb8000（首地址）右移 9 位
    // 右移 9 位是因为低位占8位，而屏幕上的每一个字符都占2位，即右移8位再除以2，即右移9位
    out_byte(CRT_ADDR_REG, CRT_START_ADDR_L);                       // 要操作显示起始位置的低位
    out_byte(CRT_DATA_REG, ((screen - MEM_BASE) >> 1) & 0xff);      // 往要显示起始位置的低位写数据
}

/**
 * 清屏，实际上是往0xb8000的内存位置写空格，写满就是清屏
 */
void console_clear()
{
    screen = MEM_BASE;
    pos = MEM_BASE;
    x = y = 0;

    set_cursor();                   // 设置光标位置
    set_screen();

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
