[bits 32]
[SECTION .text]

; 函数调用会将参数从右向左入栈，所以此时的栈为：
;  高位       value       +12
;   |         port        +8
;  \ /        返回地址     +4
;  低位       ebp         +0          // 这一步是out_byte内部的push ebp的操作
global in_byte
in_byte:
    push ebp;
    mov ebp, esp

    xor eax, eax
    mov edx, [ebp + 8]      ; port
    in al, dx               ; 将端口的数据读到 al 中
    leave
    ret

; 函数调用会将参数从右向左入栈，所以此时的栈为：
;  高位       value       +12
;   |         port        +8
;  \ /        返回地址     +4
;  低位       ebp         +0          // 这一步是out_byte内部的push ebp的操作
global out_byte
out_byte:
    push ebp;
    mov ebp, esp
    mov edx, [ebp + 8]      ; port
    mov eax, [ebp + 12]     ; value
    out dx, al
    leave
    ret