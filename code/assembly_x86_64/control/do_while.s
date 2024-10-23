# v - eax	z - ecx
	.text
do_while:
	shr	$1, %eax
	inc	%ecx
	and	%eax, %eax
	jne	do_while
