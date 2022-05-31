.section .text
.globl main
main: # 0, 0
	subq $32, %rsp

    movl 8(%rdx), %eax

    addq $32, %rsp
ret

