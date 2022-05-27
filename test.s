.section .text
.globl main 
main:
    subq $32, %rsp
    movl %ecx, 0(%rbp) # puch argc to the stack (16 bytes for some reason)
    movq %rdx, 16(%rbp) # push argv to the stack (idek how many bytes, but I hope its 16)
    call _main
    addq $32, %rsp
ret

.globl _main
_main:
    pushq %rbp
    movq %rsp, %rbp
    movl 0(%rbp), %eax
    movq %rbp, %rsp
    popq %rbp

ret
