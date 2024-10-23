        .text
        cmp     $0, %eax
        jne     if_else
        mov     $2, %ecx
        jmp     if_end
if_else:
        mov     $3, %ecx
if_end:
