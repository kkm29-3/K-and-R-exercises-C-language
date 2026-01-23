// #include <stdio.h>

// void strcpy_ptr(char *s, char *t, size_t n);

// int main(void) {
//     char s[100] = "This is the first string";
//     char *t = "Test is the second string, that is cool";
//     size_t nr_chars = 26;

//     strcpy_ptr(s, t, nr_chars);

//     puts(s);

//     return 0;
// }

// void strcpy_ptr(char *s, char *t, size_t n) {
//     while ((*s++ = *t++) && --n)
//         ;
//     ;
// }

#include <stdio.h>

void strcpy_ptr(char *s, char *t, size_t n);

int main(void) {
    char s[100];
    char t[100];
    size_t nr_chars;

    // Get destination string from user
    printf("Enter the first string (destination): ");
    scanf("%99s", s);   // reads up to whitespace

    // Get source string from user
    printf("Enter the second string (source): ");
    scanf("%99s", t);   // reads up to whitespace

    // Get number of characters to copy
    printf("Enter number of characters to copy: ");
    scanf("%zu", &nr_chars);

    // Perform copy
    strcpy_ptr(s, t, nr_chars);

    // Show result
    printf("Resulting string: %s\n", s);

    return 0;
}

void strcpy_ptr(char *s, char *t, size_t n) {
    while ((*s++ = *t++) && --n)
        ;
    *(s - 1) = '\0'; // ensure null termination
}