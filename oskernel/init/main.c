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
    // 让换行 '\n' 能够定位到行首测试
    p = "\nabcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ";
    console_write(p, 54);
    // 测试 '\0' 作为字符串结尾
    p = "\n123456789\0""123";                 // 编译器识别为 123456789 \0 123
    console_write(p, 14);
    // 这里会有一个bug，就是遇到\0不退出，但这并不一定认为是bug，暂且看printk有没有这个bug，因为printk是对console_write的封装
    // 测试 '\a' '\t' '\v' , 默认不处理
    p = "\n1234\a56\t78\v9123";
    console_write(p, 16);
    // '\b' 退格符的测试
    p = "\n123a\b456789\n";
    console_write(p, 13);
    // '\r' 回车符测试
    p = "123456789";
    console_write(p, 9);
    p = "\rabcdefghi\n";
    console_write(p, 11);
    // delete键测试
    char p1[10] = {'1', '2', '3','4', '5', 0x7f, '6', '7', '8', '9' };
    console_write(p1, 10);
    // 测试滚屏功能
    p = "\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\nm\nn\no\np\nq\nr\ns\nt\nu\nv\nw\nx\ny\nz\n"
        "jfdlkslaljfkldjsalkfjdoisajflkjdsalkjfdklsjaklfjlsdkajfkljdsalkjfkldsjalkjfldksa"
        "jfkljhdslklaljflksdjakfjdskla\n";
    console_write(p, 163);

    /* 测试printk */
//    printk("char is : %c", 'H');                // 打印一个字符
// 测试 '\0' 作为字符串结尾
//    p = "\n123456789\0""123";                 // 编译器识别为 123456789 \0 123
//    printk("%s", p);

    while (true);
}