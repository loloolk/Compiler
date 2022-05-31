
main:
	pushq	%rbp
	
	movq	%rsp, %rbp
	
	subq	$32, %rsp
	
	movl	%ecx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	
	movq	24(%rbp), %rax
	movq	8(%rax), %rax
	
	addq	$32, %rsp
	popq	%rbp
ret
