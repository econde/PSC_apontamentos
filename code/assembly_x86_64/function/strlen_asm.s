        .text
        .global strlen
strlen:
        mov     $0, %eax
        jmp     strlen_for_cond
strlen_for_do:
        add     $1, %rax
strlen_for_cond:
        cmpb    $0, (%rdi,%rax)
        jne     strlen_for_do
        ret
