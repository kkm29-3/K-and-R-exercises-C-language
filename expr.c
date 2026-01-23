#include <stdio.h>
#include <stdlib.h>   // atof()
#include <ctype.h>

#define MAXSTACK 100

double stack[MAXSTACK];
int sp = 0;   // stack pointer

/* push value onto stack */
void push(double value) {
    if (sp < MAXSTACK)
        stack[sp++] = value;
    else
        printf("Error: stack full\n");
}

/* pop value from stack */
double pop(void) {
    if (sp > 0)
        return stack[--sp];
    else {
        printf("Error: stack empty\n");
        return 0.0;
    }
}

int main(int argc, char *argv[]) {
    double op2;

    /* start from argv[1], argv[0] is program name */
    for (int i = 1; i < argc; i++) {

        /* if argument starts with digit or minus+digit → number */
        if (isdigit(argv[i][0]) ||
            (argv[i][0] == '-' && isdigit(argv[i][1]))) {

            push(atof(argv[i]));
        }
        else {
            switch (argv[i][0]) {
                case '+':
                    push(pop() + pop());
                    break;

                case '*':
                    push(pop() * pop());
                    break;

                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;

                case '/':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        printf("Error: division by zero\n");
                    break;

                default:
                    printf("Unknown operator: %s\n", argv[i]);
                    return 1;
            }
        }
    }

    /* final result */
    printf("Result = %.8g\n", pop());
    return 0;
}
