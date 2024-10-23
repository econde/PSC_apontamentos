        .text
f:
        endbr64
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $32, %rsp
        movq    %fs:40, %rax
        movq    %rax, -8(%rbp)
        xorl    %eax, %eax
        movb    $33, 10(%rbp)
        nop
        movq    -8(%rbp), %rax
        xorq    %fs:40, %rax
        je      .L2
        call    __stack_chk_fail@PLT
.L2:
        leave
        ret
