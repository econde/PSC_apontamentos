        .text
        .global main
main:
        mov     $18, %edx
        mov     $9, %esi
        mov     $2024, %edi
        call    pack_date
        mov     $0, %eax
        ret
