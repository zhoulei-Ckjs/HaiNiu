#ifndef HAINIU_IO_H
#define HAINIU_IO_H

/**
 * @brief 从指定端口接收一个字节的数据
 * @param port  端口
 */
char in_byte(int port);

/**
 * 向指定端口发送一个字节的数据
 * @param port  端口
 * @param v     要发送的值
 */
void out_byte(int port, int v);

#endif //HAINIU_IO_H
