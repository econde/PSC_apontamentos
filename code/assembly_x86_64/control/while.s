# v - rax       z - rcx
        .text
do_while:
        shr     $1, %rax
        incq    %rcx
        and     %rax, %rax
        jne     do_while
