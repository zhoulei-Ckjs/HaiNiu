dw 0x55aa
[SECTION .text]
[BITS 32]

global _start
_start:
xchg bx, bx         ; -------------------------------------调试断点------------------------------------
    jmp $