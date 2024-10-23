	.text
	.globl	main
main:
	movq	(%rsi), %rdi
	call	strlen
	ret
