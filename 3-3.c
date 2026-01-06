#include <stdio.h>

void expand(char s1[], char s2[]) {
    int i = 0;      /* index in s1 */
    int j = 0;      /* index in s2 */

    while (s1[i] != '\0') {
        if (s1[i] == '-' && i > 0 && s1[i+1] != '\0' &&
            ((s1[i-1] >= 'a' && s1[i-1] <= 'z' && s1[i+1] >= 'a' && s1[i+1] <= 'z') ||
             (s1[i-1] >= 'A' && s1[i-1] <= 'Z' && s1[i+1] >= 'A' && s1[i+1] <= 'Z') ||
             (s1[i-1] >= '0' && s1[i-1] <= '9' && s1[i+1] >= '0' && s1[i+1] <= '9')) &&
            s1[i-1] <= s1[i+1]) {

            char c;
            for (c = s1[i-1] + 1; c <= s1[i+1]; ++c)
                s2[j++] = c;
            ++i;                  /* skip the end char; it will be handled by loop */
        } else {
            s2[j++] = s1[i];
        }
        ++i;
    }
    s2[j] = '\0';
}
int main() {
    char s1[] = "a-d0-3A-Cx-z";
    char s2[100];
    expand(s1, s2);
    printf("Original: %s\n", s1);
    printf("Expanded: %s\n", s2);
    return 0;
}