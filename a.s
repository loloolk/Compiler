# make 0(%ebx) the return address

.section .text
.globl main
main:
call _main
movl 0(%ebx), %eax
ret

.globl _main
_main:
movl $0, 0(%ebx)
ret
