	.text
	.global	delay
delay:
	mov	$0, %eax
	jmp	delay_for_cond
delay_for:
	inc	%eax
delay_for_cond:
	cmp	$100, %ecx 
	jl	delay_for:

	ret
