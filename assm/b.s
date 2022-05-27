
# esp is at the "top" of the stack
# ebp 
.section .text
.globl main
main:
    call    _main 
#    movl	%ecx, 0(%rbp) # argc
#    movq    %rdx, 4(%rbp) # argv

#    movl    0(%rbp), %eax # makes argc the return value
ret

.globl _main
_main:
    movl    0(%ecx), %eax
ret
