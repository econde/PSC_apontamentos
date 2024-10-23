        .text
        .global pack_date
pack_date:
        mov     %dx, %ax
        sal     $5, %esi
        add     %si, %ax
        sub     $2000, %edi
        sal     $9, %edi
        add     %di, %ax
        ret
