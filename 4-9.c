// #include <stdio.h>

// #define BUFFSIZE 100

// int getch(void);
// void ungetch(int c);

// int main(void) {
//     int c;

//     c = getch();
//     putchar(c);

//     ungetch(EOF);

//     c = getch();
//     putchar(c);

//     return 0;
// }

// int bufp = 0;
// int buf[BUFFSIZE];

// int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

// void ungetch(int c) {
//     if (bufp >= BUFFSIZE) {
//         printf("ungetch: too many characters\n");
//     } else {
//         buf[bufp++] = c;
//     }
// }

// NOTE: The getch() function can't manage correctly the EOF character because
// in the original K&R version buf was a char array, which can't hold the EOF
// because EOF is -1 and char can't hold negative number. However the gcc
// compiler, on Windows, uses by default signed chars which can hold EOF, but
// this is not platform independent.

#include <stdio.h>

#define BUFFSIZE 100

int getch(void);
void ungetch(int c);

int bufp = 0;              /* next free position in buf */
int buf[BUFFSIZE];         /* buffer for ungetch */

/* getch: get a (possibly pushed-back) character */
int getch(void)
{
    if (bufp > 0)
        return buf[--bufp];
    else
        return getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
    if (c == EOF) {
        /* Do not push EOF into the buffer */
        return;
    }

    if (bufp >= BUFFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}

int main(void)
{
    int c;

    /* Read one character from stdin and echo it */
    c = getch();
    if (c != EOF)
        putchar(c);

    /* Push it back and read it again */
    ungetch(c);
    c = getch();
    if (c != EOF)
        putchar(c);

    return 0;
}

