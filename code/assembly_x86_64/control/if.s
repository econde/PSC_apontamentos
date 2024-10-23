        .text
        cmp     $0, %eax
        jne     if_end
        mov     $2, %ecx
if_end:
