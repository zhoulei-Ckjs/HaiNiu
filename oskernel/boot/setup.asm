; 0柱面0磁道2扇區
[ORG 0x500]         ;将setup放到0x500处

[SECTION .text]
[BITS 16]
global _start
_start:
    ; 清空所有寄存器
    mov     ax, 0
    mov     ss, ax
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     si, ax

    mov     si, msg
    call    print

    jmp     $       ; 停在这里

; 如何调用
; mov     si, msg   ; 1 传入字符串
; call    print     ; 2 调用
print:
    mov ah, 0x0e    ; 指定要使用的功能是0x0e，0x0E表示在TTY模式下写字符
    mov bh, 0       ; 表示在第0个页面输出字符
    mov bl, 0x01    ; 用于指定颜色，蓝色
.loop:
    mov al, [si]    ; 要输出的字符
    cmp al, 0       ; 字符串不结束就一直打印
    jz .done
    int 0x10        ; 调用bios的10号中断

    inc si
    jmp .loop
.done:
    ret

; 定义一个hello world字符串
msg:
    db "hello, world", 10, 13, 0