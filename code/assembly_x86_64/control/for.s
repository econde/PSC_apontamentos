# i - eax       a - ecx d - edx
        .text
for:
        mov     $0, %eax
        mov     $1, %ecx
        jmp     for_cond
for_do:
        shl     $1, %ecx
        inc     %eax
for_cond:
        cmp     %eax, %edx
        jl      for_do
