; BIOS程序会将磁盘的第一个扇区的512字节加载到0x7c00处，为引导程序
[ORG  0x7c00]

[SECTION .data]
BOOT_MAIN_ADDR equ 0x500        ; setup.asm保存在这里，是由boot进行跳转的地址

; 代码段
[SECTION .text]
[BITS 16]           ; 编码方式
global _start       ; 声明一个全局函数
_start:
    ; 当值为3时，这个调用的功能是设置视频模式。具体来说，视频模式3对应于文本模式80列×25行，16色，8页。
    ; 这通常被认为是典型的DOS文本模式。
    mov ax, 3
    int 0x10        ;调用0x10号中断

    ; 将setup读入0x500处，通过硬盘寄存器读硬盘
    mov ecx, 2      ; 从哪个扇区开始读，CHS读硬盘方式是以下标1开始的，所以第二个扇区就是2
    mov bl, 1       ; 读取扇区数量

    ; 0x1f2 8bit 指定读取或写入的扇区数
    mov dx, 0x1f2
    mov al, bl      ; 扇区数
    out dx, al      ; 向0x1f2发送命令

    ; 0x1f3 8bit lba地址的第八位 0-7
    inc dx
    mov al, cl      ; 从哪个扇区开始读，LBA low
    out dx, al

    ; 0x1f4 8bit lba地址的中八位 8-15
    inc dx
    mov al, ch      ; LBA中8位
    out dx, al

    ; 0x1f5 8bit iba地址的高八位 16-23
    inc dx
    shr ecx, 16     ; 右移16位
    mov al, cl
    out dx, al      ; 发送LBA高8位

    ; 0x1f6 8bit
    ; 0-3 位iba地址的24-27
    ; 4 0表示主盘 1表示从盘
    ; 5、7位固定为1
    ; 6 0表示CHS模式，1表示LAB模式
    inc dx
    mov al, ch      ; LBA最高4位
    and al, 0b1110_1111
    out dx, al

    ; 0x1f7 8bit  命令或状态端口
    inc dx
    mov al, 0x20    ; 发送读盘命令
    out dx, al

    ; 检测硬盘状态
    ; 3 0表示硬盘未准备好与主机交换数据 1表示准备好了
    ; 7 0表示硬盘不忙 1表示硬盘忙
    ; 0 0表示前一条指令正常执行 1表示执行出错 出错信息通过0x1f1端口获得
.read_check:
    mov dx, 0x1f7
    in al, dx
    and al, 0b10001000  ; 取硬盘状态的第3、7位
    cmp al, 0b00001000  ; 硬盘数据准备好了且不忙了
    jnz .read_check     ; 否则就一直检查下去

    ; 从0x1f0 读数据
    mov dx, 0x1f0
    mov cx, 256         ; 要循环256次，每次读 2 字节
    mov edi, BOOT_MAIN_ADDR
.read_data:
    in ax, dx           ; 读取 2 字节
    mov [edi], ax       ; 放到edi的位置
    add edi, 2
    loop .read_data

    ; 跳过去
    mov     si, jmp_to_setup
    call    print

    jmp BOOT_MAIN_ADDR

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

jmp_to_setup:
    db "jump to setup...", 10, 13, 0

; 一个扇区要以0x55aa结尾，BIOS才能识别
times 510 - ($ - $$) db 0
db 0x55, 0xaa