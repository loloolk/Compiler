	.file	"t.c"
	.text
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp 
	.seh_pushreg	%rbp

	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0

	subq	$32, %rsp ; goes back 32 bytes ;
	.seh_stackalloc	32 ; allocates previously reserved space ;
	.seh_endprologue

	movl	%ecx, 16(%rbp) ;argc
	movq	%rdx, 24(%rbp) ;argv

	call	__main
	movl	16(%rbp), %eax ;move argc -> 16(%rbp) to %eax (return value)

	addq	$32, %rsp ; restores the stack pointer ;
	popq	%rbp
ret
	.seh_endproc
