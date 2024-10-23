# v - eax       z - ecx
        .text
while:
        jmp     while_cond
while_do:
        shr     $1, %eax
        inc     %ecx
while_cond:
        and     %eax, %eax
        jne     while_do
