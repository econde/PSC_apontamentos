        .data
year:
        .long    2024
month:
        .long    9
day:
        .long    18

        .text
        .global main
main:
        mov     day(%rip), %edx
        mov     month(%rip), %esi
        mov     year(%rip), %edi
        call    pack_date
        mov     $0, %eax
        ret


        .section        .note.GNU-stack
