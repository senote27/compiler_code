section .text
global _start
_start:
    call main
    mov rdi, rax
    mov rax, 60         ; syscall: exit
    xor rsi, rsi       ; status: 0
    syscall
