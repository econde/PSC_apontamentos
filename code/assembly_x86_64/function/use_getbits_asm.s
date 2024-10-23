	.text
	.global main
main:
	mov	$3, %edx
	mov	$4, %esi
	mov	$450, %rdi
	call	getbits
	ret
