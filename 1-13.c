#include <stdio.h>

#define IN      1   /* inside a word */
#define OUT     0   /* outside a word */
#define MAXWORD 10  /* track lengths 1..9, 10+ */

int main(void)
{
    int c, state, len, i, j;
    int wl[MAXWORD + 1];   /* wl[1]..wl[9], wl[10] = 10+ */

    state = OUT;
    len = 0;

    for (i = 0; i <= MAXWORD; ++i)
        wl[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                /* end of a word */
                if (len > MAXWORD)
                    ++wl[MAXWORD];
                else
                    ++wl[len];
                len = 0;
                state = OUT;
            }
        } else {
            state = IN;
            ++len;
        }
    }

    /* in case input ends in a word without trailing space */
    if (state == IN) {
        if (len > MAXWORD)
            ++wl[MAXWORD];
        else
            ++wl[len];
    }

    /* print histogram */
    printf("Word length histogram (horizontal)\n");
    for (i = 1; i < MAXWORD; ++i) {
        printf("%2d: ", i);
        for (j = 0; j < wl[i]; ++j)
            putchar('*');
        putchar('\n');
    }

    printf("10+: ");
    for (j = 0; j < wl[MAXWORD]; ++j)
        putchar('*');
    putchar('\n');

    return 0;
}
