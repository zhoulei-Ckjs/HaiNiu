; 0柱面0磁道2扇區
[ORG 0x500]         ;将setup放到0x500处

dw 0x55aa           ; 魔数，用于判断错误

; 由setup进入保护模式，需要构建gdt表，这里先把注释写好
mov     si, loading
call    print

jmp     $       ; 停在这里

; 如何调用
; mov     si, msg   ; 1 传入字符串
; call    print     ; 2 调用
print:
    mov ah, 0x0e    ; 指定要使用的功能是0x0e，0x0E表示在TTY模式下写字符
    ; bh和bl的设置没有效果
.next:
    mov al, [si]    ; 要输出的字符
    cmp al, 0       ; 字符串不结束就一直打印
    jz .done
    int 0x10        ; 调用bios的10号中断

    inc si
    jmp .next
.done:
    ret

loading:
    db "[setup.asm] : Preparing to enter protect mode ...", 10, 13, 0     ; \n\r

[SECTION .gdt]
gdt_base:
    dd 0, 0                     ; gdt表的最开始是一个空表，占8字节