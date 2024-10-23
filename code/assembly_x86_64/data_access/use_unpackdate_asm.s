        .text
        .global main
main:
        sub     $8, %rsp
        lea     day(%rip), %rcx
        lea     month(%rip), %rdx
        lea     year(%rip), %rsi
        mov     $2024 - 2000 << 9 | 10 << 5 | 8, %edi
        call    unpack_date
        mov     $0, %eax
        add     $8, %rsp
        ret

        .bss
day:
        .zero   4
month:
        .zero   4
year:
        .zero   4

