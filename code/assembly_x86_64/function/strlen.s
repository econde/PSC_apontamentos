	.file	"strlen.c"
	.text
	.globl	strlen
	.type	strlen, @function
strlen:
.LFB16:
	.cfi_startproc
	endbr64
	movl	$0, %eax
	jmp	.L2
.L3:
	addq	$1, %rax
	movq	%rdx, %rdi
.L2:
	leaq	1(%rdi), %rdx
	cmpb	$0, (%rdi)
	jne	.L3
	ret
	.cfi_endproc
.LFE16:
	.size	strlen, .-strlen
	.ident	"GCC: (Ubuntu 13.2.0-23ubuntu4) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
