#ifndef HAINIU_TTY_H
#define HAINIU_TTY_H

#include "types.h"

/**
 * 初始化控制台
 */
void console_init(void);

/**
 * 控制台往屏幕输出数据
 * @param buf   要输出的内容
 * @param count 要输出内容的长度
 */
void console_write(char *buf, u32 count);

#endif //HAINIU_TTY_H
