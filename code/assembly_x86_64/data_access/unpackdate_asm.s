        .text
        .global unpack_date
unpack_date:
        mov     %edi, %eax
        shr     $9, %ax
        cwtl
        add     $2000, %eax
        mov     %eax, (%rsi)
        mov     %edi, %eax
        sar     $5, %ax
        and     $15, %eax
        mov     %eax, (%rdx)
        and     $31, %edi
        mov     %edi, (%rcx)
        ret
