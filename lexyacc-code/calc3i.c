#ifndef CALC3I_H
#define CALC3I_H

#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

static int lbl;

int ex(nodeType *p) {
    int lbl1, lbl2;

    if (!p) return 0;
    switch(p->type) {
        case typeCon:       
            printf("\tmovq\t$%d, %%rax\n", p->con.value);
            printf("\tpushq\t%%rax\n");
            break;
        case typeId:        
            printf("\tmovq\tvar_%c(%%rip), %%rax\n", p->id.i + 'a'); 
            printf("\tpushq\t%%rax\n");
            break;
        case typeOpr:
            switch(p->opr.oper) {
                case WHILE:
                    printf("L%03d:\n", lbl1 = lbl++);
                    ex(p->opr.op[0]);
                    printf("\tpopq\t%%rax\n");
                    printf("\tcmpq\t$0, %%rax\n");
                    printf("\tje\tL%03d\n", lbl2 = lbl++);
                    ex(p->opr.op[1]);
                    printf("\tjmp\tL%03d\n", lbl1);
                    printf("L%03d:\n", lbl2);
                    break;
                case IF:
                    ex(p->opr.op[0]);
                    printf("\tpopq\t%%rax\n");
                    printf("\tcmpq\t$0, %%rax\n");
                    if (p->opr.nops > 2) {
                        /* if else */
                        printf("\tje\tL%03d\n", lbl1 = lbl++);
                        ex(p->opr.op[1]);
                        printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                        printf("L%03d:\n", lbl1);
                        ex(p->opr.op[2]);
                        printf("L%03d:\n", lbl2);
                    } else {
                        /* if */
                        printf("\tje\tL%03d\n", lbl1 = lbl++);
                        ex(p->opr.op[1]);
                        printf("L%03d:\n", lbl1);
                    }
                    break;
                case PRINT:     
                    ex(p->opr.op[0]);
                    printf("\tpopq\t%%rsi\n");
                    printf("\tmovq\t$.LC0, %%rdi\n");
                    printf("\tmovq\t$0, %%rax\n");
                    printf("\tcall\tprintf\n");
                    break;
                case '=':       
                    ex(p->opr.op[1]);
                    printf("\tpopq\t%%rax\n");
                    printf("\tmovq\t%%rax, var_%c(%%rip)\n", p->opr.op[0]->id.i + 'a');
                    break;
                case UMINUS:    
                    ex(p->opr.op[0]);
                    printf("\tpopq\t%%rax\n");
                    printf("\tnegq\t%%rax\n");
                    printf("\tpushq\t%%rax\n");
                    break;
                case FACT:
                    ex(p->opr.op[0]);
                    printf("\tpopq\t%%rdi\n");
                    printf("\tcall\tfact\n");
                    printf("\tpushq\t%%rax\n");
                    break;
                case LNTWO:
                    ex(p->opr.op[0]);
                    printf("\tpopq\t%%rdi\n");
                    printf("\tcall\tlntwo\n");
                    printf("\tpushq\t%%rax\n");
                    break;
                case GCD:
                    ex(p->opr.op[0]);
                    ex(p->opr.op[1]);
                    printf("\tpopq\t%%rbx\n");
                    printf("\tpopq\t%%rax\n");
                    printf("\tcall\tgcd\n");
                    printf("\tpushq\t%%rax\n");
                    break;
                default:
                    ex(p->opr.op[0]);
                    ex(p->opr.op[1]);
                    printf("\tpopq\t%%rbx\n");
                    printf("\tpopq\t%%rax\n");
                    switch(p->opr.oper) {
                        case '+':   
                            printf("\taddq\t%%rbx, %%rax\n");
                            printf("\tpushq\t%%rax\n");
                            break;
                        case '-':   
                            printf("\tsubq\t%%rbx, %%rax\n");
                            printf("\tpushq\t%%rax\n");
                            break;
                        case '*':   
                            printf("\timulq\t%%rbx, %%rax\n");
                            printf("\tpushq\t%%rax\n");
                            break;
                        case '/':   
                            printf("\tmovq\t%%rax, %%rcx\n"); // Store RAX in RCX temporarily
                            printf("\tpopq\t%%rax\n"); // Pop top of stack into RAX which is the dividend
                            printf("\tcqo\n"); // Sign-extend RAX into RDX:RAX for division
                            printf("\tidivq\t%%rcx\n"); // Divide RDX:RAX by RCX
                            printf("\tpushq\t%%rax\n"); // Push the quotient onto the stack
                            break;
                        case '<':
                            printf("\tcmpq\t%%rax, %%rbx\n");
                            printf("\tsetl\t%%al\n");
                            printf("\tmovzbq\t%%al, %%rax\n");
                            printf("\tpushq\t%%rax\n");
                            break;
                        case '>':
                            printf("\tcmpq\t%%rax, %%rbx\n");
                            printf("\tsetg\t%%al\n");
                            printf("\tmovzbq\t%%al, %%rax\n");
                            printf("\tpushq\t%%rax\n");
                            break;
                        case GE:
                            printf("\tcmpq\t%%rax, %%rbx\n");
                            printf("\tsetge\t%%al\n");
                            printf("\tmovzbq\t%%al, %%rax\n");
                            printf("\tpushq\t%%rax\n");
                            break;
                        case LE:
                            printf("\tcmpq\t%%rax, %%rbx\n");
                            printf("\tsetle\t%%al\n");
                            printf("\tmovzbq\t%%al, %%rax\n");
                            printf("\tpushq\t%%rax\n");
                            break;
                        case NE:
                            printf("\tcmpq\t%%rax, %%rbx\n");
                            printf("\tsetne\t%%al\n");
                            printf("\tmovzbq\t%%al, %%rax\n");
                            printf("\tpushq\t%%rax\n");
                            break;
                        case EQ:
                            printf("\tcmpq\t%%rax, %%rbx\n");
                            printf("\tsete\t%%al\n");
                            printf("\tmovzbq\t%%al, %%rax\n");
                            printf("\tpushq\t%%rax\n");
                            break;
                        default:
                            // Handle any other operators if needed
                            return 0;
                    }
                    break;
            }
    }

    return 0;
}

#endif  // CALC3I_H

