#include <stdio.h>
#include <stdlib.h>   /* for atof, exit */

#define MAXSTACK 100

/* stack */
double stack[MAXSTACK];
int sp = 0;

/* push: push value onto stack */
void push(double f)
{
    if (sp < MAXSTACK)
        stack[sp++] = f;
    else {
        printf("error: stack full\n");
        // exit(1);
    }
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return stack[--sp];
    else {
        printf("error: stack empty\n");
        // exit(1);
    }
}

int main(int argc, char *argv[])
{
    int i;
    double op2;

    /* start from argv[1], skip program name */
    for (i = 1; i < argc; i++) {
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
            else {
                printf("error: zero divisor\n");
                exit(1);
            }
            break;
        default:
            /* operand */
            push(atof(argv[i]));
            break;
        }
    }

    if (sp == 1)
        printf("result: %.8g\n", pop());
    else {
        printf("error: invalid expression\n");
        exit(1);
    }

    return 0;
}

// use cmd line to run the program
// gcc -o 5-10 5-10.c
// .\5-10 2 3 4 "+" "*"

//1️⃣ Why do we sometimes write "*" instead of *?
// Short answer:

// 👉 Because the shell (CMD) may interpret * before your C program ever sees it.
// More Test Cases (Try These)
//.\5-10 5 6 +
