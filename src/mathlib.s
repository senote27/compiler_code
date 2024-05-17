.section .text
.global fact
fact:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, %rax
    cmpq $0, %rax
    jne .Lfact_start
    movq $1, %rax
    jmp .Lfact_end
.Lfact_start:
    movq $1, %rcx
.Lfact_loop:
    imulq %rax, %rcx
    decq %rax
    jnz .Lfact_loop
    movq %rcx, %rax
.Lfact_end:
    popq %rbp
    ret

.global lntwo
lntwo:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, %rax
    movq $0, %rcx
    cmpq $0, %rax
    je .Llntwo_end
.Llntwo_loop:
    shrq $1, %rax
    incq %rcx
    jnz .Llntwo_loop
.Llntwo_end:
    movq %rcx, %rax
    popq %rbp
    ret

.global gcd
gcd:
    pushq %rbp
    movq %rsp, %rbp
    movq %rdi, %rax
    movq %rsi, %rbx
.Lgcd_loop:
    testq %rbx, %rbx
    je .Lgcd_end
    movq %rax, %rdx
    movq %rbx, %rax
    movq %rdx, %rbx
    cqto
    idivq %rax
    movq %rdx, %rbx
    jmp .Lgcd_loop
.Lgcd_end:
    popq %rbp
    ret

