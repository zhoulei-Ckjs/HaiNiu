dw 0x55aa
[SECTION .text]
[BITS 32]

extern kernel_main

global _start
_start:

    ; 修改栈顶
    mov esp, 0x9fbff

    ; 尝试访问1M以上的内存   0x100000
    ; 实模式下最高的地址总线20位，2^20 = 1M，不能访问超过1M的内存，但我们已经进入保护模式
    ; 至于为啥保护模式能够访问 2^32 = 4G空间，这个你要问CPU，因为在setup里面我们已经告诉CPU，开启保护模式
    mov byte [0x200000], 0x11
xchg bx, bx         ; -------------------------------------调试断点------------------------------------

    call kernel_main
    jmp $