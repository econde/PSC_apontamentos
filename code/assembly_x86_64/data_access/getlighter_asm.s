        .text
        .globl  get_lighter
get_lighter:
        mov     $1, %edx             # for (size_t i = 1; ...
        mov     $0, %r8d             # size_t lighter = 0;
        jmp     for_cond
for_do:
        add     $1, %rdx             # for (... ; ... ; ++i)
for_cond:
        cmp     %rsi, %rdx           # for ( ...; i < n_people; ...)
        jnb     for_end
        mov     %rdx, %rcx
        sal     $5, %rcx             # r8 = i * sizeof people[0]
        mov     %r8, %rax
        sal     $5, %rax             # rax = lighter * sizeof people[0]
        mov     24(%rdi,%rax), %eax  # eax = people[lighter].weight
        cmp     %eax, 24(%rdi,%rcx)  # if (people[i].weight < eax)
        jge     for_do
        mov     %rdx, %r8            # lighter = i;
        jmp     for_do
for_end:
        sal     $5, %r8              # r8 = lighter * sizeof people[0]
        lea     (%rdi,%r8), %rax     # r8 = &people[lighter]
        ret
