// #include <stdio.h>

// #define MAXLEN 100

// void int_to_array(int n, char str[]);

// int main(void) {
//     int n = -1234;
//     char str[MAXLEN];

//     int_to_array(n, str);
//     printf("%s\n", str);

//     n = -7676;

//     int_to_array(n, str);
//     printf("%s", str);

//     return 0;
// }

// void int_to_array(int n, char str[]) {
//     static int i = 0;

//     if (n) {
//         if (n < 0) {
//             i = 0;
//             str[i++] = '-';
//             n *= -1;
//         }

//         int d = n % 10;
//         n /= 10;

//         int_to_array(n, str);

//         str[i++] = d + '0';
//         str[i] = '\0';
//     }
// }

#include <stdio.h>

void printd(int n);

int main(void) {
    int n;
    
    printf("Enter an integer: ");
    scanf("%d", &n);
    printf("The digits are: ");
    printd(n);
    printf("\n");
    
    return 0;
}

void printd(int n) {
    static int first_call = 1;
    
    if (n) {
        if (first_call && n < 0) {
            first_call = 0;
            putchar('-');
            n *= -1;
        }
        
        int d = n % 10;
        n /= 10;
        
        printd(n);
        
        putchar(d + '0');
    } else {
        first_call = 1;  // Reset for next number
    }
}
