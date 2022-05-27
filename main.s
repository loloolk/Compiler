.section .text
.globl main
main:
subq $32, %rsp
movl %ecx, 0(%rbp)
call _main
addq $32, %rsp
ret

.globl _main
_main:
pushq %rbp
movq %rsp, %rbp
movl 0(%rsp), %eax
movq %rbp, %rsp
popq %rbp
ret
