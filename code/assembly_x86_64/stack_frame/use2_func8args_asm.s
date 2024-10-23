        .text
        .global use_func8args
use_func8args:
        push    %rbp
        mov     %rsp, %rbp
        sub     $16, %rsp
        movq    $1, -8(%rbp)
        movl    $2, -12(%rbp)
        movw    $3, -14(%rbp)
        movb    $-4, -15(%rbp)
        lea     -15(%rbp), %r8
        push    %r8
        movb    -15(%rbp), %dil
        push    %rdi
        lea     -14(%rbp), %r9
        movw    -14(%rbp), %r8w
        lea     -12(%rbp), %rcx
        movl    -12(%rbp), %edx
        lea     -8(%rbp), %rsi
        movq    -8(%rbp), %rdi
        call    proc
        movslq  -12(%rbp), %rdx
        movq    -8(%rbp), %rcx
        add     %rdx, %rcx
        movswl  -14(%rbp), %edx
        movsbl  -15(%rbp), %eax
        sub     %eax, %edx
        mov     %edx, %eax
        cltq
        imul    %rcx, %rax
        mov     %rbp, %rsp
        pop     %rbp
        ret

