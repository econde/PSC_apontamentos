        .text
        .global main
main:
        sub     $8, %rsp
        mov     $2, %esi
        lea     people(%rip), %rdi
        call    get_lighter
        mov     $0, %eax
        add     $8, %rsp
        ret

        .data
people:
        .string "Ana"
        .zero   16
        .long   30
        .long   60
        .long   0b00111111111000000000000000000000
        .string "Manuel"
        .zero   13
        .long   30
        .long   70
        .long   0b01000000000000000000000000000000
