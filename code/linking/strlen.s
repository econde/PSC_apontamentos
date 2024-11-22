
strlen.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <strlen>:
   0:	f3 0f 1e fa          	endbr64
   4:	b8 00 00 00 00       	mov    $0x0,%eax
   9:	eb 07                	jmp    12 <strlen+0x12>
   b:	48 83 c0 01          	add    $0x1,%rax
   f:	48 89 d7             	mov    %rdx,%rdi
  12:	48 8d 57 01          	lea    0x1(%rdi),%rdx
  16:	80 3f 00             	cmpb   $0x0,(%rdi)
  19:	75 f0                	jne    b <strlen+0xb>
  1b:	c3                   	ret
