        .text
        .global main
main:
        sub     $24, %rsp
        lea     4(%rsp), %rcx
        lea     8(%rsp), %rdx
        lea     12(%rsp), %rsi
        mov     $12616, %edi
        call    unpack_date
        mov     $0, %eax
        add     $24, %rsp
        ret
