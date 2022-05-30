main:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	
	movl	%ecx, 16(%rbp)
	
	movl	16(%rbp), %ecx
	call	_main

	addq	$32, %rsp
	popq	%rbp
ret

_main:
	pushq	%rbp
	movq	%rsp, %rbp

	movl	%ecx, 16(%rbp)
	movl	16(%rbp), %eax

	popq	%rbp
ret

