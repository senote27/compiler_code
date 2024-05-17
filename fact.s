# fact.s

    pushq %rbp
    movq %rsp, %rbp

    # Function prologue

    movl $1, %eax        # Initialize result to 1
    movl 8(%rbp), %ecx   # Load argument (n) into ECX

    # Calculate factorial
    testl %ecx, %ecx     # Check if n is zero
    jz end               # If zero, jump to end

loop:
    imull %ecx, %eax     # Multiply result by n
    subl $1, %ecx        # Decrement n
    jnz loop             # Loop until n becomes zero

end:
    # Function epilogue

    popq %rbp
    ret

