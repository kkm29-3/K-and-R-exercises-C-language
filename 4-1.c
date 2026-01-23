#include <stdio.h>
int strrindex(char s[], char t[]) {
    int i, j, k;
    int pos = -1;                 /* rightmost position found so far */

    for (i = 0; s[i] != '\0'; ++i) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k)
            ;                     /* match t starting at s[i] */
        if (k > 0 && t[k] == '\0')
            pos = i;              /* found an occurrence, remember it */
    }
    return pos;                   /* -1 if never found */
}
/* strrindex: return rightmost index of t in s, -1 if none */

int main() {
    // char s[] = "hello world";
    // char t[] = "o";
    char s[100], t[100];
    printf("Enter string s: ");
    scanf("%99s", s);
    printf("Enter string t: ");
    scanf("%99s", t);
    
    int pos = strrindex(s, t);
    printf("Rightmost position of '%s' in '%s' is %d\n", t, s, pos);
    return 0;
}