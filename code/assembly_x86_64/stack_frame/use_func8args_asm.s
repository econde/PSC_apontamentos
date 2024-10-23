        .text
        .global use_func8args
use_func8args:
        sub     $8, %rsp
        lea     x4(%rip), %rax
        push    %rax
        movsbl  x4(%rip), %eax
        push    %rax
        lea     x3(%rip), %r9
        movswl  x3(%rip), %r8d
        lea     x2(%rip), %rcx
        mov     x2(%rip), %edx
        lea     x1(%rip), %rsi
        mov     x1(%rip), %rdi
        call    func8args
        movslq  x2(%rip), %rax
        add     x1(%rip), %rax
        movswl  x3(%rip), %edx
        movsbl  x4(%rip), %ecx
        sub     %ecx, %edx
        movslq  %edx, %rdx
        imul    %rdx, %rax
        add     $24, %rsp
        ret

        .data
x4:
        .byte   -4
        .align  2
x3:
        .word   3
        .align  4
x2:
        .long   2
        .align  8
x1:
        .quad   1
