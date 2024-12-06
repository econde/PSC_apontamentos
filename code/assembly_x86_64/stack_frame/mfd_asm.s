	.text
	.globl	must_frequent_digit
must_frequent_digit:
	endbr64
	mov	$0, %eax
	jmp	mfd_for1_cond
mfd_for1_do:
	movl	$0, -40(%rsp,%rax,4)
	add	$1, %rax
mfd_for1_cond:
	cmp	$9, %rax
	jbe	mfd_for1_do
mfd_while_do:
	cmpb	$0, (%rdi)
	je	mfd_while_exit
	inc	%rdi
	movzbl	(%rdi), %eax
	sub	$'0', %eax
	cmp	$9, %al
	ja	mfd_while_do
	movsbl	(%rdi), %eax
	sub	$'0', %eax
	cltq
	incl	-40(%rsp,%rax,4)
	jmp	mfd_while_do
mfd_while_exit:
	mov	$1, %edx
	mov	$0, %eax
	jmp	mfd_for2_cond
mfd_for2_do:
	add	$1, %rdx
mfd_for2_cond:
	cmp	$9, %rdx
	ja	mfd_for2_exit
	mov	-40(%rsp,%rdx,4), %esi
	cmp	%esi, -40(%rsp,%rax,4)
	jge	mfd_for2_do
	mov	%rdx, %rax
	jmp	mfd_for2_do
mfd_for2_exit:
	ret

	.section .note.GNU-stack
