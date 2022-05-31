.section .text
.globl main
main: # 0, 0
    pushl %ecx
    popl %eax
ret

.globl _main
_main:
    pushq %rbp
    movq %rsp, %rbp

    movl 12(%rbp), %eax

    movq %rbp, %rsp
    popq %rbp
ret
