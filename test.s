.section .text
.globl main
main: # 0, 0
	subq	$32, %rsp

	movl	%ecx, 16(%rbp) # argc
	# movl	16(%rbp), %ecx # get ready for function call
    call    _main
    

	addq	$32, %rsp
ret

.globl _main
_main:
    pushq %rbp
    movq %rsp, %rbp

    # movl %ecx, 16(%rbp)
    movl 16(%rsp), %eax

    movq %rbp, %rsp
    popq %rbp
ret
