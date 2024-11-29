	.file	"main.c"
	.text
.Ltext0:
	.file 0 "/home/ezequiel/Dropbox/disciplinas/psc/psc_notes/code/pic" "main.c"
	.globl	prog_func
	.type	prog_func, @function
prog_func:
.LFB0:
	.file 1 "main.c"
	.loc 1 7 17 view -0
	.cfi_startproc
	endbr64
	.loc 1 8 2 view .LVU1
	.loc 1 8 18 is_stmt 0 view .LVU2
	movl	lib_var(%rip), %eax
	addl	prog_var(%rip), %eax
	.loc 1 9 1 view .LVU3
	ret
	.cfi_endproc
.LFE0:
	.size	prog_func, .-prog_func
	.globl	main
	.type	main, @function
main:
.LFB1:
	.loc 1 11 12 is_stmt 1 view -0
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	.loc 1 12 2 view .LVU5
	call	lib_func1@PLT
.LVL0:
	.loc 1 13 2 view .LVU6
	call	lib_func2@PLT
.LVL1:
	.loc 1 14 2 view .LVU7
	.loc 1 14 9 is_stmt 0 view .LVU8
	call	prog_func
.LVL2:
	.loc 1 15 1 view .LVU9
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.globl	prog_var
	.data
	.align 4
	.type	prog_var, @object
	.size	prog_var, 4
prog_var:
	.long	4
	.text
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xc8
	.value	0x5
	.byte	0x1
	.byte	0x8
	.long	.Ldebug_abbrev0
	.uleb128 0x3
	.long	.LASF6
	.byte	0x1d
	.long	.LASF0
	.long	.LASF1
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x4
	.long	.LASF2
	.byte	0x1
	.byte	0x1
	.byte	0xc
	.long	0x3a
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x6
	.long	.LASF3
	.byte	0x1
	.byte	0x5
	.byte	0x5
	.long	0x3a
	.uleb128 0x9
	.byte	0x3
	.quad	prog_var
	.uleb128 0x2
	.long	.LASF4
	.byte	0x3
	.uleb128 0x2
	.long	.LASF5
	.byte	0x2
	.uleb128 0x7
	.long	.LASF7
	.byte	0x1
	.byte	0xb
	.byte	0x5
	.long	0x3a
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0xad
	.uleb128 0x1
	.quad	.LVL0
	.long	0x5d
	.uleb128 0x1
	.quad	.LVL1
	.long	0x57
	.uleb128 0x1
	.quad	.LVL2
	.long	0xad
	.byte	0
	.uleb128 0x8
	.long	.LASF8
	.byte	0x1
	.byte	0x7
	.byte	0x5
	.long	0x3a
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x48
	.byte	0
	.uleb128 0x7d
	.uleb128 0x1
	.uleb128 0x7f
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x1f
	.uleb128 0x1b
	.uleb128 0x1f
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF2:
	.string	"lib_var"
.LASF6:
	.string	"GNU C2X 13.2.0 -mtune=generic -march=x86-64 -g -Og -std=c2x -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection"
.LASF5:
	.string	"lib_func1"
.LASF4:
	.string	"lib_func2"
.LASF8:
	.string	"prog_func"
.LASF7:
	.string	"main"
.LASF3:
	.string	"prog_var"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/home/ezequiel/Dropbox/disciplinas/psc/psc_notes/code/pic"
.LASF0:
	.string	"main.c"
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
