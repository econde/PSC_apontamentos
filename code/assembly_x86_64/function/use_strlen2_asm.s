        .data
message:
        .string "abcdef"

        .bss
i:
        .zero     8

        .text
        .global main
main:
        sub     $8, %rsp
        lea     message(%rip), %rdi
        call    my_strlen
        mov     %rax, i(%rip)
        mov     $0, %eax
        add     $8, %rsp
        ret
