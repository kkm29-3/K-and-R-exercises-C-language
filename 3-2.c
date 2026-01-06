#include <stdio.h>
/* escape: copy t to s, converting real control chars to escape sequences */
void escape(char s[], char t[]) {
    int i, j;

    for (i = 0, j = 0; t[i] != '\0'; ++i) {
        switch (t[i]) {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        /* add more if you want: '\a', '\b', '\r', etc. */
        default:
            s[j++] = t[i];
            break;
        }
    }
    s[j] = '\0';
}

int main() {
    char s[100];
    char t[] = "Hello\tWorld\nThis is a test.";
    escape(s, t);
    printf("Original: %s\n", t);
    printf("Escaped: %s\n", s);
    return 0;
}

