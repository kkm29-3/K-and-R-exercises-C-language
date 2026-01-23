#include <stdio.h>

int strcmp_ptr(char *s, char *t, size_t n);

// int main(void) {
//     char s[100] = "This is the first string";
//     char *t = "This is the second string";
//     size_t nr_chars = 13;

//     int is_equal = strcmp_ptr(s, t, nr_chars);

//     if (is_equal == 0) {
//         puts("String s is equal with string t.");
//     } else if (is_equal > 0) {
//         puts("String s contains more chars than string t.");
//     } else if (is_equal < 0) {
//         puts("String s contains less chars than string t.");
//     }

//     return 0;
// }

// Return <0 if s<t, 0 if s==t, >0 if s>t *1
// int strcmp_ptr(char *s, char *t, size_t n) {
//     while ((*s == *t) && --n) {
//         if (*s == '\0')
//             return 0;

//         ++s;
//         ++t;
//     }

#include <stdio.h>

int strcmp_ptr(char *s, char *t, size_t n);

int main(void) {
    char s[100];
    char t[100];
    size_t nr_chars;

    // Get first string from user
    printf("Enter the first string: ");
    scanf("%99s", s);   // reads up to whitespace

    // Get second string from user
    printf("Enter the second string: ");
    scanf("%99s", t);   // reads up to whitespace

    // Get number of characters to compare
    printf("Enter number of characters to compare: ");
    scanf("%zu", &nr_chars);

    // Compare strings
    int is_equal = strcmp_ptr(s, t, nr_chars);

    if (is_equal == 0) {
        printf("String s is equal with string t.\n");
    } else if (is_equal > 0) {
        printf("String s contains more chars than string t.\n");
    } else {
        printf("String s contains less chars than string t.\n");
    }

    return 0;
}

// Return <0 if s<t, 0 if s==t, >0 if s>t
int strcmp_ptr(char *s, char *t, size_t n) {
    while ((*s == *t) && --n) {
        if (*s == '\0')
            return 0;

        ++s;
        ++t;
    }

    return *s - *t;
}
    // If the s string contains more characters than t, then the t char will
    // become '\0' before s char. If this happen then the s char will be its
    // ascii value and t char will be 0, so the final result will be
    // s_ascii_value - 0.

    // If the t string contains more character than s, then the s char will
    // become '\0' before t char. If this happen then the s char will be 0 and
    // t char will be whatever ascii_value is holding, so the final result will
    // be 0 - t_ascii_value.

//     return *s - *t;
// }