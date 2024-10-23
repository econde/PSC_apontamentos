        .text
        .global func8args
func8args:
        mov     16(%rsp), %rax
        add     %rdi, (%rsi)
        add     %edx, (%rcx)
        add     %r8w, (%r9)
        mov     8(%rsp), %edx
        add     %dl, (%rax)
        ret
