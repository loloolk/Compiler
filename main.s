.section .text
.globl main
main:
subq $32, %rsp
movl %ecx, 16(%rbp)
call _main
addq $32, %rsp
ret

.globl _main
_main:
pushq %rbp
movq %rsp, %rbp
movl 16(%rbp), %eax
movq %rbp, %rsp
popq %rbp
ret
