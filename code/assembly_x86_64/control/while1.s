# v - eax       z - ecx
        .text
while:
        and     %eax, %eax
        je      while_end
        shr     $1, %eax
        inc     %ecx
        jmp     while
while_end:
