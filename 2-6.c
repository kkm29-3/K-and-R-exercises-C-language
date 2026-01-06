#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(){
    unsigned x = 0b11111111; // Example value for x
    unsigned y = 0b00000000; // Example value for y
    int p = 5;               // Example position
    int n = 3;               // Example number of bits

    unsigned result = setbits(x, p, n, y);
    printf("Result: %u\n", result); // Print the result

    return 0;
}

/* setbits(x, p, n, y):
   return x with the n bits starting at position p
   replaced by the rightmost n bits of y */
    unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned mask = ~(~0u << n);                 /* n rightmost bits = 1 */

    /* rightmost n bits of y, shifted into position p..p-n+1 */
    unsigned y_part = (y & mask) << (p + 1 - n);

    /* n bits wide field at position p in x */
    unsigned field_mask = mask << (p + 1 - n);

    /* clear that field in x, then OR in the y bits */
    return (x & ~field_mask) | y_part;
}
