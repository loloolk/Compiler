	.file	"t.c"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp

	movq	%rsp, %rbp

	subq	$32, %rsp

	movl	%ecx, 16(%rbp) ;argc
	movq	%rdx, 24(%rbp) ;argv

	movl	16(%rbp), %eax ;move argc -> 16(%rbp) to %eax (return value)

	addq	$32, %rsp ; restores the stack pointer ;
	popq	%rbp
ret
