main:
	pushq	%rbp
	movq	%rsp, %rbp
	
	subq	$32, %rsp

	movl	%ecx, 16(%rbp)
	call	__main

	movl	16(%rbp), %eax

	addq	$32, %rsp
	popq	%rbp
ret
