#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"
#include "../include/string.h"

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

    // 测试 memcpy 函数
    p = "abcde\n";
    memcpy(p1, p, 6);
    console_write(p1, 6);
    // 测试 '\f' 滚动一行
    p = "12345\f67890\f";
    console_write(p, 12);

    // 测试 strlen
    size_t  size = strlen(p);

    /* 测试printk */
    printk("char is : %c", 'H');                // 打印一个字符
    // 测试 '\0' 作为字符串结尾
    p = "\n123456789\0""123";                 // 编译器识别为 123456789 \0 123
    printk("%s", p);
    // 测试 '%d'
    p = "\nhainiu";
    printk("%s,%d", p, 10);
    // 测试 '%x'
    printk("%s,%d,%X", p, 10, 16);
    printk("%s,%d,%X", p, 10, 255);
    // 测试 '%x'
    printk("%s,%d,%X,%x", p, 10, 255, 254);
    printk("%s,%d,%X,%x,%u", p, 0xffffffff, 255, 254,0xffffffff);
    // 测试 '%o' 八进制
    printk("\n%o\n", 16);
    // 测试 '%p' 以十六进制的形式输出指针类型的内容
    printk("%p\n", p);
    // 测试 '%n' , 统计输出了多少字符
    int count = 0;
    p = "123456";
    printk("%s %n\n", p, &count);
    printk("%d\n", count);
    // 测试非标准输出
    printk("%a\n");
    printk("%a%%d%t\n",6);
    printk("%%\n");
    printk("%%d\n", 3);
    printk("%%%s\n", p);
    printk("%\0%s\n", p);
    printk("%\0%s\n", p);
    // 测试输出宽度
    printk("\n------\n");
    printk("%16c~\n", 64);
    printk("%16s~\n", p);
    printk("%16o~\n", 16);
    printk("%16p~\n", p);
    printk("%16X~\n", 255);
    printk("%16x~\n", 255);
    printk("%16d~\n", 10);
    printk("%16i~\n", 10);
    printk("%16u~\n", -1);
    printk("%*u~\n", 32, -1);
    // 测试左对齐
    printk("\n------\n");
    printk("%-16c~\n", 64);
    printk("%-16s~\n", p);
    printk("%-16o~\n", 16);
    printk("%-16p~\n", p);
    printk("%-16X~\n", 255);
    printk("%-16x~\n", 255);
    printk("%-16d~\n", 10);
    printk("%-16i~\n", 10);
    printk("%-16u~\n", -1);
    printk("%-*u~\n", 32, -1);

    // 测试补零操作
    printk("\n------\n");
    printk("%016c~\n", 64);
    printk("%-016s~\n", p);
    printk("%016o~\n", 16);
    printk("%016p~\n", p);
    printk("%016X~\n", 255);
    printk("%016x~\n", 255);
    printk("%016d~\n", 10);
    printk("%016i~\n", 10);
    printk("%016u~\n", -1);
    printk("%0*u~\n", 32, -1);

    // 测试带 '+' 的输出
    printk("\n------\n");
    printk("%+16d~\n", 64);
    // 测试 ' '
    printk("\n------\n");
    printk("% 16d~\n", 64);

    // 测试前缀 0x
    printk("\n------0x------\n");
    printk("% #16x~\n", 64);
    printk("% #16X~\n", 64);

    // 测试前缀 0
    printk("\n------0------\n");
    printk("% #16o~\n", 64);

    // 测试 %*
    printk("\n------%*------\n");               // 这里没有打印出*，暂时不管了
    printk("%*u~\n", 32, -1);
    printk("%*d~\n", 32, -1);
    printk("%*o~\n", 32, -1);
    printk("%*x~\n", 32, -1);
    printk("%*X~\n", 32, -1);
    printk("%*u~\n", -32, -1);
    printk("%*d~\n", -32, -1);
    printk("%*o~\n", -32, -1);
    printk("%*x~\n", -32, -1);
    printk("%*X~\n", -32, -1);

    // 测试 %p，应该输出 000 前缀
    printk("\n------------\n");
    printk("%p~\n", p);

    // 测试精度
    printk("%16.10d~\n", 33);
    printk("%.2s~\n", p);

    while (true);
}