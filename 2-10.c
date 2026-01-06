#include <stdio.h>

int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int main(void) {
    char input[] = "Hello World!";
    printf("Original: %s\n", input);

    for (int i = 0; input[i] != '\0'; i++) {
        input[i] = lower(input[i]);
    }

    printf("Lowercase: %s\n", input);
    return 0;
}

