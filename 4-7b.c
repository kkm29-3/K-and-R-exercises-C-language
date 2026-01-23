#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
static char buf[BUFSIZE];
static int bufp = 0;

/* Get a character from input with pushback buffer */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Push a character back to input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters pushed back\n");
    } else {
        buf[bufp++] = c;
    }
}

/* Push an entire string back to input */
void ungets(char *s)
{
    int len = strlen(s);
    /* We need to push characters in reverse order since we're using */
    /* a stack-like buffer. The rightmost char of the string will be */
    /* popped first from the buffer. */
    for (int i = len - 1; i >= 0; i--) {
        ungetch(s[i]);
    }
}

int main(void)
{
    printf("Exercise 4-7: ungets() function\n");
    printf("================================\n\n");

    printf("Pushing string 'Hello' back to input buffer...\n");
    ungets("Hello");

    printf("Reading characters from buffer:\n");
    for (int i = 0; i < 5; i++) {
        printf("%c", getch());
    }
    printf("\n\n");

    printf("Pushing string 'World!' back to input buffer...\n");
    ungets("World!");

    printf("Reading characters from buffer:\n");
    for (int i = 0; i < 6; i++) {
        printf("%c", getch());
    }
    printf("\n\n");

    printf("Test completed successfully!\n");

    return 0;
}