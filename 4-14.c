// #include <stdio.h>

// #define swap(t, x, y)                                                          \
//     {                                                                          \
//         t temp;                                                                \
//         temp = x;                                                              \
//         x = y;                                                                 \
//         y = temp;                                                              \
//     };

// int main(void) {
//     int x = 2;
//     int y = 3;

//     printf("x: %d, y: %d\n", x, y);

//     swap(int, x, y);
//     printf("x: %d, y: %d\n", x, y);

//     return 0;
// }

// // NOTE: A use of a block is very useful because there can be created local
// // variables that don't create conflicts with already existed entities.

// #include <stdio.h>

// #define swap(t, x, y) { t temp; temp = x; x = y; y = temp; }

// int main(void) {
//     int x, y;
    
//     printf("Enter value for x: ");
//     scanf("%d", &x);
//     printf("Enter value for y: ");
//     scanf("%d", &y);
    
//     printf("Before swap - x: %d, y: %d\n", x, y);
//     swap(int, x, y);
//     printf("After swap - x: %d, y: %d\n", x, y);
    
//     return 0;
// }

#include <stdio.h>

#define swap(t, x, y) do { \
    t _tmp = (x);          \
    (x) = (y);             \
    (y) = _tmp;            \
} while (0)

int main() {
    int a, b;
    printf("Enter two integers (a b): ");
    scanf("%d %d", &a, &b);
    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(int, a, b);
    printf("After swap:  a = %d, b = %d\n", a, b);

    double p, q;
    printf("Enter two doubles (p q): ");
    scanf("%lf %lf", &p, &q);
    printf("Before swap: p = %.2f, q = %.2f\n", p, q);
    swap(double, p, q);
    printf("After swap:  p = %.2f, q = %.2f\n", p, q);

    char c1, c2;
    printf("Enter two chars (c1 c2): ");
    scanf(" %c %c", &c1, &c2);  // Space skips whitespace
    printf("Before swap: c1 = %c, c2 = %c\n", c1, c2);
    swap(char, c1, c2);
    printf("After swap:  c1 = %c, c2 = %c\n", c1, c2);

    return 0;
}

