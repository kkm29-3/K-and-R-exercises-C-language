#include <stdio.h>

int htoi(const char s[]) {
    int i = 0;
    int value = 0;
    int digit;

    /* skip optional 0x or 0X */
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        i = 2;
    }

    for (i=0; s[i] != '\0'; ++i) {
        if (s[i] >= '0' && s[i] <= '9')
            digit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            digit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            digit = s[i] - 'A' + 10;
        else
            break;      /* stop on first non-hex char */

        value = 16 * value + digit;
    }

    return value;
}

int main(void) {
    printf("%d\n", htoi("0xAF"));  /* 175 */
    printf("%d\n", htoi("FF"));    /* 255 */
    printf("%d\n", htoi("1a3"));   /* 419 */
    return 0;
}
