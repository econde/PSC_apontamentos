        .text
        .global  main
main:
        sub     $8, %rsp
        mov     $4, %esi
        lea     a(%rip), %rdi
        call    find_bigger@PLT
        mov     $0, %eax
        add     $8, %rsp
        ret

        .data
a:
        .long   10
        .long   40
        .long   30
        .long   5
