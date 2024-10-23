# v - eax       a - ecx
        .text
switch:
        cmp     $1, %eax
        jne     switch_case_10
        mov     $11, %ecx
        jmp     switch_break
switch_case_10:
        cmp     $10, %eax
        jne     switch_default
        mov     $111, %ecx
        jmp     switch_break
switch_default:
        mov     $0, %ecx
switch_break:
