; BIOS程序会将磁盘的第一个扇区的512字节加载到0x7c00处，为引导程序
[ORG  0x7c00]

; 代码段
[SECTION .text]
[BITS 16]           ; 编码方式
global _start       ; 声明一个全局函数
_start:
    ; 当值为3时，这个调用的功能是设置视频模式。具体来说，视频模式3对应于文本模式80列×25行，16色，8页。
    ; 这通常被认为是典型的DOS文本模式。
    xchg bx,bx
    mov ax, 3
    int 0x10        ;调用0x10号中断

    jmp     $       ;停在这里，看屏幕是否被clear

; 一个扇区要以0x55aa结尾，BIOS才能识别
times 510 - ($ - $$) db 0
db 0x55, 0xaa