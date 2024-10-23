	.file	"use_packdate.c"
	.text
	.globl	year
	.data
	.align 4
	.type	year, @object
	.size	year, 4
year:
	.long	2024
	.globl	month
	.align 4
	.type	month, @object
	.size	month, 4
month:
	.long	9
	.globl	day
	.align 4
	.type	day, @object
	.size	day, 4
day:
	.long	18
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	day(%rip), %edx
	movl	month(%rip), %ecx
	movl	year(%rip), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	pack_date@PLT
	movw	%ax, -2(%rbp)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
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
