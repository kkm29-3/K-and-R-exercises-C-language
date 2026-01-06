#include <stdio.h>

void reverse(char s[]) {
    int i, j;
    char c;
    for (i = 0, j = 0; s[j] != '\0'; ++j)     /* find length */
        ;
    --j;                                      /* last valid index */
    while (i < j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        ++i;
        --j;
    }
}

/* itoa: convert n into s, padded on the left to at least width characters */
void itoa(int n, char s[], int width) {
    int i, sign;

    sign = n;
    if (n < 0)
        n = -n;               /* works except for INT_MIN; ignore that here */

    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';

    /* pad with blanks until we reach width */
    while (i < width)
        s[i++] = ' ';

    s[i] = '\0';
    reverse(s);               /* reverse to correct order */
}
int main() {
    char s[100];
    int number = -12345;
    int width = 10;

    itoa(number, s, width);
    printf("Number: %d\n", number);
    printf("String with width %d: '%s'\n", width, s);

    return 0;
}