#include <stdio.h>

/* invert x's n bits starting at position p */
unsigned invert(unsigned x, int p, int n) {
    unsigned mask = (~(~0u << n)) << (p + 1 - n);
    return x ^ mask;
}

int main(void) {
    unsigned x = 0b10101010;  // Example: 170 in decimal
    int p = 3;                // Starting position
    int n = 2;                // Number of bits to invert

    unsigned result = invert(x, p, n);

    printf("Original x: %u (binary: ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
    }
    printf(")\n");

    printf("Inverted bits %d to %d: %u (binary: ", p, p - n + 1, result);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (result >> i) & 1);
    }
    printf(")\n");

    return 0;
}
