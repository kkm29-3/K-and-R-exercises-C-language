#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

/* Buffer for ungetch */
char buf[BUFSIZE];
int bufp = 0;

/* getch: get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;
    
    while (isspace(c = getch())) /* skip white space */
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it is not a number */
        return 0;
    }
    
    sign = (c == '-') ? -1 : 1;
    
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            /* Not a number: push back both characters */
            ungetch(c);
            /* Push back the sign we already read */
            ungetch((sign == -1) ? '-' : '+');
            return 0;
        }
    }
    
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    
    *pn *= sign;
    
    if (c != EOF)
        ungetch(c);
    
    return c;
}

/* Test program */
int main(void)
{
    int n, result;
    
    printf("Enter integers (or + or - not followed by digit to test):");
  
    
    while ((result = getint(&n)) != EOF) {
        if (result == 0) {
            printf("Not a valid number, character returned to input\n");
            /* Read and discard the non-number character */
            getch();
        } else {
            printf("Read integer: %d\n", n);
        }
    }
    
    return 0;
}
