        .text
        .global find_bigger
find_bigger:
        mov     (%rdi), %ecx
        mov     $1, %eax
        jmp     for_cond
for_do:
        add     $1, %rax
for_cond:
        cmp     %rsi, %rax
        jnb     for_end
        mov     (%rdi,%rax,4), %edx
        cmp     %ecx, %edx
        jle     for_do
        mov     %edx, %ecx
        jmp     for_do
for_end:
        mov     %ecx, %eax
        ret
