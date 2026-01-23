
// #include <stdio.h>

// #define MAXLEN 100

// void reverse(char str[]);

// int main(void) {
//     char str[MAXLEN] = "This is just a string";

//     printf("%s\n", str);
//     reverse(str);
//     printf("%s\n", str);

//     return 0;
// }

// void reverse(char str[]) {
//     static int i = 0;
//     static int j = 0;

//     if (str[i] != '\0') {
//         char c = str[i++];
//         reverse(str);

//         str[j++] = c;
//     }

//     // if whole reverse process is complete, reset the static variables to make
//     // this function reusable
//     if (str[j] == '\0') {
//         i = 0;
//         j = 0;
//     }
// }

// // NOTE: As a simple observation when recursive functions are used, static
// // variables become handy to construct some useful functionalities.


#include <stdio.h>

#define MAXLEN 100

void reverse(char str[]);

int main(void) {
    char str[MAXLEN];
    int i = 0;

    printf("Enter a string (end with Enter): ");

    // Read char-by-char with getchar
    int c;
    while ((c = getchar()) != '\n' && i < MAXLEN - 1) {
        str[i++] = (char)c;
    }
    str[i] = '\0';

    printf("Original: %s\n", str);
    reverse(str);
    printf("Reversed: %s\n", str);

    return 0;
}

void reverse(char str[]) {
    static int i = 0;
    static int j = 0;

    if (str[i] != '\0') {
        char ch = str[i++];
        reverse(str);
        str[j++] = ch;
    }

    if (str[j] == '\0') {
        i = 0;
        j = 0;
    }
}
// NOTE: As a simple observation when recursive functions are used, static
// variables become handy to construct some useful functionalities.