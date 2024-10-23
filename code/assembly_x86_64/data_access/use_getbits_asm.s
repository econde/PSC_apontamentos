        .data
x:
        .quad   30

        .bss
y:
        .zero   8

        .text
        .global main
main:
        sub     $8, %rsp
        mov     $3, %edx
        mov     $4, %esi
        mov     x(%rip), %rdi
        call    getbits
        mov     %rax, y(%rip)
        mov     $0, %eax
        add     $8, %rsp
        ret
